#include "ctrl.h"

uint8_t op_call_n16(CPU *cpu, Bus *bus) {
  uint16_t imm = cpu_get_imm16(cpu, bus);
  cpu->pc++;
  bus_write(bus, cpu->sp--, cpu->pc >> 4);
  bus_write(bus, cpu->sp--, cpu->pc & 0xFF);
  cpu->pc = imm;
  return 6;
}
