#include <stdbool.h>
#include <stdint.h>

#include "cpu.h"
#include "map.h"
#include "screen-device.c"

Device screen = {.set_uint8 = sd_set_uint8,
                 .get_uint8 = sd_get_uint8,
                 .set_uint16 = sd_set_uint16,
                 .get_uint16 = sd_get_uint16};
Device *device_ref;

bool check_device_map(uint16_t address)
{
    if (0x1000 <= address && address <= 0x10ff)
    {
        device_ref = &screen;
        return true;
    }
    return false;
}

void set_uint8(CPU *cpu, uint16_t address, uint8_t data)
{
    if (check_device_map(address))
        device_ref->set_uint8(address, data);
    else
        cpu->mem[address] = data;
};

void set_uint16(CPU *cpu, uint16_t address, uint16_t data)
{
    if (check_device_map(address))
        device_ref->set_uint16(address, data);
    else
    {
        cpu->mem[address] = data >> 8;
        cpu->mem[address + 1] = data;
    }
};

uint8_t get_uint8(CPU *cpu, uint8_t address)
{
    if (check_device_map(address))
        return device_ref->get_uint8(address);
    else
        return cpu->mem[address];
};

uint16_t get_uint16(CPU *cpu, uint16_t address)
{
    if (check_device_map(address))
        return device_ref->get_uint16(address);
    else
        return (cpu->mem[address] << 8) | cpu->mem[address + 1];
    ;
};