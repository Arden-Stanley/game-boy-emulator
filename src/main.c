#include "bus.h"
#include "cpu.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char **argv) {
  CPU cpu;
  Bus bus;
  struct timespec ts;
  ts.tv_sec = 0;
  ts.tv_nsec = 25000000;

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
  cpu.running = 1;

  bus_ld_rom(&bus, "../test_roms/06-ld r,r.gb");

  while (cpu.running) {
    cpu_step(&cpu, &bus);
    nanosleep(&ts, NULL);
  }
  free(bus.rom);
  free(bus.ext_ram);
}
