#ifndef LD_H
#define LD_H
#include "../bus.h"
#include "../cpu.h"

uint8_t op_ld_r8_r8(uint8_t *dest, uint8_t);
uint8_t op_ld_r8_n8(CPU *cpu, Bus *bus, uint8_t *dest);
uint8_t op_ld_r16_n16(CPU *cpu, Bus *bus, uint16_t *dest);
uint8_t op_ld_mhl_r8(CPU *cpu, Bus *bus, uint8_t src);
uint8_t op_ld_mhl_n8(CPU *cpu, Bus *bus);
uint8_t op_ld_r8_mhl(CPU *cpu, Bus *bus, uint8_t *dest);
uint8_t op_ld_mr16_a(CPU *cpu, Bus *bus, uint16_t addr);
uint8_t op_ld_mn16_a(CPU *cpu, Bus *bus);
uint8_t op_ldh_mn16_a(CPU *cpu, Bus *bus);
uint8_t op_ldh_mc_a(CPU *cpu, Bus *bus);
uint8_t op_ld_a_mr16(CPU *cpu, Bus *bus, uint16_t addr);
uint8_t op_ld_a_mn16(CPU *cpu, Bus *bus);
uint8_t op_ldh_a_mn16(CPU *cpu, Bus *bus);
uint8_t op_ldh_a_mc(CPU *cpu, Bus *bus);
uint8_t op_ld_mhli_a(CPU *cpu, Bus *bus);
uint8_t op_ld_mhld_a(CPU *cpu, Bus *bus);
uint8_t op_ld_a_mhld(CPU *cpu, Bus *bus);
uint8_t op_ld_a_mhli(CPU *cpu, Bus *bus);
uint8_t op_ld_sp_n16(CPU *cpu, Bus *bus);
uint8_t op_ld_mn16_sp(CPU *cpu, Bus *bus); // TODO
uint8_t op_ld_hl_spe8(CPU *cpu, Bus *bus);
uint8_t op_ld_sp_hl(CPU *cpu);

#endif
