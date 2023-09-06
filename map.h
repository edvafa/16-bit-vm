#ifndef _MAP
#define _MAP

#include "cpu.h"
#include <stdint.h>

typedef struct Device
{
    void (*set_uint8)(uint16_t address, uint8_t data);
    void (*set_uint16)(uint16_t address, uint16_t data);
    uint8_t (*get_uint8)(uint8_t address);
    uint16_t (*get_uint16)(uint16_t address);
} Device;

void set_uint8(CPU *cpu, uint16_t address, uint8_t data);
void set_uint16(CPU *cpu, uint16_t address, uint16_t data);
uint8_t get_uint8(CPU *cpu, uint8_t address);
uint16_t get_uint16(CPU *cpu, uint16_t address);

#endif