#include "cpu.h"

#include <stdlib.h>

void cpu_set_flag(CPU *cpu, Flags flag) { cpu->f |= (1 << flag); }
void cpu_clear_flag(CPU *cpu, Flags flag) { cpu->f &= ~(1 << flag); }
uint8_t cpu_get_flag(CPU *cpu, Flags flag) { return (cpu->f >> flag) & 1; }

static void op_inc_r8(CPU *cpu, uint8_t *r) {
  if ((*r & 0x0F) == 0x0F) {
    cpu_set_flag(cpu, H);
  }
  (*r)++;
  if (*r == 0) {
    cpu_clear_flag(cpu, Z);
  }
  cpu_clear_flag(cpu, N);
}

static void op_inc_mem(CPU *cpu, Bus *bus, uint16_t addr) {
  uint8_t data = bus_read8(bus, addr);
  if ((data & 0x0F) == 0x0F) {
    cpu_set_flag(cpu, H);
  }
  data++;
  if (data == 0) {
    cpu_clear_flag(cpu, Z);
  }
  cpu_clear_flag(cpu, N);
  bus_write(bus, addr, data);
}

static void op_inc_r16(CPU *cpu, uint16_t *r) { (*r)++; }

static void op_dec_r8(CPU *cpu, uint8_t *r) {
  if ((*r & 0x0F) == 0x00) {
    cpu_set_flag(cpu, H);
  }
  (*r)--;
  if (*r == 0) {
    cpu_set_flag(cpu, Z);
  }
  cpu_set_flag(cpu, N);
}

static void op_dec_r16(uint16_t *reg) { (*reg)--; }

static void op_rlc_r8(CPU *cpu, uint8_t *r) {
  uint8_t carry_bit = (*r) >> 7;
  if (carry_bit)
    cpu_set_flag(cpu, C);
  else
    cpu_clear_flag(cpu, C);
  *r = ((*r) << 1) | carry_bit;
  if (r == &cpu->a)
    cpu_clear_flag(cpu, Z);
  else {
    if (*r == 0)
      cpu_set_flag(cpu, Z);
  }
  cpu_clear_flag(cpu, N);
  cpu_clear_flag(cpu, H);
}

static void op_rlc_mem(CPU *cpu, Bus *bus, uint16_t addr) {
  uint8_t data = bus_read8(bus, addr);
  uint8_t carry_bit = (data) >> 7;
  if (carry_bit)
    cpu_set_flag(cpu, C);
  else
    cpu_clear_flag(cpu, C);
  data = ((data) << 1) | carry_bit;
  if (data == 0) {
    cpu_set_flag(cpu, Z);
  }
  cpu_clear_flag(cpu, N);
  cpu_clear_flag(cpu, H);
  bus_write(bus, addr, data);
}

static void op_add_r16_r16(CPU *cpu, uint16_t *dest, uint16_t src) {
  *dest += src;
  if (*dest > 0x7FF) {
    cpu_set_flag(cpu, H);
  }
  if (*dest > 0xFFFF) {
    cpu_set_flag(cpu, C);
  }
  cpu_clear_flag(cpu, N);
}

uint8_t cpu_step(CPU *cpu, Bus *bus) {
  uint8_t opcode = bus_read8(bus, cpu->pc++);

  switch (opcode) {

  case 0x00: // noop
    return 1;
  case 0x01: // ld bc, n16
    cpu->bc = bus_read16(bus, cpu->pc++);
    cpu->pc++;
    return 3;
  case 0x02: // ld [bc], a
    bus_write(bus, cpu->bc, cpu->a);
    return 2;
  case 0x03: // inc bc
    op_inc_r16(cpu, &cpu->bc);
    return 2;
  case 0x04: // inc b
    op_inc_r8(cpu, &cpu->b);
    return 1;
  case 0x05: // dec b
    op_dec_r8(cpu, &cpu->b);
    return 1;
  case 0x06: // ld b, n8
    cpu->b = bus_read8(bus, cpu->pc++);
    return 2;
  case 0x07: // rlca
    op_rlc_r8(cpu, &cpu->a);
    return 1;
  case 0x08: // ld [a16], sp
  {
    uint16_t addr = bus_read16(bus, cpu->pc++);
    cpu->pc++;
    bus_write(bus, addr, cpu->sp & 0xFF);
    bus_write(bus, addr + 1, (cpu->sp >> 8));
  }
    return 5;
  case 0x09: // add hl, bc
    op_add_r16_r16(cpu, &cpu->hl, cpu->bc);
    return 2;
  case 0x0A: // ld a, [bc]
    cpu->a = bus_read8(bus, cpu->bc);
    return 2;
  case 0x0B: // dec bc
    op_dec_r16(&cpu->bc);
    return 2;
  case 0x0C: // inc c
    op_inc_r8(cpu, &cpu->c);
    return 1;
  case 0x0D: // dec c
    op_dec_r8(cpu, &cpu->c);
    return 1;
  case 0x0E: // ld c, n8
    cpu->c = bus_read8(bus, cpu->pc++);
    return 2;
  case 0x0F:
    // TODO
  default:
    printf("Invalid Opcode: %X", opcode);
    exit(EXIT_FAILURE);
  }
}
