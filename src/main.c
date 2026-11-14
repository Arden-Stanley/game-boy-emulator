#include "gameboy.h"

int main(int argc, char *argv[]) {
  GameBoy *gb = gameboy_create();

  bus_load_rom(&gb->bus, argv[1]);

  gameboy_run(gb);
  gameboy_destroy(gb);
}
