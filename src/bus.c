#include "bus.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t bus_read8(Bus *bus, uint16_t addr) {
  if (addr < 0x8000) {
    return bus->rom[addr];
  } else if (addr < 0xA000) {
    return bus->vram[addr - 0x8000];
  } else if (addr < 0xC000) {
    return bus->ext_ram[addr - 0xA000];
  } else if (addr < 0xE000) {
    return bus->wram[addr - 0xC000];
  } else if (addr < 0xFE00) {
    return bus->wram[addr - 0xE000];
  } else if (addr < 0xFEA0) {
    return bus->oam[addr - 0xFE00];
  } else if (addr < 0xFF00) {
    return 0x00;
  } else if (addr < 0xFF80) {
    return bus->io[addr - 0xFF00];
  } else if (addr < 0xFFFF) {
    return bus->hram[addr - 0xFF80];
  } else if (addr == 0xFFFF) {
    return bus->ie;
  }
  return 0x00;
}

void bus_write(Bus *bus, uint16_t addr, uint8_t data) {
  if (addr < 0x8000) {
    bus->rom[addr] = data;
  } else if (addr < 0xA000) {
    bus->vram[addr - 0x8000] = data;
  } else if (addr < 0xC000) {
  } else if (addr < 0xE000) {
    bus->wram[addr - 0xC000] = data;
  } else if (addr < 0xFE00) {
    bus->wram[addr - 0xE000] = data;
  } else if (addr < 0xFEA0) {
    bus->oam[addr - 0xFE00] = data;
  } else if (addr < 0xFF00) {
  } else if (addr < 0xFF80) {
    if (addr == 0xFF02 && data == 0x81) {
      char c = bus_read8(bus, 0xFF01);
      printf("%c", c);
      fflush(stdout);
      bus_write(bus, 0xFF02, 0x00);
    }

    bus->io[addr - 0xFF00] = data;
  } else if (addr < 0xFFFF) {
    bus->hram[addr - 0xFF80] = data;
  } else if (addr == IE) {
    bus->ie = data;
  } else {
    printf("Memory Address Out of Bounds: %X", addr);
  }
}

void bus_ld_rom(Bus *bus, const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    printf("No file exists: %s", path);
    return;
  }
  fseek(file, 0, SEEK_END);

  long size = ftell(file);
  char temp;
  rewind(file);

  printf("Rom Size: %i\n\n", (int)size);
  bus->rom = malloc(size * sizeof(uint8_t));
  bus->ext_ram = malloc(1000 * sizeof(uint8_t));
  fread(bus->rom, sizeof(uint8_t), size, file);

  fclose(file);
}
