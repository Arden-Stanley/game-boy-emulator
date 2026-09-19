#ifndef CTRL_H
#define CTRL_H
#include "../bus.h"
#include "../cpu.h"
#include <stdint.h>

typedef enum { CC_NZ, CC_NC, CC_Z, CC_C } Condition;

uint8_t op_call_n16(CPU *cpu, Bus *bus);
uint8_t op_call_cc_n16(CPU *cpu, Bus *bus, Condition cc);

uint8_t op_jp_hl(CPU *cpu);
uint8_t op_jp_n16(CPU *cpu, Bus *bus);
uint8_t op_jp_cc_n16(CPU *cpu, Bus *bus, Condition cc);

uint8_t op_jr_n16(CPU *cpu, Bus *bus);
uint8_t op_jr_cc_n16(CPU *cpu, Bus *bus, Condition cc);

uint8_t op_ret(CPU *cpu, Bus *bus);
uint8_t op_ret_cc(CPU *cpu, Bus *bus, Condition cc);
uint8_t op_reti(CPU *cpu, Bus *bus);
uint8_t op_rst_vec(CPU *cpu, Bus *bus, uint8_t vec);

uint8_t op_pop_af(CPU *cpu, Bus *bus);
uint8_t op_pop_r16(CPU *cpu, Bus *bus, uint16_t *reg);
uint8_t op_push_af(CPU *cpu, Bus *bus);
uint8_t op_push_r16(CPU *cpu, Bus *bus, uint16_t reg);

#endif
