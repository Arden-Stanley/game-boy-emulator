#include "alu.h"

uint8_t op_adc_a_r8(CPU *cpu, uint8_t val) {
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->a & 0x0F) + (val & 0x0F) + flag > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = flag + cpu->a + val;
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + flag + val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 1;
}

uint8_t op_adc_a_mhl(CPU *cpu, Bus *bus) {
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);

  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->a & 0x0F) + (bus_read8(bus, cpu->hl) & 0x0F) + flag > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = flag + cpu->a + bus_read8(bus, cpu->hl);
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + flag + bus_read8(bus, cpu->hl);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_adc_a_n8(CPU *cpu, Bus *bus) {
  uint8_t val = cpu_get_imm8(cpu, bus);
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->a & 0x0F) + (val & 0x0F) + cpu_get_flag(cpu, FLAG_C) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = cpu_get_flag(cpu, FLAG_C) + cpu->a + val;
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + flag + val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_add_a_r8(CPU *cpu, uint8_t val) {
  if ((cpu->a & 0x0F) + (val & 0x0F) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = cpu->a + val;
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 0);

  return 1;
}

uint8_t op_add_a_mhl(CPU *cpu, Bus *bus) {
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->a & 0x0F) + (bus_read8(bus, cpu->hl) & 0x0F) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = cpu->a + bus_read8(bus, cpu->hl);
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + bus_read8(bus, cpu->hl);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_add_a_n8(CPU *cpu, Bus *bus) {
  uint8_t val = cpu_get_imm8(cpu, bus);
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->a & 0x0F) + (val & 0x0F) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = cpu->a + val;
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a + val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_add_hl_r16(CPU *cpu, uint16_t val) {
  if ((cpu->hl & 0x0FFF) + (val & 0x0FFF) > 0x0FFF)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  cpu_set_flag(cpu, FLAG_N, 0);

  uint32_t sum = cpu->hl + val;
  if (sum > 0xFFFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->hl = cpu->hl + val;
  return 2;
}

uint8_t op_add_hl_sp(CPU *cpu) {
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->hl & 0x0FFF) + (cpu->sp & 0x0FFF) > 0x0FFF)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint32_t sum = cpu->hl + cpu->sp;
  if (sum > 0xFFFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->hl = cpu->hl + cpu->sp;
  return 2;
}

uint8_t op_add_sp_e8(CPU *cpu, Bus *bus) {
  int8_t val = (int8_t)cpu_get_imm8(cpu, bus);
  cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_N, 0);

  if ((cpu->sp & 0x0F) + ((uint8_t)val & 0x0F) > 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  uint16_t sum = (cpu->sp & 0xFF) + (uint8_t)val;
  if (sum > 0xFF)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->sp = cpu->sp + val;
  return 4;
}

uint8_t op_cp_a_r8(CPU *cpu, uint8_t val) {
  uint8_t diff = cpu->a - val;
  if (diff == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 1);

  if ((cpu->a & 0x0F) < (val & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  return 1;
}

uint8_t op_cp_a_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t diff = cpu->a - val;
  if (diff == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 1);

  if ((cpu->a & 0x0F) < (val & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  return 2;
}

uint8_t op_cp_a_n8(CPU *cpu, Bus *bus) {
  uint8_t val = cpu_get_imm8(cpu, bus);
  uint8_t diff = cpu->a - val;
  if (diff == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 1);

  if ((cpu->a & 0x0F) < (val & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  return 2;
}

uint8_t op_dec_r8(CPU *cpu, uint8_t *reg) {
  cpu_set_flag(cpu, FLAG_N, 1);

  if (((*reg) & 0x0F) == 0x00)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  *reg = (*reg) - 1;
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 1;
}

uint8_t op_dec_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  if ((val & 0x0F) == 0x00)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  val--;
  bus_write(bus, cpu->hl, val);
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 1);

  return 3;
}

uint8_t op_dec_r16(uint16_t *reg) {
  *reg = (*reg) - 1;
  return 2;
}

uint8_t op_dec_sp(CPU *cpu) {
  cpu->sp = cpu->sp - 1;
  return 2;
}

uint8_t op_inc_r8(CPU *cpu, uint8_t *reg) {
  uint8_t orig_val = *reg;
  *reg = (*reg) + 1;
  if (*reg == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 0);

  if (((orig_val) & 0x0F) == 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  return 1;
}

uint8_t op_inc_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  uint8_t orig_val = val;
  val++;
  if (val == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 0);

  if ((orig_val & 0x0F) == 0x0F)
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  bus_write(bus, cpu->hl, val);
  return 3;
}

uint8_t op_inc_r16(uint16_t *reg) {
  *reg = (*reg) + 1;
  return 2;
}

uint8_t op_inc_sp(CPU *cpu) {
  cpu->sp++;
  return 2;
}

uint8_t op_sbc_a_r8(CPU *cpu, uint8_t val) {
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);
  cpu_set_flag(cpu, FLAG_N, 1);

  if ((flag & 0x0F) + (val & 0x0F) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if ((val + flag) > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a - (flag + val);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 1;
}

uint8_t op_sbc_a_mhl(CPU *cpu, Bus *bus) {
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu_set_flag(cpu, FLAG_N, 1);

  if (((flag & 0x0F) + (val & 0x0F)) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val + flag > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a - (flag + val);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_sbc_a_n8(CPU *cpu, Bus *bus) {
  uint8_t flag = cpu_get_flag(cpu, FLAG_C);
  uint8_t val = cpu_get_imm8(cpu, bus);
  cpu_set_flag(cpu, FLAG_N, 1);

  if ((flag + (val & 0x0F)) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if ((val + flag) > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a - (flag + val);
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_sub_a_r8(CPU *cpu, uint8_t val) {
  if ((val & 0x0F) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a - val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  cpu_set_flag(cpu, FLAG_N, 1);

  return 1;
}

uint8_t op_sub_a_mhl(CPU *cpu, Bus *bus) {
  uint8_t val = bus_read8(bus, cpu->hl);
  cpu_set_flag(cpu, FLAG_N, 1);

  if ((val & 0x0F) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);

  cpu->a = cpu->a - val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_sub_a_n8(CPU *cpu, Bus *bus) {
  uint8_t val = cpu_get_imm8(cpu, bus);
  cpu_set_flag(cpu, FLAG_N, 1);

  if ((val & 0x0F) > (cpu->a & 0x0F))
    cpu_set_flag(cpu, FLAG_H, 1);
  else
    cpu_set_flag(cpu, FLAG_H, 0);

  if (val > cpu->a)
    cpu_set_flag(cpu, FLAG_C, 1);
  else
    cpu_set_flag(cpu, FLAG_C, 0);
  cpu->a = cpu->a - val;
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);

  return 2;
}

uint8_t op_ccf(CPU *cpu) {
  uint8_t c = cpu_get_flag(cpu, FLAG_C) ^ 1;
  cpu_set_flag(cpu, FLAG_C, c);
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_scf(CPU *cpu) {
  cpu_set_flag(cpu, FLAG_N, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  cpu_set_flag(cpu, FLAG_C, 1);
  return 1;
}
