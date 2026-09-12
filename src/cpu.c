#include "cpu.h"

void cpu_set_flag(CPU *cpu, Flags flag, bool val) {
  cpu->f = (cpu->f & ~(1 << flag)) | (val << flag);
}
uint8_t cpu_get_flag(CPU *cpu, Flags flag) { return (cpu->f >> flag) & 1; }
uint8_t cpu_get_imm8(CPU *cpu, Bus *bus) { return bus_read8(bus, cpu->pc++); }
uint16_t cpu_get_imm16(CPU *cpu, Bus *bus) {
  uint16_t data = bus_read16(bus, cpu->pc++);
  cpu->pc++;
  return data;
}

uint8_t cpu_step(CPU *cpu, Bus *bus) {
  uint8_t opcode = bus_read8(bus, cpu->pc++);

  switch (opcode) {
  case 0x00:
    return 1;
  default:
    printf("Invalid Opcode: %X", opcode);
    exit(EXIT_FAILURE);
  }
}
