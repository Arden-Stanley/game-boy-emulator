#include "misc.h"

uint8_t op_daa(CPU *cpu) {
  uint8_t adj = 0;
  if (cpu_get_flag(cpu, FLAG_N)) {
    if (cpu_get_flag(cpu, FLAG_H)) {
      adj += 0x6;
    }
    if (cpu_get_flag(cpu, FLAG_C)) {
      adj += 0x60;
    }
    cpu->a -= adj;
  } else {
    if (cpu_get_flag(cpu, FLAG_H) | ((cpu->a & 0xF) > 0x9)) {
      adj += 0x6;
    }
    if (cpu_get_flag(cpu, FLAG_C) | (cpu->a > 0x99)) {
      adj += 0x60;
      cpu_set_flag(cpu, FLAG_C, 1);
    }
    cpu->a += adj;
  }
  if (cpu->a == 0)
    cpu_set_flag(cpu, FLAG_Z, 1);
  else
    cpu_set_flag(cpu, FLAG_Z, 0);
  cpu_set_flag(cpu, FLAG_H, 0);
  return 1;
}

uint8_t op_stop(CPU *cpu) {
  cpu->pc += 1;
  return 0;
}
