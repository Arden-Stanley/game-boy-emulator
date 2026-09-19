#ifndef ITRPT_H
#define ITRPT_H
#include "../bus.h"
#include "../cpu.h"

uint8_t op_di(CPU *cpu);
uint8_t op_ei(CPU *cpu);
uint8_t op_halt(CPU *cpu, Bus *bus);

#endif
