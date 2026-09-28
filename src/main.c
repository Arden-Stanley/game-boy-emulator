#include "bus.h"
#include "cpu.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  CPU cpu;
  Bus bus;

  cpu.a = 0x01;
  cpu.f = 0x08;
  cpu.b = 0x00;
  cpu.c = 0x13;
  cpu.d = 0x00;
  cpu.e = 0xD8;
  cpu.h = 0x01;
  cpu.l = 0x4D;
  cpu.pc = 0x100;
  cpu.sp = 0xFFFE;
  cpu.halt_bug = 0;

  bus_ld_rom(&bus, "../test_roms/09-op r,r.gb");

  while (cpu.pc < 0x8000) {
    cpu_step(&cpu, &bus);
  }
  free(bus.rom);
  free(bus.ext_ram);
}
