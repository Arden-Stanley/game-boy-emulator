#include "bus.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t bus_read8(Bus *bus, uint16_t addr) {
  if (addr < 0x8000) {
    return bus->rom[addr]; // change later
  }
  if (addr < 0xA000) {
    return bus->vram[addr - 0x8000];
  }
  if (addr < 0xC000) {
    return 0x00; // change later
  }
  if (addr < 0xE000) {
    return bus->wram[addr - 0xC000];
  }
  if (addr < 0xFE00) {
    return bus->wram[addr - 0xE000];
  }
  if (addr < 0xFEA0) {
    return bus->oam[addr - 0xFE00];
  }
  if (addr < 0xFF00) {
    return 0x00;
  }
  if (addr < 0xFF80) {
    return bus->io[addr - 0xFF00];
  }
  if (addr < 0xFFFF) {
    return bus->hram[addr - 0xFF80];
  }
  if (addr == 0xFFFF) {
    return bus->ie;
  }
  return 0x00;
}

uint16_t bus_read16(Bus *bus, uint16_t addr) {
  uint8_t high_byte = bus_read8(bus, addr);
  uint8_t low_byte = bus_read8(bus, addr++);
  return (low_byte << 8) | high_byte;
}

void bus_write(Bus *bus, uint16_t addr, uint8_t data) {
  if (addr < 0x8000) {
  }
  if (addr < 0xA000) {
    bus->vram[addr - 0x8000] = data;
  }
  if (addr < 0xC000) {
  }
  if (addr < 0xE000) {
    bus->wram[addr - 0xC000] = data;
  }
  if (addr < 0xFE00) {
    bus->wram[addr - 0xE000] = data;
  }
  if (addr < 0xFEA0) {
    bus->oam[addr - 0xFE00] = data;
  }
  if (addr < 0xFF00) {
  }
  if (addr < 0xFF80) {
    bus->io[addr - 0xFF00] = data;
  }
  if (addr < 0xFFFF) {
    bus->hram[addr - 0xFF80] = data;
  }
  if (addr == 0xFFFF) {
    bus->ie = data;
  }
  if (addr > 0xFFFF) {
    printf("Memory Address Out of Bounds: %X", addr);
  }
}

void bus_ld_rom(Bus *bus, const char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("No file exists: %s", path);
    return;
  }
  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    return;
  }
  long size = ftell(file);
  int temp;
  bus->rom = malloc(size * sizeof(uint8_t));

  int ct = 0;
  while ((temp = fgetc(file)) != EOF) {
    bus->rom[ct] = (uint8_t)temp;
  }
}
