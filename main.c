// https://www.youtube.com/watch?v=mamop8aqFNk&list=PLP29wDx6QmW5DdwpdwHCRJsEubS5NrQ9b&index=3

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cpu.c"
#include "map.c"
#include "test.c"

void debug(CPU *cpu)
{
    printf("ip: %4x\n", cpu->reg[ip]);
    printf("ac: %4x\n", cpu->reg[ac]);
    printf("sp: %4x\n", cpu->reg[sp]);
    printf("fp: %4x\n", cpu->reg[fp]);
    printf("rA: %4x\n", cpu->reg[rA]);
    printf("rB: %4x\n", cpu->reg[rB]);
    printf("rC: %4x\n", cpu->reg[rC]);
    printf("rD: %4x\n", cpu->reg[rD]);
    printf("rE: %4x\n", cpu->reg[rE]);
    printf("rF: %4x\n", cpu->reg[rF]);
}

void debug_show_mem(CPU *cpu, uint16_t address, int n)
{
    printf("0x%04x: ", address);
    for (int i = 0; i < (n - 1); i++)
    {
        printf("%02x ", cpu->mem[address + i]);
    }
    printf("\n");
}

int main()
{
    CPU cpu;

    init(&cpu);

    write_test_to_mem(&cpu);

    while (cpu.run)
    {
        debug(&cpu);
        debug_show_mem(&cpu, cpu.reg[ip], 8);
        debug_show_mem(&cpu, 0xffff - 42, 44);
        step(&cpu);
        while (getchar() != '\n')
            ;
    }

    return 0;
}