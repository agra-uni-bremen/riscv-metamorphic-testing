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



uint32_t ADD(unsigned rd, unsigned rs1, unsigned rs2) {
	return (rs2 << 20) | (rs1 << 15) | (rd << 7) | 0b0110011;
}


struct test_rule_if {
	virtual ~test_rule_if() {}
	
	virtual void run(ISS &core) = 0;
};


struct AddRule1 : public EmptyMemoryInterface, test_rule_if {
	// a + b == b + a
	unsigned idx = 0;
	std::vector<uint32_t> code;
	
	unsigned rd1 = 1;
	unsigned rd2 = 2;
	
	AddRule1() {
		code.push_back(ADD(rd1, 3, 4));
		code.push_back(ADD(rd2, 4, 3));
	}

	uint32_t load_instr(uint64_t addr) {
		return code[idx++];
	}
	
	void run(ISS &core) override {
		core.instr_mem = this;
		
		while (idx < code.size()) {
			core.run_step();
		}
		
		if (core.regs[rd1] != core.regs[rd2]) {
			throw std::runtime_error("error");
		}
	}
};



struct AddRule2 : public EmptyMemoryInterface, test_rule_if {
	// a + b == a + ceil(b/2) + floor(b/2)
	unsigned idx = 0;
	std::vector<uint32_t> code;

	uint32_t load_instr(uint64_t addr) {
		return code[idx++];
	}
	
	void run(ISS &core) override {
		auto rs1 = (rand() % 27) + 5;
		auto rs2 = (rand() % 27) + 5;
		auto rd1 = 1;
		auto rd2 = 2;
		auto rx  = 3;
		auto ry  = 4;
	
		code.push_back(ADD(rd1, rs1, rs2));
		code.push_back(ADD(rd2, rs1, rx));
		code.push_back(ADD(rd2, rd2, ry));
		
		uint32_t b = core.regs[rs2];
		
		core.regs[rx] = b % 2 == 0 ? b / 2 : b / 2 + 1;
		core.regs[ry] = b / 2;
		
	
		core.instr_mem = this;
		
		while (idx < code.size()) {
			core.run_step();
		}
		
		
		if (core.regs[rd1] != core.regs[rd2]) {
			throw std::runtime_error("error");
		}
	}
};



struct AddRule3 : public EmptyMemoryInterface, test_rule_if {
	// a + b == a if b == 0
	// a + b != a if b != 0
	unsigned idx = 0;
	std::vector<uint32_t> code;

	uint32_t load_instr(uint64_t addr) {
		return code[idx++];
	}
	
	void run(ISS &core) override {
		auto rs1 = rand() % 32;
		auto rs2 = rand() % 32;
		auto rd  = rand() % 32;
	
		code.push_back(ADD(rd, rs1, rs2));
		
		auto a = core.regs[rs1];
		auto b = core.regs[rs2];
		
	
		core.instr_mem = this;
		
		while (idx < code.size()) {
			core.run_step();
		}
		
		
		if (b == 0) {
			if (core.regs[rd] != a)
				throw std::runtime_error("error");
		} else {
			if (core.regs[rd] == a)
				throw std::runtime_error("error");
		}
	}
};


std::shared_ptr<test_rule_if> random_rule() {
	switch (rand() % 2) {
		case 0:
			return std::make_shared<AddRule1>();
			
		case 1:
			return std::make_shared<AddRule2>();
			
		case 2:
			return std::make_shared<AddRule3>();
			
		default:
			throw std::runtime_error("assert false");
	}
}


int main(int argc, char **argv) {
    ISS core(0, false);
    
    core.randomize_state();
    
    for (int i=0; i<10000; ++i) {
		auto rule = random_rule();
		rule->run(core);
    }
    
	core.show();

    return 0;
}
