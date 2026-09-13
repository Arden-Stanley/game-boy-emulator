#ifndef BIT_H
#define BIT_H
#include "../bus.h"
#include "../cpu.h"

uint8_t op_and_a_r8(CPU *cpu, uint8_t val);
uint8_t op_and_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_and_a_n8(CPU *cpu, Bus *bus);

uint8_t op_cpl(CPU *cpu);

uint8_t op_or_a_r8(CPU *cpu, uint8_t val);
uint8_t op_or_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_or_a_n8(CPU *cpu, Bus *bus);

uint8_t op_xor_a_r8(CPU *cpu, uint8_t val);
uint8_t op_xor_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_xor_a_n8(CPU *cpu, Bus *bus);

uint8_t op_bit_u3_r8(CPU *cpu, uint8_t idx, uint8_t val);
uint8_t op_bit_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx);

uint8_t op_res_u3_r8(uint8_t idx, uint8_t *reg);
uint8_t op_res_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx);

uint8_t op_set_u3_r8(uint8_t idx, uint8_t *reg);
uint8_t op_set_u3_mhl(CPU *cpu, Bus *bus, uint8_t idx);

uint8_t op_rl_r8(CPU *cpu, uint8_t *reg);
uint8_t op_rl_mhl(CPU *cpu, Bus *bus);
uint8_t op_rla(CPU *cpu);

uint8_t op_rlc_r8(CPU *cpu, uint8_t *reg);
uint8_t op_rlc_mhl(CPU *cpu, Bus *bus);
uint8_t op_rlca(CPU *cpu);

uint8_t op_rr_r8(CPU *cpu, uint8_t *reg);
uint8_t op_rr_mhl(CPU *cpu, Bus *bus);
uint8_t op_rra(CPU *cpu);

uint8_t op_rrc_r8(CPU *cpu, uint8_t *reg);
uint8_t op_rrc_mhl(CPU *cpu, Bus *bus);
uint8_t op_rrca(CPU *cpu);

uint8_t op_sla_r8(CPU *cpu, uint8_t *reg);
uint8_t op_sla_mhl(CPU *cpu, Bus *bus);

uint8_t op_sra_r8(CPU *cpu, uint8_t *reg);
uint8_t op_sra_mhl(CPU *cpu, Bus *bus);

uint8_t op_srl_r8(CPU *cpu, uint8_t *reg);
uint8_t op_srl_mhl(CPU *cpu, Bus *bus);

uint8_t op_swap_r8(CPU *cpu, uint8_t *reg);
uint8_t op_swap_mhl(CPU *cpu, Bus *bus);

#endif
