#include "cpu.h"
#include "ops/alu.h"
#include "ops/bit.h"
#include "ops/ld.h"

void cpu_set_flag(CPU *cpu, Flags flag, bool val) {
  cpu->f = (cpu->f & ~(1 << flag)) | (val << flag);
}
uint8_t cpu_get_flag(CPU *cpu, Flags flag) { return (cpu->f >> flag) & 1; }
uint8_t cpu_get_imm8(CPU *cpu, Bus *bus) { return bus_read8(bus, cpu->pc++); }
uint16_t cpu_get_imm16(CPU *cpu, Bus *bus) {
  uint8_t low_byte = bus_read8(bus, cpu->pc++);
  uint8_t high_byte = bus_read8(bus, cpu->pc++);
  uint16_t data = (low_byte & 0x00FF) | (high_byte << 8);
  return data;
}

uint8_t cpu_step(CPU *cpu, Bus *bus) {
  uint8_t opcode = bus_read8(bus, cpu->pc++);
  printf("Servicing Opcode: %02X\n", opcode);

  switch (opcode) {
  case 0x00:
    return 1;
  case 0x01:
    return op_ld_r16_n16(cpu, bus, &cpu->bc);
  case 0x02:
    return op_ld_mr16_a(cpu, bus, cpu->bc);
  default:
    printf("Invalid Opcode: %X", opcode);
    exit(EXIT_FAILURE);
  }
}
