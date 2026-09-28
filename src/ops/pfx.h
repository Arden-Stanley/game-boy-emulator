#ifndef PFX_H
#define PFX_H
#include "../bus.h"
#include "../cpu.h"
#include "bit.h"
#include <stdint.h>
#include <stdio.h>

uint8_t op_pfx_decode(CPU *cpu, Bus *bus);

#endif
