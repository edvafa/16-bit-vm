#include <stdint.h>
#include <stdio.h>

void clear_screen()
{
    printf("\033[2J");
}

void set_bold()
{
    printf("\033[1m");
}

void set_regular()
{
    printf("\033[0m");
}

void move_cursor(uint8_t x, uint8_t y)
{
    printf("\033[%d;%dH", y + 1, (x * 2) + 1);
}

void sd_set_uint8(uint16_t address, uint8_t data)
{
    const uint8_t x = (address & 0x0f);
    const uint8_t y = ((address & 0xf0) >> 4);
    move_cursor(x, y);
    printf("%c", (char)data);
};

void sd_set_uint16(uint16_t address, uint16_t data)
{
    const uint8_t x = (address & 0x0f);
    const uint8_t y = ((address & 0xf0) >> 4);
    const uint8_t command = (data & 0xff00) >> 8;

    if (command == 0xff)
        clear_screen();
    else if (command == 0x01)
        set_bold();
    else if (command == 0x02)
        set_regular();

    move_cursor(x, y);
    printf("%c", (char)data);
};

uint8_t sd_get_uint8(uint8_t address)
{
    return 0;
};

uint16_t sd_get_uint16(uint16_t address)
{
    return 0;
};