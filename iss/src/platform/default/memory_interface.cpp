#include "memory_interface.h"

uint8_t RandomLazyMemory::get_byte(uint64_t addr) {
    if (data.find(addr) == data.end()) {
        set_byte(addr, random.byte());
    }
    return data[addr];
}
void RandomLazyMemory::set_byte(uint64_t addr, uint8_t byte) {
    data[addr] = byte;
}
uint32_t EmptyMemoryInterface::load_instr(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
int32_t EmptyMemoryInterface::load_word(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
int32_t EmptyMemoryInterface::load_half(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
int32_t EmptyMemoryInterface::load_byte(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
uint32_t EmptyMemoryInterface::load_uhalf(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
uint32_t EmptyMemoryInterface::load_ubyte(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
void EmptyMemoryInterface::store_word(uint64_t addr, uint32_t value) {
    throw std::runtime_error("not implemented");
}
void EmptyMemoryInterface::store_half(uint64_t addr, uint16_t value) {
    throw std::runtime_error("not implemented");
}
void EmptyMemoryInterface::store_byte(uint64_t addr, uint8_t value) {
    throw std::runtime_error("not implemented");
}
int32_t EmptyMemoryInterface::atomic_load_word(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
void EmptyMemoryInterface::atomic_store_word(uint64_t addr, uint32_t value) {
    throw std::runtime_error("not implemented");
}
int32_t EmptyMemoryInterface::atomic_load_reserved_word(uint64_t addr) {
    throw std::runtime_error("not implemented");
}
bool EmptyMemoryInterface::atomic_store_conditional_word(uint64_t addr, uint32_t value) {
    throw std::runtime_error("not implemented");
}
void EmptyMemoryInterface::atomic_unlock() {
    throw std::runtime_error("not implemented");
}
DefaultLoadStoreMemoryInterface::DefaultLoadStoreMemoryInterface(RandomLazyMemory &mem) : mem(mem) {}
int32_t DefaultLoadStoreMemoryInterface::load_word(uint64_t addr) {
    uint8_t b0 = mem.get_byte(addr);
    uint8_t b1 = mem.get_byte(addr + 1);
    uint8_t b2 = mem.get_byte(addr + 2);
    uint8_t b3 = mem.get_byte(addr + 3);
    return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
}
int32_t DefaultLoadStoreMemoryInterface::load_half(uint64_t addr) {
    uint8_t b0 = mem.get_byte(addr);
    uint8_t b1 = mem.get_byte(addr + 1);
    return (int16_t)((b1 << 8) | b0);
}
int32_t DefaultLoadStoreMemoryInterface::load_byte(uint64_t addr) {
    return (int8_t)mem.get_byte(addr);
}
uint32_t DefaultLoadStoreMemoryInterface::load_uhalf(uint64_t addr) {
    uint8_t b0 = mem.get_byte(addr);
    uint8_t b1 = mem.get_byte(addr + 1);
    return (b1 << 8) | b0;
}
uint32_t DefaultLoadStoreMemoryInterface::load_ubyte(uint64_t addr) {
    return mem.get_byte(addr);
}
void DefaultLoadStoreMemoryInterface::store_word(uint64_t addr, uint32_t value) {
    mem.set_byte(addr, value);
    mem.set_byte(addr + 1, value >> 8);
    mem.set_byte(addr + 2, value >> 16);
    mem.set_byte(addr + 3, value >> 24);
}
void DefaultLoadStoreMemoryInterface::store_half(uint64_t addr, uint16_t value) {
    mem.set_byte(addr, value);
    mem.set_byte(addr + 1, value >> 8);
}
void DefaultLoadStoreMemoryInterface::store_byte(uint64_t addr, uint8_t value) {
    mem.set_byte(addr, value);
}