#ifndef BUS_H
#define BUS_H

#include <stdint.h>

typedef struct {
  uint8_t *rom;
  uint32_t rom_size;
  uint8_t *ext_ram;
  uint32_t ext_ram_size;

  uint8_t vram[0x2000];
  uint8_t wram[0x2000];
  uint8_t oam[0x0A0];
  uint8_t io[0x080];
  uint8_t hram[0x07F];
  uint8_t ie;
} Bus;

uint8_t bus_read8(Bus *bus, uint16_t addr);
void bus_write(Bus *bus, uint16_t addr, uint8_t data);

void bus_ld_rom(Bus *bus, const char *path);

#endif
