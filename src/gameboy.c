#include "gameboy.h"
#include "interrupt.h"

GameBoy *gameboy_create() {
  GameBoy *gb = malloc(sizeof(GameBoy));
  timer_init(&gb->timer);
  cpu_init(&gb->cpu);
  bus_init(&gb->bus);
  logger_init(&gb->logger, stdout, DEBUG);
  return gb;
}

void gameboy_run(GameBoy *gb) {
  while (gb->cpu.running) {
    gb->timer.cycle_count = cpu_step(&gb->cpu, &gb->bus);
    timer_increment(&gb->timer);
    if (gb->timer.request_interrupt)
      interrupt_set_req(&gb->bus, IRQ_TIMER, true);
  }
}

void gameboy_destroy(GameBoy *gb) {
  bus_cleanup(&gb->bus);
  free(gb);
  gb = NULL;
}
