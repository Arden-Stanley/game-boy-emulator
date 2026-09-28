#include "pfx.h"

uint8_t op_pfx_decode(CPU *cpu, Bus *bus) {
  uint8_t pfx_op = cpu_get_imm8(cpu, bus);
  switch (pfx_op) {
  case 0x00:
    return op_rlc_r8(cpu, &cpu->b);
  case 0x01:
    return op_rlc_r8(cpu, &cpu->c);
  case 0x02:
    return op_rlc_r8(cpu, &cpu->d);
  case 0x03:
    return op_rlc_r8(cpu, &cpu->e);
  case 0x04:
    return op_rlc_r8(cpu, &cpu->h);
  case 0x05:
    return op_rlc_r8(cpu, &cpu->l);
  case 0x06:
    return op_rlc_mhl(cpu, bus);
  case 0x07:
    return op_rlca(cpu);
  case 0x08:
    return op_rrc_r8(cpu, &cpu->b);
  case 0x09:
    return op_rrc_r8(cpu, &cpu->c);
  case 0x0A:
    return op_rrc_r8(cpu, &cpu->d);
  case 0x0B:
    return op_rrc_r8(cpu, &cpu->e);
  case 0x0C:
    return op_rrc_r8(cpu, &cpu->h);
  case 0x0D:
    return op_rrc_r8(cpu, &cpu->l);
  case 0x0E:
    return op_rrc_mhl(cpu, bus);
  case 0x0F:
    return op_rrca(cpu);
  case 0x10:
    return op_rl_r8(cpu, &cpu->b);
  case 0x11:
    return op_rl_r8(cpu, &cpu->c);
  case 0x12:
    return op_rl_r8(cpu, &cpu->d);
  case 0x13:
    return op_rl_r8(cpu, &cpu->e);
  case 0x14:
    return op_rl_r8(cpu, &cpu->h);
  case 0x15:
    return op_rl_r8(cpu, &cpu->l);
  case 0x16:
    return op_rl_mhl(cpu, bus);
  case 0x17:
    return op_rla(cpu);
  case 0x18:
    return op_rr_r8(cpu, &cpu->b);
  case 0x19:
    return op_rr_r8(cpu, &cpu->c);
  case 0x1A:
    return op_rr_r8(cpu, &cpu->d);
  case 0x1B:
    return op_rr_r8(cpu, &cpu->e);
  case 0x1C:
    return op_rr_r8(cpu, &cpu->h);
  case 0x1D:
    return op_rr_r8(cpu, &cpu->l);
  case 0x1E:
    return op_rr_mhl(cpu, bus);
  case 0x1F:
    return op_rra(cpu);
  case 0x20:
    return op_sla_r8(cpu, &cpu->b);
  case 0x21:
    return op_sla_r8(cpu, &cpu->c);
  case 0x22:
    return op_sla_r8(cpu, &cpu->d);
  case 0x23:
    return op_sla_r8(cpu, &cpu->e);
  case 0x24:
    return op_sla_r8(cpu, &cpu->h);
  case 0x25:
    return op_sla_r8(cpu, &cpu->l);
  case 0x26:
    return op_sla_mhl(cpu, bus);
  case 0x27:
    return op_sla_r8(cpu, &cpu->a);
  case 0x28:
    return op_sra_r8(cpu, &cpu->b);
  case 0x29:
    return op_sra_r8(cpu, &cpu->c);
  case 0x2A:
    return op_sra_r8(cpu, &cpu->d);
  case 0x2B:
    return op_sra_r8(cpu, &cpu->e);
  case 0x2C:
    return op_sra_r8(cpu, &cpu->h);
  case 0x2D:
    return op_sra_r8(cpu, &cpu->l);
  case 0x2E:
    return op_sra_mhl(cpu, bus);
  case 0x2F:
    return op_sra_r8(cpu, &cpu->a);
  case 0x30:
    return op_swap_r8(cpu, &cpu->b);
  case 0x31:
    return op_swap_r8(cpu, &cpu->c);
  case 0x32:
    return op_swap_r8(cpu, &cpu->d);
  case 0x33:
    return op_swap_r8(cpu, &cpu->e);
  case 0x34:
    return op_swap_r8(cpu, &cpu->h);
  case 0x35:
    return op_swap_r8(cpu, &cpu->l);
  case 0x36:
    return op_swap_mhl(cpu, bus);
  case 0x37:
    return op_swap_r8(cpu, &cpu->a);
  case 0x38:
    return op_srl_r8(cpu, &cpu->b);
  case 0x39:
    return op_srl_r8(cpu, &cpu->c);
  case 0x3A:
    return op_srl_r8(cpu, &cpu->d);
  case 0x3B:
    return op_srl_r8(cpu, &cpu->e);
  case 0x3C:
    return op_srl_r8(cpu, &cpu->h);
  case 0x3D:
    return op_srl_r8(cpu, &cpu->l);
  case 0x3E:
    return op_srl_mhl(cpu, bus);
  case 0x3F:
    return op_srl_r8(cpu, &cpu->a);
  case 0x40:
    return op_bit_u3_r8(cpu, 0, cpu->b);
  case 0x41:
    return op_bit_u3_r8(cpu, 0, cpu->c);
  case 0x42:
    return op_bit_u3_r8(cpu, 0, cpu->d);
  case 0x43:
    return op_bit_u3_r8(cpu, 0, cpu->e);
  case 0x44:
    return op_bit_u3_r8(cpu, 0, cpu->h);
  case 0x45:
    return op_bit_u3_r8(cpu, 0, cpu->l);
  case 0x46:
    return op_bit_u3_mhl(cpu, bus, 0);
  case 0x47:
    return op_bit_u3_r8(cpu, 0, cpu->a);
  case 0x48:
    return op_bit_u3_r8(cpu, 1, cpu->b);
  case 0x49:
    return op_bit_u3_r8(cpu, 1, cpu->c);
  case 0x4A:
    return op_bit_u3_r8(cpu, 1, cpu->d);
  case 0x4B:
    return op_bit_u3_r8(cpu, 1, cpu->e);
  case 0x4C:
    return op_bit_u3_r8(cpu, 1, cpu->h);
  case 0x4D:
    return op_bit_u3_r8(cpu, 1, cpu->l);
  case 0x4E:
    return op_bit_u3_mhl(cpu, bus, 1);
  case 0x4F:
    return op_bit_u3_r8(cpu, 1, cpu->a);
  case 0x50:
    return op_bit_u3_r8(cpu, 2, cpu->b);
  case 0x51:
    return op_bit_u3_r8(cpu, 2, cpu->c);
  case 0x52:
    return op_bit_u3_r8(cpu, 2, cpu->d);
  case 0x53:
    return op_bit_u3_r8(cpu, 2, cpu->e);
  case 0x54:
    return op_bit_u3_r8(cpu, 2, cpu->h);
  case 0x55:
    return op_bit_u3_r8(cpu, 2, cpu->l);
  case 0x56:
    return op_bit_u3_mhl(cpu, bus, 2);
  case 0x57:
    return op_bit_u3_r8(cpu, 2, cpu->a);
  case 0x58:
    return op_bit_u3_r8(cpu, 3, cpu->b);
  case 0x59:
    return op_bit_u3_r8(cpu, 3, cpu->c);
  case 0x5A:
    return op_bit_u3_r8(cpu, 3, cpu->d);
  case 0x5B:
    return op_bit_u3_r8(cpu, 3, cpu->e);
  case 0x5C:
    return op_bit_u3_r8(cpu, 3, cpu->h);
  case 0x5D:
    return op_bit_u3_r8(cpu, 3, cpu->l);
  case 0x5E:
    return op_bit_u3_mhl(cpu, bus, 3);
  case 0x5F:
    return op_bit_u3_r8(cpu, 3, cpu->a);
  case 0x60:
    return op_bit_u3_r8(cpu, 4, cpu->b);
  case 0x61:
    return op_bit_u3_r8(cpu, 4, cpu->c);
  case 0x62:
    return op_bit_u3_r8(cpu, 4, cpu->d);
  case 0x63:
    return op_bit_u3_r8(cpu, 4, cpu->e);
  case 0x64:
    return op_bit_u3_r8(cpu, 4, cpu->h);
  case 0x65:
    return op_bit_u3_r8(cpu, 4, cpu->l);
  case 0x66:
    return op_bit_u3_mhl(cpu, bus, 4);
  case 0x67:
    return op_bit_u3_r8(cpu, 4, cpu->a);
  case 0x68:
    return op_bit_u3_r8(cpu, 5, cpu->b);
  case 0x69:
    return op_bit_u3_r8(cpu, 5, cpu->c);
  case 0x6A:
    return op_bit_u3_r8(cpu, 5, cpu->d);
  case 0x6B:
    return op_bit_u3_r8(cpu, 5, cpu->e);
  case 0x6C:
    return op_bit_u3_r8(cpu, 5, cpu->h);
  case 0x6D:
    return op_bit_u3_r8(cpu, 5, cpu->l);
  case 0x6E:
    return op_bit_u3_mhl(cpu, bus, 5);
  case 0x6F:
    return op_bit_u3_r8(cpu, 5, cpu->a);
  case 0x70:
    return op_bit_u3_r8(cpu, 6, cpu->b);
  case 0x71:
    return op_bit_u3_r8(cpu, 6, cpu->c);
  case 0x72:
    return op_bit_u3_r8(cpu, 6, cpu->d);
  case 0x73:
    return op_bit_u3_r8(cpu, 6, cpu->e);
  case 0x74:
    return op_bit_u3_r8(cpu, 6, cpu->h);
  case 0x75:
    return op_bit_u3_r8(cpu, 6, cpu->l);
  case 0x76:
    return op_bit_u3_mhl(cpu, bus, 6);
  case 0x77:
    return op_bit_u3_r8(cpu, 6, cpu->a);
  case 0x78:
    return op_bit_u3_r8(cpu, 7, cpu->b);
  case 0x79:
    return op_bit_u3_r8(cpu, 7, cpu->c);
  case 0x7A:
    return op_bit_u3_r8(cpu, 7, cpu->d);
  case 0x7B:
    return op_bit_u3_r8(cpu, 7, cpu->e);
  case 0x7C:
    return op_bit_u3_r8(cpu, 7, cpu->h);
  case 0x7D:
    return op_bit_u3_r8(cpu, 7, cpu->l);
  case 0x7E:
    return op_bit_u3_mhl(cpu, bus, 7);
  case 0x7F:
    return op_bit_u3_r8(cpu, 7, cpu->a);
  case 0x80:
    return op_res_u3_r8(0, &cpu->b);
  case 0x81:
    return op_res_u3_r8(0, &cpu->c);
  case 0x82:
    return op_res_u3_r8(0, &cpu->d);
  case 0x83:
    return op_res_u3_r8(0, &cpu->e);
  case 0x84:
    return op_res_u3_r8(0, &cpu->h);
  case 0x85:
    return op_res_u3_r8(0, &cpu->l);
  case 0x86:
    return op_res_u3_mhl(cpu, bus, 0);
  case 0x87:
    return op_res_u3_r8(0, &cpu->a);
  case 0x88:
    return op_res_u3_r8(1, &cpu->b);
  case 0x89:
    return op_res_u3_r8(1, &cpu->c);
  case 0x8A:
    return op_res_u3_r8(1, &cpu->d);
  case 0x8B:
    return op_res_u3_r8(1, &cpu->e);
  case 0x8C:
    return op_res_u3_r8(1, &cpu->h);
  case 0x8D:
    return op_res_u3_r8(1, &cpu->l);
  case 0x8E:
    return op_res_u3_mhl(cpu, bus, 1);
  case 0x8F:
    return op_res_u3_r8(1, &cpu->a);
  case 0x90:
    return op_res_u3_r8(2, &cpu->b);
  case 0x91:
    return op_res_u3_r8(2, &cpu->c);
  case 0x92:
    return op_res_u3_r8(2, &cpu->d);
  case 0x93:
    return op_res_u3_r8(2, &cpu->e);
  case 0x94:
    return op_res_u3_r8(2, &cpu->h);
  case 0x95:
    return op_res_u3_r8(2, &cpu->l);
  case 0x96:
    return op_res_u3_mhl(cpu, bus, 2);
  case 0x97:
    return op_res_u3_r8(2, &cpu->a);
  case 0x98:
    return op_res_u3_r8(3, &cpu->b);
  case 0x99:
    return op_res_u3_r8(3, &cpu->c);
  case 0x9A:
    return op_res_u3_r8(3, &cpu->d);
  case 0x9B:
    return op_res_u3_r8(3, &cpu->e);
  case 0x9C:
    return op_res_u3_r8(3, &cpu->h);
  case 0x9D:
    return op_res_u3_r8(3, &cpu->l);
  case 0x9E:
    return op_res_u3_mhl(cpu, bus, 3);
  case 0x9F:
    return op_res_u3_r8(3, &cpu->a);
  case 0xA0:
    return op_res_u3_r8(4, &cpu->b);
  case 0xA1:
    return op_res_u3_r8(4, &cpu->c);
  case 0xA2:
    return op_res_u3_r8(4, &cpu->d);
  case 0xA3:
    return op_res_u3_r8(4, &cpu->e);
  case 0xA4:
    return op_res_u3_r8(4, &cpu->h);
  case 0xA5:
    return op_res_u3_r8(4, &cpu->l);
  case 0xA6:
    return op_res_u3_mhl(cpu, bus, 4);
  case 0xA7:
    return op_res_u3_r8(4, &cpu->a);
  case 0xA8:
    return op_res_u3_r8(5, &cpu->b);
  case 0xA9:
    return op_res_u3_r8(5, &cpu->c);
  case 0xAA:
    return op_res_u3_r8(5, &cpu->d);
  case 0xAB:
    return op_res_u3_r8(5, &cpu->e);
  case 0xAC:
    return op_res_u3_r8(5, &cpu->h);
  case 0xAD:
    return op_res_u3_r8(5, &cpu->l);
  case 0xAE:
    return op_res_u3_mhl(cpu, bus, 5);
  case 0xAF:
    return op_res_u3_r8(5, &cpu->a);
  case 0xB0:
    return op_res_u3_r8(6, &cpu->b);
  case 0xB1:
    return op_res_u3_r8(6, &cpu->c);
  case 0xB2:
    return op_res_u3_r8(6, &cpu->d);
  case 0xB3:
    return op_res_u3_r8(6, &cpu->e);
  case 0xB4:
    return op_res_u3_r8(6, &cpu->h);
  case 0xB5:
    return op_res_u3_r8(6, &cpu->l);
  case 0xB6:
    return op_res_u3_mhl(cpu, bus, 6);
  case 0xB7:
    return op_res_u3_r8(6, &cpu->a);
  case 0xB8:
    return op_res_u3_r8(7, &cpu->b);
  case 0xB9:
    return op_res_u3_r8(7, &cpu->c);
  case 0xBA:
    return op_res_u3_r8(7, &cpu->d);
  case 0xBB:
    return op_res_u3_r8(7, &cpu->e);
  case 0xBC:
    return op_res_u3_r8(7, &cpu->h);
  case 0xBD:
    return op_res_u3_r8(7, &cpu->l);
  case 0xBE:
    return op_res_u3_mhl(cpu, bus, 7);
  case 0xBF:
    return op_res_u3_r8(7, &cpu->a);
  case 0xC0:
    return op_set_u3_r8(0, &cpu->b);
  case 0xC1:
    return op_set_u3_r8(0, &cpu->c);
  case 0xC2:
    return op_set_u3_r8(0, &cpu->d);
  case 0xC3:
    return op_set_u3_r8(0, &cpu->e);
  case 0xC4:
    return op_set_u3_r8(0, &cpu->h);
  case 0xC5:
    return op_set_u3_r8(0, &cpu->l);
  case 0xC6:
    return op_set_u3_mhl(cpu, bus, 0);
  case 0xC7:
    return op_set_u3_r8(0, &cpu->a);
  case 0xC8:
    return op_set_u3_r8(1, &cpu->b);
  case 0xC9:
    return op_set_u3_r8(1, &cpu->c);
  case 0xCA:
    return op_set_u3_r8(1, &cpu->d);
  case 0xCB:
    return op_set_u3_r8(1, &cpu->e);
  case 0xCC:
    return op_set_u3_r8(1, &cpu->h);
  case 0xCD:
    return op_set_u3_r8(1, &cpu->l);
  case 0xCE:
    return op_set_u3_mhl(cpu, bus, 1);
  case 0xCF:
    return op_set_u3_r8(1, &cpu->a);
  case 0xD0:
    return op_set_u3_r8(2, &cpu->b);
  case 0xD1:
    return op_set_u3_r8(2, &cpu->c);
  case 0xD2:
    return op_set_u3_r8(2, &cpu->d);
  case 0xD3:
    return op_set_u3_r8(2, &cpu->e);
  case 0xD4:
    return op_set_u3_r8(2, &cpu->h);
  case 0xD5:
    return op_set_u3_r8(2, &cpu->l);
  case 0xD6:
    return op_set_u3_mhl(cpu, bus, 2);
  case 0xD7:
    return op_set_u3_r8(2, &cpu->a);
  case 0xD8:
    return op_set_u3_r8(3, &cpu->b);
  case 0xD9:
    return op_set_u3_r8(3, &cpu->c);
  case 0xDA:
    return op_set_u3_r8(3, &cpu->d);
  case 0xDB:
    return op_set_u3_r8(3, &cpu->e);
  case 0xDC:
    return op_set_u3_r8(3, &cpu->h);
  case 0xDD:
    return op_set_u3_r8(3, &cpu->l);
  case 0xDE:
    return op_set_u3_mhl(cpu, bus, 3);
  case 0xDF:
    return op_set_u3_r8(3, &cpu->a);
  case 0xE0:
    return op_set_u3_r8(4, &cpu->b);
  case 0xE1:
    return op_set_u3_r8(4, &cpu->c);
  case 0xE2:
    return op_set_u3_r8(4, &cpu->d);
  case 0xE3:
    return op_set_u3_r8(4, &cpu->e);
  case 0xE4:
    return op_set_u3_r8(4, &cpu->h);
  case 0xE5:
    return op_set_u3_r8(4, &cpu->l);
  case 0xE6:
    return op_set_u3_mhl(cpu, bus, 4);
  case 0xE7:
    return op_set_u3_r8(4, &cpu->a);
  case 0xE8:
    return op_set_u3_r8(5, &cpu->b);
  case 0xE9:
    return op_set_u3_r8(5, &cpu->c);
  case 0xEA:
    return op_set_u3_r8(5, &cpu->d);
  case 0xEB:
    return op_set_u3_r8(5, &cpu->e);
  case 0xEC:
    return op_set_u3_r8(5, &cpu->h);
  case 0xED:
    return op_set_u3_r8(5, &cpu->l);
  case 0xEE:
    return op_set_u3_mhl(cpu, bus, 5);
  case 0xEF:
    return op_set_u3_r8(5, &cpu->a);
  case 0xF0:
    return op_set_u3_r8(6, &cpu->b);
  case 0xF1:
    return op_set_u3_r8(6, &cpu->c);
  case 0xF2:
    return op_set_u3_r8(6, &cpu->d);
  case 0xF3:
    return op_set_u3_r8(6, &cpu->e);
  case 0xF4:
    return op_set_u3_r8(6, &cpu->h);
  case 0xF5:
    return op_set_u3_r8(6, &cpu->l);
  case 0xF6:
    return op_set_u3_mhl(cpu, bus, 6);
  case 0xF7:
    return op_set_u3_r8(6, &cpu->a);
  case 0xF8:
    return op_set_u3_r8(7, &cpu->b);
  case 0xF9:
    return op_set_u3_r8(7, &cpu->c);
  case 0xFA:
    return op_set_u3_r8(7, &cpu->d);
  case 0xFB:
    return op_set_u3_r8(7, &cpu->e);
  case 0xFC:
    return op_set_u3_r8(7, &cpu->h);
  case 0xFD:
    return op_set_u3_r8(7, &cpu->l);
  case 0xFE:
    return op_set_u3_mhl(cpu, bus, 7);
  case 0xFF:
    return op_set_u3_r8(7, &cpu->a);
  default:
    printf("Invalid Prefixed Opcode: %X", pfx_op);
    return 0;
  }
}
