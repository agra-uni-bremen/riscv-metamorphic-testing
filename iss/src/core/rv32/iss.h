#pragma once

#include "core/common/bus_lock_if.h"
#include "core/common/clint_if.h"
#include "core/common/instr.h"
#include "core/common/irq_if.h"
#include "core/common/trap.h"
#include "core/common/fp.h"
#include "csr.h"
#include "mem_if.h"
#include "syscall_if.h"
#include "util/common.h"

#include <assert.h>
#include <stdint.h>
#include <string.h>

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <unordered_set>
#include <vector>


namespace rv32 {

constexpr int EXIT_TOHOST = 0;
constexpr int EXIT_LOAD_ADDRESS = 1;
constexpr int EXIT_STORE_ADDRESS = 2;
constexpr int EXIT_NUM_INSTR = 3;
constexpr int EXIT_CSR_ACCESS = 4;
constexpr int EXIT_SPECIAL_INSTR = 5;

struct ExitNotification {
	int code;
	ExitNotification(int code) 
		: code(code) {
	}
};


struct RegFile {
	static constexpr unsigned NUM_REGS = 32;

	int32_t regs[NUM_REGS];

	RegFile();

	RegFile(const RegFile &other);

	void write(uint32_t index, int32_t value);

	int32_t read(uint32_t index);

	uint32_t shamt(uint32_t index);

	int32_t &operator[](const uint32_t idx);

	void show();

	enum e : uint16_t {
		x0 = 0,
		x1,
		x2,
		x3,
		x4,
		x5,
		x6,
		x7,
		x8,
		x9,
		x10,
		x11,
		x12,
		x13,
		x14,
		x15,
		x16,
		x17,
		x18,
		x19,
		x20,
		x21,
		x22,
		x23,
		x24,
		x25,
		x26,
		x27,
		x28,
		x29,
		x30,
		x31,

		zero = x0,
		ra = x1,
		sp = x2,
		gp = x3,
		tp = x4,
		t0 = x5,
		t1 = x6,
		t2 = x7,
		s0 = x8,
		fp = x8,
		s1 = x9,
		a0 = x10,
		a1 = x11,
		a2 = x12,
		a3 = x13,
		a4 = x14,
		a5 = x15,
		a6 = x16,
		a7 = x17,
		s2 = x18,
		s3 = x19,
		s4 = x20,
		s5 = x21,
		s6 = x22,
		s7 = x23,
		s8 = x24,
		s9 = x25,
		s10 = x26,
		s11 = x27,
		t3 = x28,
		t4 = x29,
		t5 = x30,
		t6 = x31,
	};
};


struct PendingInterrupts {
	PrivilegeLevel target_mode;
	uint32_t pending;
};

struct ISS : public external_interrupt_target, public clint_interrupt_target, public iss_syscall_if {
	clint_if *clint = nullptr;
	instr_memory_if *instr_mem = nullptr;
	data_memory_if *mem = nullptr;
	syscall_emulator_if *sys = nullptr;  // optional, if provided, the iss will intercept and handle syscalls directly
	RegFile regs;
	FpRegs fp_regs;
	uint32_t pc = 0;
	uint32_t last_pc = 0;
	bool trace = false;
	bool shall_exit = false;
	csr_table csrs;
	PrivilegeLevel prv = MachineMode;
	uint64_t lr_sc_counter = 0;
	uint64_t total_num_instr = 0;

	// last decoded and executed instruction and opcode
	Instruction instr;
	Opcode::Mapping op;

	CoreExecStatus status = CoreExecStatus::Runnable;
	std::unordered_set<uint32_t> breakpoints;
	bool debug_mode = false;

	static constexpr int32_t REG_MIN = INT32_MIN;

	ISS(uint32_t hart_id, bool use_E_base_isa = false);
	
	void randomize_state();

	void exec_step();

	void init(instr_memory_if *instr_mem, data_memory_if *data_mem, uint32_t entrypoint, uint32_t sp);

	void trigger_external_interrupt(PrivilegeLevel level) override;

	void clear_external_interrupt(PrivilegeLevel level) override;

	void trigger_timer_interrupt(bool status) override;

	void trigger_software_interrupt(bool status) override;

	void sys_exit() override;
	unsigned get_syscall_register_index() override;
	uint32_t read_register(unsigned idx) override;
	void write_register(unsigned idx, uint32_t value) override;

	uint32_t get_hart_id();

	void release_lr_sc_reservation() {
		lr_sc_counter = 0;
		mem->atomic_unlock();
	}

	void fp_prepare_instr();
	void fp_finish_instr();
	void fp_set_dirty();
	void fp_update_exception_flags();
	void fp_setup_rm();
	void fp_require_not_off();

	uint32_t get_csr_value(uint32_t addr);
	void set_csr_value(uint32_t addr, uint32_t value);

	bool is_invalid_csr_access(uint32_t csr_addr, bool is_write);
	void validate_csr_counter_read_access_rights(uint32_t addr);

	unsigned pc_alignment_mask() {
		if (csrs.misa.has_C_extension())
			return ~0x1;
		else
			return ~0x3;
	}

	inline void trap_check_pc_alignment() {
		assert(!(pc & 0x1) && "not possible due to immediate formats and jump execution");

		if (unlikely((pc & 0x3) && (!csrs.misa.has_C_extension()))) {
			// NOTE: misaligned instruction address not possible on machines supporting compressed instructions
			raise_trap(EXC_INSTR_ADDR_MISALIGNED, pc);
		}
	}

	template <unsigned Alignment, bool isLoad>
	inline void trap_check_addr_alignment(uint32_t addr) {
		if (unlikely(addr % Alignment)) {
			raise_trap(isLoad ? EXC_LOAD_ADDR_MISALIGNED : EXC_STORE_AMO_ADDR_MISALIGNED, addr);
		}
	}

	inline void execute_amo(Instruction &instr, std::function<int32_t(int32_t, int32_t)> operation) {
		uint32_t addr = regs[instr.rs1()];
		trap_check_addr_alignment<4, false>(addr);
		uint32_t data;
		try {
			data = mem->atomic_load_word(addr);
		} catch (SimulationTrap &e) {
			if (e.reason == EXC_LOAD_ACCESS_FAULT)
				e.reason = EXC_STORE_AMO_ACCESS_FAULT;
			throw e;
		}
		uint32_t val = operation(data, regs[instr.rs2()]);
		mem->atomic_store_word(addr, val);
		regs[instr.rd()] = data;
	}

	inline bool m_mode() {
		return prv == MachineMode;
	}

	inline bool s_mode() {
		return prv == SupervisorMode;
	}

	inline bool u_mode() {
		return prv == UserMode;
	}

	PrivilegeLevel prepare_trap(SimulationTrap &e);

	void prepare_interrupt(const PendingInterrupts &x);

	PendingInterrupts compute_pending_interrupts();

	bool has_pending_enabled_interrupts() {
		return compute_pending_interrupts().target_mode != NoneMode;
	}

	bool has_local_pending_enabled_interrupts() {
		return csrs.mie.reg & csrs.mip.reg;
	}

	void return_from_trap_handler(PrivilegeLevel return_mode);

	void switch_to_trap_handler(PrivilegeLevel target_mode);

	void performance_and_sync_update(Opcode::Mapping executed_op);

	void run_step();

	void run();

	void show();
};

}  // namespace rv32