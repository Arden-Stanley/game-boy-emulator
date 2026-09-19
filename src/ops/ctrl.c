#include "ctrl.h"

uint8_t op_call_n16(CPU *cpu, Bus *bus) {
  uint16_t imm = cpu_get_imm16(cpu, bus);
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->pc >> 4);
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->pc & 0xFF);
  cpu->pc = imm;
  return 6;
}

uint8_t op_call_cc_n16(CPU *cpu, Bus *bus, Condition cc) {
  switch (cc) {
  case CC_NZ:
    if (cpu_get_flag(cpu, FLAG_Z) == 0)
      return op_call_n16(cpu, bus);
    break;
  case CC_NC:
    if (cpu_get_flag(cpu, FLAG_C) == 0)
      return op_call_n16(cpu, bus);
    break;
  case CC_Z:
    if (cpu_get_flag(cpu, FLAG_Z) == 1)
      return op_call_n16(cpu, bus);
    break;
  case CC_C:
    if (cpu_get_flag(cpu, FLAG_C) == 1)
      return op_call_n16(cpu, bus);
    break;
  }
  cpu->pc += 2;
  return 3;
}

uint8_t op_jp_hl(CPU *cpu) {
  cpu->pc = cpu->hl;
  return 1;
}

uint8_t op_jp_n16(CPU *cpu, Bus *bus) {
  cpu->pc = cpu_get_imm16(cpu, bus);
  return 4;
}

uint8_t op_jp_cc_n16(CPU *cpu, Bus *bus, Condition cc) {
  switch (cc) {
  case CC_NZ:
    if (cpu_get_flag(cpu, FLAG_Z) == 0)
      return op_jp_n16(cpu, bus);
    break;
  case CC_NC:
    if (cpu_get_flag(cpu, FLAG_C) == 0)
      return op_jp_n16(cpu, bus);
    break;
  case CC_Z:
    if (cpu_get_flag(cpu, FLAG_Z) == 1)
      return op_jp_n16(cpu, bus);
    break;
  case CC_C:
    if (cpu_get_flag(cpu, FLAG_C) == 1)
      return op_jp_n16(cpu, bus);
    break;
  }
  cpu->pc += 2;
  return 3;
}

uint8_t op_jr_n16(CPU *cpu, Bus *bus) {
  int8_t offset = (int8_t)cpu_get_imm8(cpu, bus);
  cpu->pc += (int8_t)offset;
  return 3;
}

uint8_t op_jr_cc_n16(CPU *cpu, Bus *bus, Condition cc) {
  switch (cc) {
  case CC_NZ:
    if (cpu_get_flag(cpu, FLAG_Z) == 0)
      return op_jr_n16(cpu, bus);
    break;
  case CC_NC:
    if (cpu_get_flag(cpu, FLAG_C) == 0)
      return op_jr_n16(cpu, bus);
    break;
  case CC_Z:
    if (cpu_get_flag(cpu, FLAG_Z) == 1)
      return op_jr_n16(cpu, bus);
    break;
  case CC_C:
    if (cpu_get_flag(cpu, FLAG_C) == 1)
      return op_jr_n16(cpu, bus);
    break;
  }
  cpu->pc += 1;
  return 2;
}

uint8_t op_ret(CPU *cpu, Bus *bus) {
  uint8_t low_byte = bus_read8(bus, cpu->sp);
  bus_write(bus, cpu->sp, 0x00);
  cpu->sp++;
  uint8_t high_byte = bus_read8(bus, cpu->sp);
  bus_write(bus, cpu->sp, 0x00);
  cpu->sp++;
  cpu->pc = ((high_byte << 8) | (low_byte & 0x00FF));
  return 4;
}

uint8_t op_ret_cc(CPU *cpu, Bus *bus, Condition cc) {
  switch (cc) {
  case CC_NZ:
    if (cpu_get_flag(cpu, FLAG_Z) == 0)
      return op_ret(cpu, bus) + 1;
    break;
  case CC_NC:
    if (cpu_get_flag(cpu, FLAG_C) == 0)
      return op_ret(cpu, bus) + 1;
    break;
  case CC_Z:
    if (cpu_get_flag(cpu, FLAG_Z) == 1)
      return op_ret(cpu, bus) + 1;
    break;
  case CC_C:
    if (cpu_get_flag(cpu, FLAG_C) == 1)
      return op_ret(cpu, bus) + 1;
    break;
  }
  return 2;
}

uint8_t op_reti(CPU *cpu, Bus *bus) {
  op_ret(cpu, bus);
  cpu->ime = 1;
  return 4;
}

uint8_t op_rst_vec(CPU *cpu, Bus *bus, uint8_t vec) {
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->pc >> 4);
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->pc & 0xFF);
  cpu->pc = (vec & 0x00FF);
  return 4;
}

uint8_t op_pop_af(CPU *cpu, Bus *bus) {
  cpu->f = bus_read8(bus, cpu->sp);
  cpu->sp++;
  cpu->a = bus_read8(bus, cpu->sp);
  cpu->sp++;

  return 3;
}

uint8_t op_pop_r16(CPU *cpu, Bus *bus, uint16_t *reg) {
  uint8_t low_byte = bus_read8(bus, cpu->sp);
  cpu->sp++;
  uint8_t high_byte = bus_read8(bus, cpu->sp);
  cpu->sp++;
  *reg = (low_byte & 0x00FF) | (high_byte << 8);
  return 3;
}

uint8_t op_push_af(CPU *cpu, Bus *bus) {
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->a);
  cpu->sp--;
  bus_write(bus, cpu->sp, cpu->f);
  return 4;
}

uint8_t op_push_r16(CPU *cpu, Bus *bus, uint16_t reg) {
  cpu->sp--;
  bus_write(bus, cpu->sp, reg >> 8);
  cpu->sp--;
  bus_write(bus, cpu->sp, reg & 0xFF);
  return 4;
}
