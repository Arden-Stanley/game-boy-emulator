#ifndef GAMEBOY_H
#define GAMEBOY_H
#include "bus.h"
#include "cpu.h"
#include "logger.h"
#include "timer.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct GameBoy {
  Bus bus;
  CPU cpu;
  Timer timer;
  Logger logger;
} GameBoy;

GameBoy *gameboy_create();
void gameboy_run(GameBoy *gb);
void gameboy_destroy(GameBoy *gb);

#endif
