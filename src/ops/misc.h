#ifndef MISC_H
#define MISC_H
#include "../bus.h"
#include "../cpu.h"
#include <stdint.h>

uint8_t op_daa(CPU *cpu);
uint8_t op_stop(CPU *cpu);

#endif
