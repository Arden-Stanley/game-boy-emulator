#include "ld.h"

uint8_t op_ld_r8_r8(uint8_t *dest, uint8_t src) {
  *dest = src;
  return 1;
}

uint8_t op_ld_r8_n8(CPU *cpu, Bus *bus, uint8_t *dest) {
  *dest = cpu_get_imm8(cpu, bus);
  return 2;
}
uint8_t op_ld_r16_n16(CPU *cpu, Bus *bus, uint16_t *dest) {
  *dest = cpu_get_imm16(cpu, bus);
  return 3;
}
uint8_t op_ld_mhl_r8(CPU *cpu, Bus *bus, uint8_t src) {
  bus_write(bus, cpu->hl, src);
  return 2;
}
uint8_t op_ld_mhl_n8(CPU *cpu, Bus *bus) {
  bus_write(bus, cpu->hl, cpu_get_imm8(cpu, bus));
  return 3;
}
uint8_t op_ld_r8_mhl(CPU *cpu, Bus *bus, uint8_t *dest) {
  *dest = bus_read8(bus, cpu->hl);
  return 2;
}
uint8_t op_ld_mr16_a(CPU *cpu, Bus *bus, uint16_t addr) {
  bus_write(bus, addr, cpu->a);
  return 2;
}
uint8_t op_ld_mn16_a(CPU *cpu, Bus *bus) {
  bus_write(bus, cpu_get_imm16(cpu, bus), cpu->a);
  return 4;
}
uint8_t op_ldh_mn16_a(CPU *cpu, Bus *bus) {
  uint16_t addr = ((0xFF00) | cpu_get_imm8(cpu, bus));
  bus_write(bus, addr, cpu->a);
  return 3;
}
uint8_t op_ldh_mc_a(CPU *cpu, Bus *bus) {
  uint16_t addr = ((0xFF00) | cpu->c);
  bus_write(bus, addr, cpu->a);
  return 2;
}

uint8_t op_ld_a_mr16(CPU *cpu, Bus *bus, uint16_t addr) {
  cpu->a = bus_read8(bus, addr);
  return 2;
}
uint8_t op_ld_a_mn16(CPU *cpu, Bus *bus) {
  cpu->a = bus_read8(bus, cpu_get_imm16(cpu, bus));
  return 4;
}
uint8_t op_ldh_a_mn16(CPU *cpu, Bus *bus) {
  uint16_t addr = ((0xFF00) | cpu_get_imm8(cpu, bus));
  cpu->a = bus_read8(bus, addr);
  return 3;
}
uint8_t op_ldh_a_mc(CPU *cpu, Bus *bus) {
  uint16_t addr = ((0xFF00) | cpu->c);
  cpu->a = bus_read8(bus, addr);
  return 2;
}
uint8_t op_ld_mhli_a(CPU *cpu, Bus *bus) {
  bus_write(bus, cpu->hl, cpu->a);
  cpu->hl++;
  return 2;
}
uint8_t op_ld_mhld_a(CPU *cpu, Bus *bus) {
  bus_write(bus, cpu->hl, cpu->a);
  cpu->hl--;
  return 2;
}
uint8_t op_ld_a_mhld(CPU *cpu, Bus *bus) {
  cpu->a = bus_read8(bus, cpu->hl);
  cpu->hl--;
  return 2;
}
uint8_t op_ld_a_mhli(CPU *cpu, Bus *bus) {
  cpu->a = bus_read8(bus, cpu->hl);
  cpu->hl++;
  return 2;
}

uint8_t op_ld_sp_n16(CPU *cpu, Bus *bus) {
  cpu->sp = cpu_get_imm16(cpu, bus);
  return 3;
}
uint8_t op_ld_mn16_sp(CPU *cpu, Bus *bus) {
  uint16_t addr = cpu_get_imm16(cpu, bus);
  bus_write(bus, addr, cpu->sp & 0xFF);
  bus_write(bus, addr + 1, (cpu->sp >> 8));
  return 5;
}
uint8_t op_ld_hl_spe8(CPU *cpu, Bus *bus) {
  int8_t offset = (int8_t)cpu_get_imm8(cpu, bus);
  uint16_t val = cpu->sp + (int8_t)offset;
  cpu->hl = val;
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((((uint8_t)offset & 0x0F) + (cpu->sp & 0x0F)) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);

  uint16_t temp = ((uint8_t)offset + cpu->sp);
  if (temp > 0x00FF)
    cpu_set_flag(cpu, FLAG_C, 1);

  return 3;
}
uint8_t op_ld_sp_hl(CPU *cpu) {
  cpu->sp = cpu->hl;
  return 2;
}
