#include <cstdlib>
#include <ctime>
#include <stdint.h>

#include "core/rv32/elf_loader.h"
#include "core/rv32/iss.h"
#include "core/rv32/mem.h"

#include <boost/io/ios_state.hpp>
#include <boost/program_options.hpp>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace rv32;


struct EmptyMemoryInterface : public instr_memory_if, public data_memory_if {
	uint32_t load_instr(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}

	int32_t load_word(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	int32_t load_half(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	int32_t load_byte(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	uint32_t load_uhalf(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	uint32_t load_ubyte(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}

	void store_word(uint64_t addr, uint32_t value) {
		throw std::runtime_error("not implemented");
	}
	void store_half(uint64_t addr, uint16_t value) {
		throw std::runtime_error("not implemented");
	}
	void store_byte(uint64_t addr, uint8_t value) {
		throw std::runtime_error("not implemented");
	}

	virtual int32_t atomic_load_word(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	virtual void atomic_store_word(uint64_t addr, uint32_t value) {
		throw std::runtime_error("not implemented");
	}
	virtual int32_t atomic_load_reserved_word(uint64_t addr) {
		throw std::runtime_error("not implemented");
	}
	virtual bool atomic_store_conditional_word(uint64_t addr, uint32_t value) {
		throw std::runtime_error("not implemented");
	}
	virtual void atomic_unlock() {
		throw std::runtime_error("not implemented");
	}
};



struct InstrBuilder {
	
	static inline uint32_t LUI(unsigned rd, unsigned U_imm) {
		return ((U_imm & 1048575) << 12) | ((rd & 0x1f) << 7) | 0b0110111;
	}
	
	static inline uint32_t AUIPC(unsigned rd, unsigned U_imm) {
		return ((U_imm & 1048575) << 12) | ((rd & 0x1f) << 7) | 0b0010111;
	}
	
	
	static inline uint32_t JAL(unsigned rd, int J_imm) {
		return 0b1101111 | ((rd & 0x1f) << 7) | ((J_imm & (0b11111111 << 12)) | ((J_imm & (1 << 11)) << 9) | ((J_imm & 0b11111111110) << 20) | ((J_imm & (1 << 20)) << 11));
	}
	
	static inline uint32_t JALR(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 103;
	}
	
	
	static inline uint32_t _branch_format(unsigned rs1, unsigned rs2, int B_imm) {
		return ((((B_imm & 0b11110) << 7) | ((B_imm & (1 << 11)) >> 4)) | (((B_imm & (0b111111 << 5)) << 20) | ((B_imm & (1 << 12)) << 19))) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b1100011;
	}
	
	static inline uint32_t BEQ(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b000 << 12);
	}
	
	static inline uint32_t BNE(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b001 << 12);
	}
	
	static inline uint32_t BLT(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b100 << 12);
	}
	
	static inline uint32_t BGE(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b101 << 12);
	}
	
	static inline uint32_t BLTU(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b110 << 12);
	}
	
	static inline uint32_t BGEU(unsigned rs1, unsigned rs2, int B_imm) {
		return _branch_format(rs1, rs2, B_imm) | (0b111 << 12);
	}
	
	
	static inline uint32_t LB(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b000 << 12);
	}
	
	static inline uint32_t LH(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b001 << 12);
	}
	
	static inline uint32_t LW(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b010 << 12);
	}
	
	static inline uint32_t LBU(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b100 << 12);
	}
	
	static inline uint32_t LHU(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rd & 0x1f) << 7) | ((rs1 & 0x1f) << 15) | 0b0000011 | (0b101 << 12);
	}
	
	static inline uint32_t SB(unsigned rs2, unsigned rs1, int S_imm) {
		return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b000 << 12);
	}
	
	static inline uint32_t SH(unsigned rs2, unsigned rs1, int S_imm) {
		return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b001 << 12);
	}
	
	static inline uint32_t SW(unsigned rs2, unsigned rs1, int S_imm) {
		return (((S_imm & 0b11111) << 7) | ((S_imm & (0b1111111 << 5)) << 20)) | ((rs1 & 0x1f) << 15) | ((rs2 & 0x1f) << 20) | 0b0100011 | (0b010 << 12);
	}
	
	
	static inline uint32_t ADDI(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011;
	}
	
	static inline uint32_t SLTI(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b010 << 12);
	}
	
	static inline uint32_t SLTIU(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b011 << 12);
	}
	
	static inline uint32_t XORI(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b100 << 12);
	}
	
	static inline uint32_t ORI(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b110 << 12);
	}
	
	static inline uint32_t ANDI(unsigned rd, unsigned rs1, int I_imm) {
		return ((I_imm & 4095) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b111 << 12);
	}
	
	
	static inline uint32_t SLLI(unsigned rd, unsigned rs1, unsigned shamt) {
		return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b001 << 12);
	}
	
	static inline uint32_t SRLI(unsigned rd, unsigned rs1, unsigned shamt) {
		return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b101 << 12);
	}
	
	static inline uint32_t SRAI(unsigned rd, unsigned rs1, unsigned shamt) {
		return ((shamt & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0010011 | (0b101 << 12) | (0b0100000 << 25);
	}


	static inline uint32_t ADD(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011;
	}
	
	static inline uint32_t SUB(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b0100000 << 25);
	}
	
	static inline uint32_t SLL(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b001 << 12);
	}
	
	static inline uint32_t SLT(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b010 << 12);
	}
	
	static inline uint32_t SLTU(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b011 << 12);
	}
	
	static inline uint32_t XOR(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b100 << 12);
	}

	static inline uint32_t SRL(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b101 << 12);
	}
	
	static inline uint32_t SRA(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b101 << 12) | (0b0100000 << 25);
	}
	
	static inline uint32_t OR(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b110 << 12);
	}
	
	static inline uint32_t AND(unsigned rd, unsigned rs1, unsigned rs2) {
		return ((rs2 & 0x1f) << 20) | ((rs1 & 0x1f) << 15) | ((rd & 0x1f) << 7) | 0b0110011 | (0b111 << 12);
	}

};


constexpr static unsigned zero = 0;


struct CodeBuilder {
	std::vector<uint32_t> code;
	unsigned idx = 0;
	
	void clear() {
		code.clear();
		idx = 0;
	}
	
	uint32_t next() {
		return code[idx++];
	}
	
	bool has_next() {
		return idx < code.size();
	}
	
	
	/* RV32I instructions */
	
	void LUI(unsigned rd, unsigned imm) {
		code.push_back(InstrBuilder::LUI(rd, imm));
	}
	
	void AUIPC(unsigned rd, unsigned imm) {
		code.push_back(InstrBuilder::LUI(rd, imm));
	}
	
	
	void JAL(unsigned rd, int imm) {
		code.push_back(InstrBuilder::JAL(rd, imm));
	}
	
	void JALR(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::JALR(rd, rs1, imm));
	}
	
	
	void BEQ(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BEQ(rs1, rs2, imm));
	}
	
	void BNE(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BNE(rs1, rs2, imm));
	}
	
	void BLT(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BLT(rs1, rs2, imm));
	}
	
	void BGE(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BGE(rs1, rs2, imm));
	}
	
	void BLTU(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BLTU(rs1, rs2, imm));
	}
	
	void BGEU(unsigned rs1, unsigned rs2, int imm) {
		code.push_back(InstrBuilder::BGEU(rs1, rs2, imm));
	}
	
	
	void LB(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::LB(rd, rs1, imm));
	}
	
	void LH(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::LH(rd, rs1, imm));
	}
	
	void LW(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::LW(rd, rs1, imm));
	}
	
	void LBU(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::LBU(rd, rs1, imm));
	}
	
	void LHU(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::LHU(rd, rs1, imm));
	}
	
	void SB(unsigned rs2, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::SB(rs2, rs1, imm));
	}
	
	void SH(unsigned rs2, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::SH(rs2, rs1, imm));
	}
	
	void SW(unsigned rs2, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::SW(rs2, rs1, imm));
	}
	
	
	void ADDI(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::ADDI(rd, rs1, imm));
	}
	
	void SLTI(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::SLTI(rd, rs1, imm));
	}
	
	void SLTIU(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::SLTIU(rd, rs1, imm));
	}
	
	void XORI(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::XORI(rd, rs1, imm));
	}
	
	void ORI(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::ORI(rd, rs1, imm));
	}
	
	void ANDI(unsigned rd, unsigned rs1, int imm) {
		code.push_back(InstrBuilder::ANDI(rd, rs1, imm));
	}
	
	void SLLI(unsigned rd, unsigned rs1, unsigned shamt) {
		code.push_back(InstrBuilder::SLLI(rd, rs1, shamt));
	}
	
	void SRLI(unsigned rd, unsigned rs1, unsigned shamt) {
		code.push_back(InstrBuilder::SRLI(rd, rs1, shamt));
	}
	
	void SRAI(unsigned rd, unsigned rs1, unsigned shamt) {
		code.push_back(InstrBuilder::SRAI(rd, rs1, shamt));
	}


	void ADD(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::ADD(rd, rs1, rs2));
	}
	
	void SUB(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SUB(rd, rs1, rs2));
	}
	
	void SLL(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SLL(rd, rs1, rs2));
	}
	
	void SLT(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SLT(rd, rs1, rs2));
	}
	
	void SLTU(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SLTU(rd, rs1, rs2));
	}
	
	void XOR(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::XOR(rd, rs1, rs2));
	}
	
	void SRL(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SRL(rd, rs1, rs2));
	}
	
	void SRA(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::SRA(rd, rs1, rs2));
	}
	
	void OR(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::OR(rd, rs1, rs2));
	}
	
	void AND(unsigned rd, unsigned rs1, unsigned rs2) {
		code.push_back(InstrBuilder::AND(rd, rs1, rs2));
	}


	/* RV32I pseudo-instructions */
	
	void LI(unsigned rd, int imm) {
		if (imm >= -2048 && imm <= 2047) {
			ADDI(rd, zero, imm);
		} else {			
			auto x = imm & 4095;
			if (x > 2047) {
				x -= 4096;
				LUI(rd, (imm >> 12) + 1);
			} else {
				LUI(rd, imm >> 12);
			}
			ADDI(rd, rd, x);
		}
	}
	
	void MV(unsigned rd, unsigned rs) {
		ADD(rd, rs, zero);
	}
};



struct Random {
	unsigned operator() (unsigned n) {
		return rand() % n;
	}
	
	int8_t byte() {
		return (rand() % 256) - 128;
	}

	unsigned u_imm() {
		return rand() % 1048576;
	}
	
	int i_imm() {
		return (rand() % 4096) - 2048;
	}
	
	int s_imm() {
		return (rand() % 4096) - 2048;
	}
	
	int b_imm() {
		return (rand() % 4096) << 1;
	}
	
	int j_imm() {
		return (rand() % 1048576) << 1;
	}
	
	uint32_t reg_val() {
		return rand() % 0xffffffff;
	}
	
	uint32_t reg_val(unsigned reg) {
		if (reg == zero)
			return 0;
		return reg_val();
	}
	
	unsigned reg() {
		return rand() % 32;
	}
	
	unsigned non_zero_reg() {
		return (rand() % 31) + 1;
	}
	
	unsigned unique_reg(std::initializer_list<unsigned> xs) {
		assert (xs.size() < 32);
		unsigned ans = reg();
		while (std::any_of(xs.begin(), xs.end(), [ans](unsigned i){return i==ans;}))
			ans = (ans + 1) % 32;
		return ans;
	}
};


struct RandomLazyMemory {
	Random &random;
	std::unordered_map<uint64_t, uint8_t> data;
	
	RandomLazyMemory(Random &random)
		: random(random) {
	}

	uint8_t get_byte(uint64_t addr) {
		if (data.find(addr) == data.end()) {
			set_byte(addr, random.byte());
		}
		return data[addr];
	}
	
	void set_byte(uint64_t addr, uint8_t byte) {
		data[addr] = byte;
	}
};


struct DefaultLoadStoreMemoryInterface : public EmptyMemoryInterface {
	RandomLazyMemory &mem;
	
	DefaultLoadStoreMemoryInterface(RandomLazyMemory &mem)
		: mem(mem) {
	}
	
	int32_t load_word(uint64_t addr) {
		uint8_t b0 = mem.get_byte(addr);
		uint8_t b1 = mem.get_byte(addr+1);
		uint8_t b2 = mem.get_byte(addr+2);
		uint8_t b3 = mem.get_byte(addr+3);
		return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
	}
	int32_t load_half(uint64_t addr) {
		uint8_t b0 = mem.get_byte(addr);
		uint8_t b1 = mem.get_byte(addr+1);
		return (int16_t)((b1 << 8) | b0);
	}
	int32_t load_byte(uint64_t addr) {
		return (int8_t)mem.get_byte(addr);
	}
	uint32_t load_uhalf(uint64_t addr) {
		uint8_t b0 = mem.get_byte(addr);
		uint8_t b1 = mem.get_byte(addr+1);
		return (b1 << 8) | b0;
	}
	uint32_t load_ubyte(uint64_t addr) {
		return mem.get_byte(addr);
	}

	void store_word(uint64_t addr, uint32_t value) {
		mem.set_byte(addr, value);
		mem.set_byte(addr+1, value >> 8);
		mem.set_byte(addr+2, value >> 16);
		mem.set_byte(addr+3, value >> 24);
	}
	void store_half(uint64_t addr, uint16_t value) {
		mem.set_byte(addr, value);
		mem.set_byte(addr+1, value >> 8);
	}
	void store_byte(uint64_t addr, uint8_t value) {
		mem.set_byte(addr, value);
	}
};



struct Executor : public DefaultLoadStoreMemoryInterface {
	ISS &core;
	Random &random;
	CodeBuilder code;
	
	Executor(ISS &core, Random &random, RandomLazyMemory &mem) 
		: DefaultLoadStoreMemoryInterface(mem), core(core), random(random) {
		core.instr_mem = this;
		core.mem = this;
	}
	
	uint32_t load_instr(uint64_t addr) {
		return code.next();
	}
	
	uint32_t run(unsigned rd=0) {
		assert (code.has_next());
		
		while (code.has_next()) {
			core.run_step();
		}
		
		code.clear();
		
		return core.regs[rd];
	}
	
	uint32_t get_reg(unsigned idx) {
		return core.regs[idx];
	}
	
	void check(bool cond) {
		if (!cond)
			throw std::runtime_error("ERROR: rule check failed");
	}
};



struct test_rule_if {
	virtual ~test_rule_if() {}
	
	virtual void randomize(Random &random) = 0;
	
	virtual void run(Executor &exec) = 0;
};


struct ADD_Comm : public test_rule_if {
	unsigned rd1, rd2, rs1, rs2;
	uint32_t a, b;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rd1 = random.unique_reg({rs1, rs2, zero});
		rd2 = random.unique_reg({rd1, rs1, rs2, zero});
		a = random.reg_val();
		b = random.reg_val();
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LI(rs2, b);
		x.code.ADD(rd1, rs1, rs2);
		x.code.ADD(rd2, rs2, rs1);
		x.run();
		x.check(x.get_reg(rd1) == x.get_reg(rd2));
	}
};


struct ADD_Split : public test_rule_if {
	unsigned rd1, rd2, rs1, rs2, rx, ry;
	uint32_t a, b;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rd1 = random.unique_reg({rs1, rs2, zero});
		rd2 = random.unique_reg({rd1, rs1, rs2, zero});
		rx = random.unique_reg({rd1, rd2, rs1, rs2, zero});
		ry = random.unique_reg({rx, rd1, rd2, rs1, rs2, zero});
		a = random.reg_val();
		b = random.reg_val();
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LI(rs2, b);
		x.code.ADD(rd1, rs1, rs2);
		
		x.code.SRLI(rx, rs2, 1);	// floor(b/2)
		x.code.ADD(rd2, rs1, rx);	// a + floor(b/2)
		
		x.code.ANDI(ry, rs2, 1);	// b % 2 == 1 ?
		x.code.ADD(ry, ry, rx);		// ceil(b/2)
		x.code.ADD(rd2, rd2, ry);
		
		x.run();
		x.check(x.get_reg(rd1) == x.get_reg(rd2));
	}
};


struct ADD_Split2 : public test_rule_if {
	unsigned rd1, rd2, rs1, rs2;
	uint32_t a, b, b_low, b_high;	
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rd1 = random.unique_reg({rs1, rs2, zero});
		rd2 = random.unique_reg({rd1, rs1, rs2, zero});
		a = random.reg_val();
		b = random.reg_val();
		b_low = b / 2;
		b_high = b % 2 == 0 ? b_low : b_low + 1;
	}
	
	void run(Executor &x) {	
		x.code.LI(rs1, a);
		x.code.LI(rs2, b);
		x.code.ADD(rd1, rs1, rs2);

		x.code.ADD(rd2, rs1, zero);
		x.code.LI(rs2, b_low);
		x.code.ADD(rd2, rd2, rs2);
		x.code.LI(rs2, b_high);
		x.code.ADD(rd2, rd2, rs2);
		
		x.run();
		x.check(x.get_reg(rd1) == x.get_reg(rd2));
	}
};


struct ADD_Change : public test_rule_if {
	unsigned rd, rs1, rs2;
	uint32_t a, b;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rd = random.unique_reg({rs1, rs2, zero});
		a = random.reg_val();
		b = random.reg_val();
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LI(rs2, b);		
		x.code.ADD(rd, rs1, rs2);
		x.run();
	
		if (b == 0 || rs2 == zero) {
			x.check(x.get_reg(rd) == x.get_reg(rs1));
		} else {
			x.check(x.get_reg(rd) != x.get_reg(rs1));
		}
	}
};


struct ADD_Assoc : public test_rule_if {
	unsigned rd1, rd2, rs1, rs2, rs3;
	uint32_t a, b, c;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rs3 = random.reg();
		rd1 = random.unique_reg({rs1, rs2, rs3, zero});
		rd2 = random.unique_reg({rd1, rs1, rs2, rs3, zero});
		a = random.reg_val();
		b = random.reg_val();
		c = random.reg_val();
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LI(rs2, b);
		x.code.LI(rs3, c);
		x.code.ADD(rd1, rs1, rs2);
		x.code.ADD(rd1, rd1, rs3);
		x.code.ADD(rd2, rs2, rs3);
		x.code.ADD(rd2, rs1, rd2);
		x.run();
		x.check(x.get_reg(rd1) == x.get_reg(rd2));
	}
};



template <unsigned N>
int align_memory_addr(int reg, int off) {
	while (((reg+off) % N) != 0)
		off = (off + 1) % 2048;
	return off;
}

template <unsigned N>
int align_memory_addr(int addr) {
	if (addr % N == 0)
		return addr;
	return addr + (N - (addr % N));
}

enum class LoadInstr {
	LB,
	LBU,
	LH,
	LHU,
	LW
};

template <LoadInstr T>
constexpr unsigned GetAlignWidth() {
	if (T == LoadInstr::LB || T == LoadInstr::LBU)
		return 1;
	if (T == LoadInstr::LH || T == LoadInstr::LHU)
		return 2;
	return 4;
}


template <LoadInstr T>
struct LX_AddrId : public test_rule_if {
	/*
		@assume R[rs1]+off1 == R[rs2]+off2
		lX rd, rs1, off1 == lX rd, rs2, off2
	 */
	unsigned rd1, rd2, rs1, rs2;
	int32_t a, b;
	int off1, off2;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.unique_reg({rs1, zero});
		rd1 = random.unique_reg({rs1, rs2, zero});
		rd2 = random.unique_reg({rd1, rs1, rs2, zero});
		a = random.reg_val(rs1);
		off1 = align_memory_addr<GetAlignWidth<T>()>(a, random.i_imm());
		off2 = random.i_imm();
	}
	
	void _LX(Executor &x, unsigned rd, unsigned rs, int off) {
		if (T == LoadInstr::LB)
			x.code.LB(rd, rs, off);
		else if (T == LoadInstr::LBU)
			x.code.LBU(rd, rs, off);
		else if (T == LoadInstr::LH)
			x.code.LH(rd, rs, off);
		else if (T == LoadInstr::LHU)
			x.code.LHU(rd, rs, off);
		else if (T == LoadInstr::LW)
			x.code.LW(rd, rs, off);
		else
			throw std::runtime_error("not implemented");
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);		
		_LX(x, rd1, rs1, off1);
		
		x.code.ADDI(rs2, rs1, off1);
		x.code.ADDI(rd2, zero, off2);
		x.code.SUB(rs2, rs2, rd2);		
		_LX(x, rd2, rs2, off2);
		
		x.run();		
		x.check(x.get_reg(rd1) == x.get_reg(rd2));
	}
};


template <unsigned N>
struct SX_LX_Id : public test_rule_if {
	/*	@assume R[rs1]+off is properly aligned
		sw rs2, rs1, off == lw rd, rs1, off		{ R[rd] == R[rs2] }
		sh rs2, rs1, off == lhu rd, rs1, off	{ R[rd] == R[rs2] }
		sb rs2, rs1, off == lbu rd, rs1, off	{ R[rd] == R[rs2] }
	 */
	static_assert (N == 1 || N == 2 || N == 4, "invalid memory width");

	unsigned rd, rs1, rs2;
	int32_t a, b;
	int off;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		rd = random.unique_reg({zero});
		a = random.reg_val(rs1);
		b = random.reg_val();
		off = align_memory_addr<N>(a, random.i_imm());
	}
	
	void run(Executor &x) {
		x.code.LI(rs2, b);
		x.code.LI(rs1, a);	// ensure that rs1 is aligned in case rs1==rs2
		if (N == 1) {
			x.code.SB(rs2, rs1, off);
			x.code.LBU(rd, rs1, off);
			x.code.ANDI(rs2, rs2, 0xff);
		} else if (N == 2) {
			x.code.SH(rs2, rs1, off);
			x.code.LHU(rd, rs1, off);
			x.code.SLLI(rs2, rs2, 16);
			x.code.SRLI(rs2, rs2, 16);
		} else if (N == 4) {
			x.code.SW(rs2, rs1, off);
			x.code.LW(rd, rs1, off);
		}
		x.run();		
		x.check(x.get_reg(rd) == x.get_reg(rs2));
	}
};


struct LW_Combine2 : public test_rule_if {
	/*
		lw rd, rs1, off == 
			lhu rx, rs1, off
			addi rs1, rs1, 2
			lhu ry, rs1, off
			slli ry, ry, 16
			or rx, rx, ry
			{ R[rd] == R[rx] }
	 */
	unsigned rd, rs1, rx, ry;
	uint32_t a;
	int off;
	
	void randomize(Random &random) {
		rs1 = random.unique_reg({zero});
		rd = random.unique_reg({rs1, zero});
		rx = random.unique_reg({rs1, rd, zero});
		ry = random.unique_reg({rs1, rd, rx, zero});
		a = random.reg_val(rs1);
		off = align_memory_addr<4>(a, random.i_imm());
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LW(rd, rs1, off);

		x.code.LHU(rx, rs1, off);		
		x.code.ADDI(rs1, rs1, 2);
		x.code.LHU(ry, rs1, off);		
		x.code.SLLI(ry, ry, 16);
		x.code.OR(rx, rx, ry);

		x.run();
		x.check(x.get_reg(rd) == x.get_reg(rx));
	}
};

struct LHU_Combine2 : public test_rule_if {
	/*
		lhu rd, rs1, off == 
			lbu rx, rs1, off
			addi rs1, rs1, 1
			lbu ry, rs1, off
			slli ry, ry, 8
			or rx, rx, ry
			{ R[rd] == R[rx] }
	 */
	unsigned rd, rs1, rx, ry;
	uint32_t a;
	int off;
	
	void randomize(Random &random) {
		rs1 = random.unique_reg({zero});
		rd = random.unique_reg({rs1, zero});
		rx = random.unique_reg({rs1, rd, zero});
		ry = random.unique_reg({rs1, rd, rx, zero});
		a = random.reg_val(rs1);
		off = align_memory_addr<2>(a, random.i_imm());
	}
	
	void run(Executor &x) {
		x.code.LI(rs1, a);
		x.code.LHU(rd, rs1, off);

		x.code.LBU(rx, rs1, off);
		x.code.ADDI(rs1, rs1, 1);
		x.code.LBU(ry, rs1, off);
		x.code.SLLI(ry, ry, 8);
		x.code.OR(rx, rx, ry);

		x.run();
		x.check(x.get_reg(rd) == x.get_reg(rx));
	}
};


template <LoadInstr T>
struct LX_ExtCheck : public test_rule_if {
	/*
		lhu rd, rs1, off
		mv rx, rd
		slli rx, rx, 16
		srli rx, rx, 16
		{ R[rd] == R[rx] }
		
		lh rd, rs1, off
		mv rx, rd
		slli rx, rx, 16
		srai rx, rx, 16
		{ R[rd] == R[rx] }
		
		use 8 bits shift for lbu and lb
	 */
	unsigned rd, rs1, rx;
	uint32_t a;
	int off;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rd = random.reg();
		rx = random.unique_reg({rd, zero});
		a = random.reg_val(rs1);
		off = align_memory_addr<GetAlignWidth<T>()>(a, random.i_imm());
	}
	
	void run(Executor &x) {
		unsigned shamt = 16;
		if (T == LoadInstr::LB || T == LoadInstr::LBU)
			shamt = 8;
	
		x.code.LI(rs1, a);
		if (T == LoadInstr::LB)
			x.code.LB(rd, rs1, off);
		else if (T == LoadInstr::LBU)
			x.code.LBU(rd, rs1, off);
		else if (T == LoadInstr::LH)
			x.code.LH(rd, rs1, off);
		else if (T == LoadInstr::LHU)
			x.code.LHU(rd, rs1, off);
		else
			throw std::runtime_error("not supported");
		x.code.MV(rx, rd);
		x.code.SLLI(rx, rx, shamt);
		if (T == LoadInstr::LB || T == LoadInstr::LH)
			x.code.SRAI(rx, rx, shamt);
		else
			x.code.SRLI(rx, rx, shamt);
		x.run();
		x.check(x.get_reg(rd) == x.get_reg(rx));
	}
};


template <unsigned N>
struct LXU_LX_Rel : public test_rule_if {
	/*
		lbu rd, rs1, off ==
			lb rx, rs1, off
			slli ry, rx, 24
			srli ry, ry, 24
			{ R[rd] *<= R[rx]; R[rd] == R[ry] }
	 */
	static_assert (N == 1 || N == 2, "unsupported");
	 
	unsigned rd, rs1, rx, ry;
	uint32_t a;
	int off;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rd = random.unique_reg({rs1, zero});
		rx = random.unique_reg({rs1, rd, zero});
		ry = random.unique_reg({rs1, rd, rx, zero});
		a = random.reg_val(rs1);
		off = align_memory_addr<N>(a, random.i_imm());
	}
	
	void run(Executor &x) {
		constexpr unsigned shamt = N == 1 ? 24 : 16;
		x.code.LI(rs1, a);
		if (N == 1) {
			x.code.LBU(rd, rs1, off);
			x.code.LB(rx, rs1, off);
		} else {
			assert (N == 2);
			x.code.LHU(rd, rs1, off);
			x.code.LH(rx, rs1, off);
		}
		x.code.SLLI(ry, rx, shamt);
		x.code.SRLI(ry, ry, shamt);

		x.run();
//		std::cout << "R[rd=" << rd << "]=" << x.get_reg(rd) << std::endl;
//		std::cout << "R[rx=" << rx << "]=" << x.get_reg(rx) << std::endl;
//		std::cout << "R[ry=" << ry << "]=" << x.get_reg(ry) << std::endl;
//		std::cout << "R[rs1=" << rs1 << "]=" << x.get_reg(rs1) << std::endl;
		
		x.check(x.get_reg(rd) <= x.get_reg(rx));
		x.check(x.get_reg(rd) == x.get_reg(ry));
	}
};


struct SW_RefCheck : public test_rule_if, public EmptyMemoryInterface {
	/*
		sw rs2, rs1, 0 => addr == R[rs1] /\ val == R[rs2]
		
		Baseline for correct implementation (otherwise we cannot ensure that address/value is not
		modified by all load/store instructions in some consistent way, e.g. apply XOR on the
		value before/after store/load).
	 */
	unsigned rs1, rs2;
	uint32_t a, b;
	uint64_t observed_addr;
	uint32_t observed_value;
	
	void randomize(Random &random) {
		rs1 = random.reg();
		rs2 = random.reg();
		a = align_memory_addr<4>(random.reg_val(rs1));
		if (rs1 == rs2)
			b = a;
		else
			b = random.reg_val(rs2);
	}
	
	void store_word(uint64_t addr, uint32_t value) {
		observed_addr = addr;
		observed_value = value;
	}
	
	struct SwitchDataMemoryInterface {
		Executor &x;
		data_memory_if *old;
		SwitchDataMemoryInterface(Executor &x, data_memory_if *new_)
			: x(x) {
			old = x.core.mem;
			x.core.mem = new_;
		}
		~SwitchDataMemoryInterface() {
			x.core.mem = old;
		}
	};
	
	void run(Executor &x) {
		SwitchDataMemoryInterface tmp_option(x, this);
		
		x.code.LI(rs2, b);
		x.code.LI(rs1, a);	// load rs1 after rs2 to ensure proper alignment (in case rs1==rs2)		
		x.code.SW(rs2, rs1, 0);
		x.run();
		
		x.check(observed_addr == a);
		x.check(observed_value == b);
	}
};




std::vector<std::shared_ptr<test_rule_if>> rules {
	std::make_shared<ADD_Comm>(),
	std::make_shared<ADD_Split>(),
	std::make_shared<ADD_Change>(),
	std::make_shared<ADD_Assoc>(),
	std::make_shared<ADD_Split2>(),
	
	std::make_shared<LX_AddrId<LoadInstr::LB>>(),
	std::make_shared<LX_AddrId<LoadInstr::LBU>>(),
	std::make_shared<LX_AddrId<LoadInstr::LH>>(),
	std::make_shared<LX_AddrId<LoadInstr::LHU>>(),
	std::make_shared<LX_AddrId<LoadInstr::LW>>(),
	std::make_shared<SX_LX_Id<1>>(),
	std::make_shared<SX_LX_Id<2>>(),
	std::make_shared<SX_LX_Id<4>>(),
	std::make_shared<LW_Combine2>(),
	std::make_shared<LHU_Combine2>(),
	std::make_shared<LX_ExtCheck<LoadInstr::LB>>(),
	std::make_shared<LX_ExtCheck<LoadInstr::LBU>>(),
	std::make_shared<LX_ExtCheck<LoadInstr::LH>>(),
	std::make_shared<LX_ExtCheck<LoadInstr::LHU>>(),
	std::make_shared<LXU_LX_Rel<1>>(),
	std::make_shared<LXU_LX_Rel<2>>(),
	std::make_shared<SW_RefCheck>(),
};


std::shared_ptr<test_rule_if> random_rule(Random &random) {
	return rules[random(rules.size())];
}


struct NoMutation : instr_mutator_if {
	bool exec(Opcode::Mapping op, ISS &core, RegFile &regs, Instruction &instr) override {
		return false;
	}
};

template <Opcode::Mapping TargetOp, typename Impl, typename NameClass>
struct OperationMutation : instr_mutator_if {
	std::string name() {
		return std::string(NameClass::Name);
	}

	bool exec(Opcode::Mapping op, ISS &core, RegFile &regs, Instruction &instr) override {
		if (op == TargetOp) {
			static_cast<Impl*>(this)->apply(core, regs, instr);
			return true;
		}
		return false;
	}
};


#define MutationClass(OPCODE, NAME) 	\
	struct MUTATION_CLASS_NAME_ ## OPCODE ## NAME { static constexpr auto Name = #OPCODE "-" #NAME; };	\
										\
	struct OPCODE ## _Mutation ## NAME : OperationMutation<Opcode::OPCODE, OPCODE ## _Mutation ## NAME, MUTATION_CLASS_NAME_ ## OPCODE ## NAME>


MutationClass(ADD, 1) {
	void apply(ISS &core, RegFile &regs, Instruction &instr) {
		regs[instr.rd()] = regs[instr.rs1()] - regs[instr.rs2()];
	}
};

MutationClass(ADD, 2) {
	void apply(ISS &core, RegFile &regs, Instruction &instr) {
		regs[instr.rd()] = regs[instr.rs1()] + regs[instr.rs2()] + 1;
	}
};

MutationClass(ADD, 3) {
	void apply(ISS &core, RegFile &regs, Instruction &instr) {
		regs[instr.rd()] = (regs[instr.rs1()] + regs[instr.rs2()]) & ((1 << 30) - 1);
	}
};

std::vector<std::shared_ptr<instr_mutator_if>> mutators {
	std::make_shared<NoMutation>(),
	std::make_shared<ADD_Mutation1>(),
	std::make_shared<ADD_Mutation2>(),
	std::make_shared<ADD_Mutation3>(),
};


int main(int argc, char **argv) {
    ISS core(0, false);
    Random random;
    RandomLazyMemory mem(random);
    Executor exec(core, random, mem);
    
    core.randomize_state();
    //core.trace = true;
    
    for (auto m : mutators) {
    	std::cout << "> check mutator: " << std::endl;
    	core.mutator = m.get();
    	
   	    for (int i=0; i<10000; ++i) {
			auto rule = random_rule(random);
			rule->randomize(random);
			rule->run(exec);
		}
    }
    
	core.show();

    return 0;
}
