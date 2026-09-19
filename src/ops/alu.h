#ifndef ALU_H
#define ALU_H
#include "../cpu.h"

uint8_t op_adc_a_r8(CPU *cpu, uint8_t val);
uint8_t op_adc_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_adc_a_n8(CPU *cpu, Bus *bus);
uint8_t op_add_a_r8(CPU *cpu, uint8_t val);
uint8_t op_add_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_add_a_n8(CPU *cpu, Bus *bus);
uint8_t op_add_hl_r16(CPU *cpu, uint16_t val);
uint8_t op_add_hl_sp(CPU *cpu);
uint8_t op_add_sp_e8(CPU *cpu, Bus *bus);

uint8_t op_cp_a_r8(CPU *cpu, uint8_t val);
uint8_t op_cp_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_cp_a_n8(CPU *cpu, Bus *bus);

uint8_t op_dec_r8(CPU *cpu, uint8_t *reg);
uint8_t op_dec_mhl(CPU *cpu, Bus *bus);
uint8_t op_dec_r16(uint16_t *reg);
uint8_t op_dec_sp(CPU *cpu);

uint8_t op_inc_r8(CPU *cpu, uint8_t *reg);
uint8_t op_inc_mhl(CPU *cpu, Bus *bus);
uint8_t op_inc_r16(uint16_t *reg);
uint8_t op_inc_sp(CPU *cpu);

uint8_t op_sbc_a_r8(CPU *cpu, uint8_t val);
uint8_t op_sbc_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_sbc_a_n8(CPU *cpu, Bus *bus);

uint8_t op_sub_a_r8(CPU *cpu, uint8_t val);
uint8_t op_sub_a_mhl(CPU *cpu, Bus *bus);
uint8_t op_sub_a_n8(CPU *cpu, Bus *bus);

uint8_t op_ccf(CPU *cpu);
uint8_t op_scf(CPU *cpu);
#endif
