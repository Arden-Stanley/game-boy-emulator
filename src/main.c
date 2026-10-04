#include "bus.h"
#include "cpu.h"
#include <memory.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  CPU cpu;
  Bus bus;
  memset(&bus, 0, sizeof(bus));
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 2500000;

  cpu.a = 0x01;
  cpu.f = 0x08;
  cpu.b = 0xFF;
  cpu.c = 0x13;
  cpu.d = 0x00;
  cpu.e = 0xD8;
  cpu.h = 0x01;
  cpu.l = 0x4D;
  cpu.pc = 0x0100;
  cpu.sp = 0xFFFE;
  cpu.halt_bug = 0;
  cpu.running = 1;

  bus_ld_rom(&bus, "../test_roms/10-bit ops.gb");

  while (cpu.running) {
    cpu_step(&cpu, &bus);
  }
  free(bus.rom);
  free(bus.ext_ram);
}
