#include "interrupt.h"

bool interrupt_get_req(Bus *bus, IRQ req) {
  uint8_t reg = bus_read8(bus, MEM_IF);
  // printf("IF: 0x%X\n", reg);
  return (reg & (1 << req));
}

bool interrupt_get_enable(Bus *bus, IRQ req) {
  uint8_t reg = bus_read8(bus, MEM_IE);
  // printf("IE: 0x%X\n", reg);
  return (reg & (1 << req));
}

void interrupt_set_req(Bus *bus, IRQ req, bool val) {
  uint8_t reg = bus_read8(bus, MEM_IF);
  reg = (req & ~(1 << req)) | (val << req);
  bus_write(bus, MEM_IF, reg);
}

bool interrupt_poll_req(Bus *bus, IRQ req) {
  return (interrupt_get_req(bus, req) && interrupt_get_enable(bus, req));
}

uint8_t interrupt_poll(CPU *cpu, Bus *bus) {
  if (cpu->ime) {
    cpu->ime = 0;
    cpu->sp--;
    bus_write(bus, cpu->sp, cpu->pc & 0xFF);
    cpu->sp--;
    bus_write(bus, cpu->sp, cpu->pc >> 8);

    // interrupt_get_req(bus, IRQ_VBLANK);
    // interrupt_get_enable(bus, IRQ_VBLANK);

    // printf("IME Activated!\n");

    if (interrupt_poll_req(bus, IRQ_VBLANK)) {
      interrupt_set_req(bus, IRQ_VBLANK, 0);
      cpu->pc = 0x0040;

      printf("Interrupt Jump to: PC = 0x%04X", cpu->pc);
      cpu->halted = 0;
      return 5;
    } else if (interrupt_poll_req(bus, IRQ_LCD)) {
      interrupt_set_req(bus, IRQ_LCD, 0);
      cpu->pc = 0x0048;

      printf("Interrupt Jump to: PC = 0x%04X", cpu->pc);

      cpu->halted = 0;
      return 5;
    } else if (interrupt_poll_req(bus, IRQ_TIMER)) {
      interrupt_set_req(bus, IRQ_TIMER, 0);
      cpu->pc = 0x0050;

      printf("Interrupt Jump to: PC = 0x%04X", cpu->pc);

      cpu->halted = 0;
      return 5;
    } else if (interrupt_poll_req(bus, IRQ_SERIAL)) {
      interrupt_set_req(bus, IRQ_SERIAL, 0);
      cpu->pc = 0x0058;

      printf("Interrupt Jump to: PC = 0x%04X", cpu->pc);

      cpu->halted = 0;
      return 5;
    } else if (interrupt_poll_req(bus, IRQ_JOYPAD)) {
      interrupt_set_req(bus, IRQ_JOYPAD, 0);
      cpu->pc = 0x0060;

      printf("Interrupt Jump to: PC = 0x%04X", cpu->pc);

      cpu->halted = 0;
      return 5;
    }
  }
  return 0;
}
