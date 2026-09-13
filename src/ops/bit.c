#include "bit.h"

uint8_t op_and_a_r8(CPU *cpu, uint8_t val) {
  cpu->a = cpu->a & val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 1);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 1;
}

uint8_t op_and_a_mhl(CPU *cpu, Bus *bus) {
  cpu->a = cpu->a & bus_read8(bus, cpu->hl);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 1);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_and_a_n8(CPU *cpu, Bus *bus) {
  cpu->a = cpu->a & cpu_get_imm8(cpu, bus);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 1);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_cpl(CPU *cpu) {
  cpu->a = ~(cpu->a);
  cpu_set_flag(cpu, FLAG_N, 1);
  cpu_set_flag(cpu, FLAG_H, 1);
  return 1;
}

uint8_t op_or_a_r8(CPU *cpu, uint8_t val) {
  cpu->a = cpu->a | val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 1;
}

uint8_t op_or_a_mhl(CPU *cpu, Bus *bus) {
  cpu->a = cpu->a | bus_read8(bus, cpu->hl);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_or_a_n8(CPU *cpu, Bus *bus) {
  cpu->a = cpu->a | cpu_get_imm8(cpu, bus);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_xor_a_r8(CPU *cpu, uint8_t val) {
  cpu->a = cpu->a ^ val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 1;
}

uint8_t op_xor_a_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu->a = cpu->a ^ val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_xor_a_n8(CPU *cpu, Bus *bus) {
  uint8_t val = cpu_get_imm8(cpu, bus);
  cpu->a = cpu->a ^ val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_bit_u3_r8(CPU *cpu, uint8_t idx, uint8_t val) {
  idx &= 0x07;
  uint8_t test = val & (1 << idx);
  if (test == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 1);
  return 2;
}

uint8_t op_bit_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx) {
  uint8_t val = bus_read8(bus, cpu->hl);
  idx &= 0x07;
  uint8_t test = val & (1 << idx);
  if (test == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 1);
  return 3;
}

uint8_t op_res_u3_r8(uint8_t idx, uint8_t *reg) {
  idx &= 0x07;
  *reg = (*reg) & ~(1 << idx);
  return 2;
}

uint8_t op_res_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx) {
  idx &= 0x07;
  uint8_t val = bus_read8(bus, cpu->hl);
  val = val & ~(1 << idx);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_set_u3_r8(uint8_t idx, uint8_t *reg) {
  idx &= 0x07;
  *reg = (*reg) | (1 << idx);
  return 2;
}

uint8_t op_set_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx) {
  idx &= 0x07;
  uint8_t val = bus_read8(bus, cpu->hl);
  val = val | (1 << idx);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_rl_r8(CPU *cpu, uint8_t *reg) {
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, (*reg) >> 6);
  *reg = (*reg) << 1;
  *reg = (*reg) | carry;
  if ((*reg) == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_rl_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, (val) >> 6);
  val = (val) << 1;
  val = (val) | carry;
  if ((val) == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_rla(CPU *cpu) {
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, (cpu->a) >> 6);
  cpu->a = (cpu->a) << 1;
  cpu->a = (cpu->a) | carry;
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_rlc_r8(CPU *cpu, uint8_t *reg) {
  uint8_t carry = ((*reg) >> 6);
  cpu_set_flag(cpu, FLAG_C, carry);
  *reg = (*reg) << 1;
  *reg = (*reg) | carry;
  if ((*reg) == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_rlc_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t carry = (val >> 6);
  cpu_set_flag(cpu, FLAG_C, carry);
  val = (val) << 1;
  val = val | carry;
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 4;
}

uint8_t op_rlca(CPU *cpu) {
  uint8_t carry = ((cpu->a) >> 6);
  cpu_set_flag(cpu, FLAG_C, carry);
  cpu->a = cpu->a << 1;
  cpu->a = cpu->a | carry;
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_rr_r8(CPU *cpu, uint8_t *reg) {
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, ((*reg) & 0x01));
  *reg = (*reg) >> 1;
  *reg = (*reg) | (carry << 7);
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_rr_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, (val & 0x01));
  val = val >> 1;
  val = val | (carry << 7);
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_rra(CPU *cpu) {
  uint8_t carry = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_C, (cpu->a & 0x01));
  cpu->a = cpu->a >> 1;
  cpu->a = cpu->a | (carry << 7);
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_rrc_r8(CPU *cpu, uint8_t *reg) {
  uint8_t carry = (*reg) & 0x01;
  cpu_set_flag(cpu, FLAG_C, (carry));
  *reg = (*reg) >> 1;
  *reg = (*reg) | (carry << 7);
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_rrc_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t carry = val & 0x01;
  cpu_set_flag(cpu, FLAG_C, (carry));
  val = val >> 1;
  val = val | (carry << 7);
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_rrca(CPU *cpu) {
  uint8_t carry = cpu->a & 0x01;
  cpu_set_flag(cpu, FLAG_C, (carry));
  cpu->a = cpu->a >> 1;
  cpu->a = cpu->a | (carry << 7);
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_sla_r8(CPU *cpu, uint8_t *reg) {
  cpu_set_flag(cpu, FLAG_C, (*reg) >> 6);
  *reg = (*reg) << 1;
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_sla_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu_set_flag(cpu, FLAG_C, val >> 6);
  val = val << 1;
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_sra_r8(CPU *cpu, uint8_t *reg) {
  cpu_set_flag(cpu, FLAG_C, (*reg) & 0x01);
  *reg = ((*reg) >> 1) | ((*reg) & 0x80);
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_sra_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu_set_flag(cpu, FLAG_C, val & 0x01);
  val = (val >> 1) | (val & 0x80);
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_srl_r8(CPU *cpu, uint8_t *reg) {
  cpu_set_flag(cpu, FLAG_C, (*reg) & 0x01);
  *reg = (*reg) >> 1;
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 2;
}

uint8_t op_srl_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu_set_flag(cpu, FLAG_C, val & 0x01);
  val = val >> 1;
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}

uint8_t op_swap_r8(CPU *cpu, uint8_t *reg) {
  uint8_t lower = (*reg) & 0x0F;
  uint8_t higher = (*reg) >> 4;
  uint8_t new_byte = (lower << 4) | higher;
  *reg = new_byte;
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  return 2;
}

uint8_t op_swap_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t lower = val & 0x0F;
  uint8_t higher = val >> 4;
  uint8_t new_byte = (lower << 4) | higher;
  val = new_byte;
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 0);
  bus_write(bus, cpu->hl, val);
  return 4;
}
