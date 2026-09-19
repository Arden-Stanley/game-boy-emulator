#include "itrpt.h"

uint8_t op_di(CPU *cpu) {
  cpu->ime = 0;
  cpu->enable_intrpt = 0;
  return 1;
}

uint8_t op_ei(CPU *cpu) {
  cpu->enable_intrpt = 1;
  return 1;
}

uint8_t op_halt(CPU *cpu, Bus *bus) {
  if (cpu->ime == 1) {
    cpu->halted = 1;
  } else if (bus_read8(bus, IF) == 0) {
    cpu->halted = 1;
  } else {
    cpu->repeat = 1;
  }
  return 1;
}
