#include "cpu.h"
#include "ops/alu.h"
#include "ops/bit.h"
#include "ops/ld.h"

void cpu_set_flag(CPU *cpu, Flags flag, bool val) {
  cpu->f = (cpu->f & ~(1 << flag)) | (val << flag);
}
uint8_t cpu_get_flag(CPU *cpu, Flags flag) { return (cpu->f >> flag) & 1; }
uint8_t cpu_get_imm8(CPU *cpu, Bus *bus) { return bus_read8(bus, cpu->pc++); }
uint16_t cpu_get_imm16(CPU *cpu, Bus *bus) {
  uint8_t low_byte = bus_read8(bus, cpu->pc++);
  uint8_t high_byte = bus_read8(bus, cpu->pc++);
  uint16_t data = (low_byte & 0x00FF) | (high_byte << 8);
  return data;
}

uint8_t cpu_step(CPU *cpu, Bus *bus) {
  uint8_t opcode = bus_read8(bus, cpu->pc++);
  printf("Servicing Opcode: %02X\n", opcode);

  switch (opcode) {
  case 0x00:
    return 1;
  case 0x01:
    return op_ld_r16_n16(cpu, bus, &cpu->bc);
  case 0x02:
    return op_ld_mr16_a(cpu, bus, cpu->bc);
  case 0x03:
    return op_inc_r16(&cpu->bc);
  case 0x04:
    return op_inc_r8(cpu, &cpu->b);
  case 0x05:
    return op_dec_r8(cpu, &cpu->b);
  case 0x06:
    return op_ld_r8_n8(cpu, bus, &cpu->b);
  case 0x07:
    return op_rlca(cpu);
  case 0x08:
    return op_ld_mn16_sp(cpu, bus);
  case 0x09:
    return op_add_hl_r16(cpu, cpu->bc);
  case 0x0A:
    return op_ld_a_mr16(cpu, bus, cpu->bc);
  case 0x0B:
    return op_dec_r16(&cpu->bc);
  case 0x0C:
    return op_inc_r8(cpu, &cpu->c);
  case 0x0D:
    return op_dec_r8(cpu, &cpu->c);
  case 0x0E:
    return op_ld_r8_n8(cpu, bus, &cpu->c);
  case 0x0F:
    return op_rrca(cpu);
  case 0x11:
    return op_ld_r16_n16(cpu, bus, &cpu->de);
  case 0x12:
    return op_ld_mr16_a(cpu, bus, cpu->de);
  case 0x13:
    return op_inc_r16(&cpu->de);
  case 0x14:
    return op_inc_r8(cpu, &cpu->d);
  case 0x15:
    return op_dec_r8(cpu, &cpu->d);
  case 0x16:
    return op_ld_r8_n8(cpu, bus, &cpu->d);
  case 0x17:
    return op_rla(cpu);
  case 0x19:
    return op_add_hl_r16(cpu, cpu->de);
  case 0x1A:
    return op_ld_a_mr16(cpu, bus, cpu->de);
  case 0x1B:
    return op_dec_r16(&cpu->de);
  case 0x1C:
    return op_inc_r8(cpu, &cpu->e);
  case 0x1D:
    return op_dec_r8(cpu, &cpu->e);
  case 0x1E:
    return op_ld_r8_n8(cpu, bus, &cpu->e);
  case 0x1F:
    return op_rra(cpu);
  case 0x21:
    return op_ld_r16_n16(cpu, bus, &cpu->hl);
  case 0x22:
    return op_ld_mhli_a(cpu, bus);
  case 0x23:
    return op_inc_r16(&cpu->hl);
  case 0x24:
    return op_inc_r8(cpu, &cpu->h);
  case 0x25:
    return op_dec_r8(cpu, &cpu->h);
  case 0x26:
    return op_ld_r8_n8(cpu, bus, &cpu->h);
  case 0x29:
    return op_add_hl_r16(cpu, cpu->hl);
  case 0x2A:
    return op_ld_a_mhli(cpu, bus);
  case 0x2B:
    return op_dec_r16(&cpu->hl);
  case 0x2C:
    return op_inc_r8(cpu, &cpu->l);
  case 0x2D:
    return op_dec_r8(cpu, &cpu->l);
  case 0x2E:
    return op_ld_r8_n8(cpu, bus, &cpu->l);
  case 0x31:
    return op_ld_sp_n16(cpu, bus);
  case 0x32:
    return op_ld_mhld_a(cpu, bus);
  case 0x33:
    return op_inc_sp(cpu);
  case 0x34:
    return op_inc_mhl(cpu, bus);
  case 0x35:
    return op_dec_mhl(cpu, bus);
  case 0x36:
    return op_ld_mhl_n8(cpu, bus);
  case 0x39:
    return op_add_hl_sp(cpu);
  case 0x3A:
    return op_ld_a_mhld(cpu, bus);
  case 0x3B:
    return op_dec_sp(cpu);
  case 0x3C:
    return op_inc_r8(cpu, &cpu->a);
  case 0x3D:
    return op_dec_r8(cpu, &cpu->a);
  case 0x3E:
    return op_ld_r8_n8(cpu, bus, &cpu->a);
  case 0x40:
    return op_ld_r8_r8(&cpu->b, cpu->b);
  case 0x41:
    return op_ld_r8_r8(&cpu->b, cpu->c);
  case 0x42:
    return op_ld_r8_r8(&cpu->b, cpu->d);
  case 0x43:
    return op_ld_r8_r8(&cpu->b, cpu->e);
  case 0x44:
    return op_ld_r8_r8(&cpu->b, cpu->h);
  case 0x45:
    return op_ld_r8_r8(&cpu->b, cpu->l);
  case 0x46:
    return op_ld_r8_mhl(cpu, bus, &cpu->b);
  case 0x47:
    return op_ld_r8_r8(&cpu->b, cpu->a);
  case 0x48:
    return op_ld_r8_r8(&cpu->c, cpu->b);
  case 0x49:
    return op_ld_r8_r8(&cpu->c, cpu->c);
  case 0x4A:
    return op_ld_r8_r8(&cpu->c, cpu->d);
  case 0x4B:
    return op_ld_r8_r8(&cpu->c, cpu->e);
  case 0x4C:
    return op_ld_r8_r8(&cpu->c, cpu->h);
  case 0x4D:
    return op_ld_r8_r8(&cpu->c, cpu->l);
  case 0x4E:
    return op_ld_r8_mhl(cpu, bus, &cpu->c);
  case 0x4F:
    return op_ld_r8_r8(&cpu->c, cpu->a);
  case 0x50:
    return op_ld_r8_r8(&cpu->d, cpu->b);
  case 0x51:
    return op_ld_r8_r8(&cpu->d, cpu->c);
  case 0x52:
    return op_ld_r8_r8(&cpu->d, cpu->d);
  case 0x53:
    return op_ld_r8_r8(&cpu->d, cpu->e);
  case 0x54:
    return op_ld_r8_r8(&cpu->d, cpu->h);
  case 0x55:
    return op_ld_r8_r8(&cpu->d, cpu->l);
  case 0x56:
    return op_ld_r8_mhl(cpu, bus, &cpu->d);
  case 0x57:
    return op_ld_r8_r8(&cpu->d, cpu->a);
  case 0x58:
    return op_ld_r8_r8(&cpu->e, cpu->b);
  case 0x59:
    return op_ld_r8_r8(&cpu->e, cpu->c);
  case 0x5A:
    return op_ld_r8_r8(&cpu->e, cpu->d);
  case 0x5B:
    return op_ld_r8_r8(&cpu->e, cpu->e);
  case 0x5C:
    return op_ld_r8_r8(&cpu->e, cpu->h);
  case 0x5D:
    return op_ld_r8_r8(&cpu->e, cpu->l);
  case 0x5E:
    return op_ld_r8_mhl(cpu, bus, &cpu->e);
  case 0x5F:
    return op_ld_r8_r8(&cpu->e, cpu->a);
  case 0x60:
    return op_ld_r8_r8(&cpu->h, cpu->b);
  case 0x61:
    return op_ld_r8_r8(&cpu->h, cpu->c);
  case 0x62:
    return op_ld_r8_r8(&cpu->h, cpu->d);
  case 0x63:
    return op_ld_r8_r8(&cpu->h, cpu->e);
  case 0x64:
    return op_ld_r8_r8(&cpu->h, cpu->h);
  case 0x65:
    return op_ld_r8_r8(&cpu->h, cpu->l);
  case 0x66:
    return op_ld_r8_mhl(cpu, bus, &cpu->h);
  case 0x67:
    return op_ld_r8_r8(&cpu->h, cpu->a);
  case 0x68:
    return op_ld_r8_r8(&cpu->l, cpu->b);
  case 0x69:
    return op_ld_r8_r8(&cpu->l, cpu->c);
  case 0x6A:
    return op_ld_r8_r8(&cpu->l, cpu->d);
  case 0x6B:
    return op_ld_r8_r8(&cpu->l, cpu->e);
  case 0x6C:
    return op_ld_r8_r8(&cpu->l, cpu->h);
  case 0x6D:
    return op_ld_r8_r8(&cpu->l, cpu->l);
  case 0x6E:
    return op_ld_r8_mhl(cpu, bus, &cpu->l);
  case 0x6F:
    return op_ld_r8_r8(&cpu->l, cpu->a);
  case 0x70:
    return op_ld_mhl_r8(cpu, bus, cpu->b);
  case 0x71:
    return op_ld_mhl_r8(cpu, bus, cpu->c);
  case 0x72:
    return op_ld_mhl_r8(cpu, bus, cpu->d);
  case 0x73:
    return op_ld_mhl_r8(cpu, bus, cpu->e);
  case 0x74:
    return op_ld_mhl_r8(cpu, bus, cpu->h);
  case 0x75:
    return op_ld_mhl_r8(cpu, bus, cpu->l);
  case 0x77:
    return op_ld_mhl_r8(cpu, bus, cpu->a);
  case 0x78:
    return op_ld_r8_r8(&cpu->a, cpu->b);
  case 0x79:
    return op_ld_r8_r8(&cpu->a, cpu->c);
  case 0x7A:
    return op_ld_r8_r8(&cpu->a, cpu->d);
  case 0x7B:
    return op_ld_r8_r8(&cpu->a, cpu->e);
  case 0x7C:
    return op_ld_r8_r8(&cpu->a, cpu->h);
  case 0x7D:
    return op_ld_r8_r8(&cpu->a, cpu->l);
  case 0x7E:
    return op_ld_r8_mhl(cpu, bus, &cpu->a);
  case 0x7F:
    return op_ld_r8_r8(&cpu->a, cpu->a);
  case 0x80:
    return op_add_a_r8(cpu, cpu->b);
  case 0x81:
    return op_add_a_r8(cpu, cpu->c);
  case 0x82:
    return op_add_a_r8(cpu, cpu->d);
  case 0x83:
    return op_add_a_r8(cpu, cpu->e);
  case 0x84:
    return op_add_a_r8(cpu, cpu->h);
  case 0x85:
    return op_add_a_r8(cpu, cpu->l);
  case 0x86:
    return op_add_a_mhl(cpu, bus);
  case 0x87:
    return op_add_a_r8(cpu, cpu->a);
  case 0x88:
    return op_adc_a_r8(cpu, cpu->b);
  case 0x89:
    return op_adc_a_r8(cpu, cpu->c);
  case 0x8A:
    return op_adc_a_r8(cpu, cpu->d);
  case 0x8B:
    return op_adc_a_r8(cpu, cpu->e);
  case 0x8C:
    return op_adc_a_r8(cpu, cpu->h);
  case 0x8D:
    return op_adc_a_r8(cpu, cpu->l);
  case 0x8E:
    return op_adc_a_mhl(cpu, bus);
  case 0x8F:
    return op_adc_a_r8(cpu, cpu->a);
  case 0x90:
    return op_sub_a_r8(cpu, cpu->b);
  case 0x91:
    return op_sub_a_r8(cpu, cpu->c);
  case 0x92:
    return op_sub_a_r8(cpu, cpu->d);
  case 0x93:
    return op_sub_a_r8(cpu, cpu->e);
  case 0x94:
    return op_sub_a_r8(cpu, cpu->h);
  case 0x95:
    return op_sub_a_r8(cpu, cpu->l);
  case 0x96:
    return op_sub_a_mhl(cpu, bus);
  case 0x97:
    return op_sub_a_r8(cpu, cpu->a);
  case 0x98:
    return op_sbc_a_r8(cpu, cpu->b);
  case 0x99:
    return op_sbc_a_r8(cpu, cpu->c);
  case 0x9A:
    return op_sbc_a_r8(cpu, cpu->d);
  case 0x9B:
    return op_sbc_a_r8(cpu, cpu->e);
  case 0x9C:
    return op_sbc_a_r8(cpu, cpu->h);
  case 0x9D:
    return op_sbc_a_r8(cpu, cpu->l);
  case 0x9E:
    return op_sbc_a_mhl(cpu, bus);
  case 0x9F:
    return op_sbc_a_r8(cpu, cpu->a);
  // TODO: Continue opcodes for alu past this point
  case 0xE0:
    return op_ldh_mn16_a(cpu, bus);
  case 0xE2:
    return op_ldh_mc_a(cpu, bus);
  case 0xEA:
    return op_ld_mn16_a(cpu, bus);
  case 0xF0:
    return op_ldh_a_mn16(cpu, bus);
  case 0xF2:
    return op_ldh_a_mc(cpu, bus);
  case 0xF8:
    return op_ld_hl_spe8(cpu, bus);
  case 0xF9:
    return op_ld_sp_hl(cpu);
  case 0xFA:
    return op_ld_a_mn16(cpu, bus);
  default:
    printf("Invalid Opcode: %X", opcode);
    exit(EXIT_FAILURE);
  }
}
