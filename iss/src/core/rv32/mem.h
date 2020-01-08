#pragma once

#include "core/common/dmi.h"
#include "iss.h"

namespace rv32 {

struct MemoryInterface : public instr_memory_if, public data_memory_if {
	uint64_t lr_addr = 0;
	uint64_t tohost_addr = 0;

	// optionally add DMI ranges for optimization
	std::vector<MemoryDMI> dmi_ranges;
	
	MemoryInterface(uint64_t tohost_addr)
		: tohost_addr(tohost_addr) {
	}

	template <typename T>
	inline T _load_data(uint64_t addr) {
		for (auto &e : dmi_ranges) {
			if (e.contains<T>(addr)) {
				return e.load<T>(addr);
			}
		}

		throw std::runtime_error("load address: " + std::to_string(addr));
		throw ExitNotification(EXIT_LOAD_ADDRESS);
	}

	template <typename T>
	inline void _store_data(uint64_t addr, T value) {
		if (addr == tohost_addr) {
			throw ExitNotification(EXIT_TOHOST);
		}
	
		for (auto &e : dmi_ranges) {
			if (e.contains<T>(addr)) {
				e.store(addr, value);
				return;
			}
		}
		
		throw std::runtime_error("store address: " + std::to_string(addr));
		throw ExitNotification(EXIT_STORE_ADDRESS);
	}

	uint32_t load_instr(uint64_t addr) {
		return _load_data<uint32_t>(addr);
	}

	int32_t load_word(uint64_t addr) {
		return _load_data<int32_t>(addr);
	}
	int32_t load_half(uint64_t addr) {
		return _load_data<int16_t>(addr);
	}
	int32_t load_byte(uint64_t addr) {
		return _load_data<int8_t>(addr);
	}
	uint32_t load_uhalf(uint64_t addr) {
		return _load_data<uint16_t>(addr);
	}
	uint32_t load_ubyte(uint64_t addr) {
		return _load_data<uint8_t>(addr);
	}

	void store_word(uint64_t addr, uint32_t value) {
		_store_data(addr, value);
	}
	void store_half(uint64_t addr, uint16_t value) {
		_store_data(addr, value);
	}
	void store_byte(uint64_t addr, uint8_t value) {
		_store_data(addr, value);
	}

	virtual int32_t atomic_load_word(uint64_t addr) {
		return load_word(addr);
	}
	virtual void atomic_store_word(uint64_t addr, uint32_t value) {
		store_word(addr, value);
	}
	virtual int32_t atomic_load_reserved_word(uint64_t addr) {
		lr_addr = addr;
		return load_word(addr);
	}
	virtual bool atomic_store_conditional_word(uint64_t addr, uint32_t value) {
		if (addr == lr_addr) {
			store_word(addr, value);
			return true;
		}
		return false;
	}
	virtual void atomic_unlock() {
	}
};

}  // namespace rv32
