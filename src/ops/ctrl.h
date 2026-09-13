#ifndef CTRL_H
#define CTRL_H
#include "../bus.h"
#include "../cpu.h"
#include <stdint.h>

uint8_t op_call_n16(CPU *cpu, Bus *bus);

#endif
