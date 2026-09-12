#ifndef CPU_H
#define CPU_H
#include "bus.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  union {
    uint16_t af;
    struct {
      uint8_t f;
      uint8_t a;
    };
  };
  union {
    uint16_t bc;
    struct {
      uint8_t c;
      uint8_t b;
    };
  };
  union {
    uint16_t de;
    struct {
      uint8_t e;
      uint8_t d;
    };
  };
  union {
    uint16_t hl;
    struct {
      uint8_t l;
      uint8_t h;
    };
  };
  uint16_t sp;
  uint16_t pc;
} CPU;

typedef enum { FLAG_Z = 0, FLAG_N = 1, FLAG_H = 2, FLAG_C = 3 } Flags;

void cpu_set_flag(CPU *cpu, Flags flag, bool val);
uint8_t cpu_get_flag(CPU *cpu, Flags flag);
uint8_t cpu_get_imm8(CPU *cpu, Bus *bus);
uint16_t cpu_get_imm16(CPU *cpu, Bus *bus);

uint8_t cpu_step(CPU *cpu, Bus *bus);

#endif
