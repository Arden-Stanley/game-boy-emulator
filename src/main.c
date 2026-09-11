#include "bus.h"
#include "cpu.h"
#include <stdio.h>

int main(int argc, char **argv) {
  printf("Initializing...\n");
  CPU cpu;
  Bus bus;

  while (1) {
    cpu_step(&cpu, &bus);
  }
}
