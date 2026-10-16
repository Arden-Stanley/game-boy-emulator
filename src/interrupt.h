#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "bus.h"
#include "cpu.h"

typedef enum {
  IRQ_VBLANK = 0,
  IRQ_LCD = 1,
  IRQ_TIMER = 2,
  IRQ_SERIAL = 3,
  IRQ_JOYPAD = 4
} IRQ;

bool interrupt_get_req(Bus *bus, IRQ req);
bool interrupt_get_enable(Bus *bus, IRQ req);
void interrupt_set_req(Bus *bus, IRQ req, bool val);
bool interrupt_poll_req(Bus *bus, IRQ req);
uint8_t interrupt_poll(CPU *cpu, Bus *bus);

#endif
