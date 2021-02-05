#pragma once
#include "core/rv32/elf_loader.h"
#include "core/rv32/iss.h"
#include "core/rv32/mem.h"
#include "core/rv32/mem_if.h"
#include "random.h"

using namespace rv32;
struct EmptyMemoryInterface : public instr_memory_if, public data_memory_if {
    uint32_t load_instr(uint64_t addr);
    int32_t load_word(uint64_t addr);
    int32_t load_half(uint64_t addr);
    int32_t load_byte(uint64_t addr);
    uint32_t load_uhalf(uint64_t addr);
    uint32_t load_ubyte(uint64_t addr);
    void store_word(uint64_t addr, uint32_t value);
    void store_half(uint64_t addr, uint16_t value);
    void store_byte(uint64_t addr, uint8_t value);
    virtual int32_t atomic_load_word(uint64_t addr);
    virtual void atomic_store_word(uint64_t addr, uint32_t value);
    virtual int32_t atomic_load_reserved_word(uint64_t addr);
    virtual bool atomic_store_conditional_word(uint64_t addr, uint32_t value);
    virtual void atomic_unlock();
};
struct RandomLazyMemory {
    Random &random;
    std::unordered_map<uint64_t, uint8_t> data;
    RandomLazyMemory(Random &random);
    uint8_t get_byte(uint64_t addr);
    void set_byte(uint64_t addr, uint8_t byte);
};
struct DefaultLoadStoreMemoryInterface : public EmptyMemoryInterface {
    RandomLazyMemory &mem;
    DefaultLoadStoreMemoryInterface(RandomLazyMemory &mem);
    int32_t load_word(uint64_t addr);
    int32_t load_half(uint64_t addr);
    int32_t load_byte(uint64_t addr);
    uint32_t load_uhalf(uint64_t addr);
    uint32_t load_ubyte(uint64_t addr);
    void store_word(uint64_t addr, uint32_t value);
    void store_half(uint64_t addr, uint16_t value);
    void store_byte(uint64_t addr, uint8_t value);
};
