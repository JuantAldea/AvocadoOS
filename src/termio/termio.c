#include "termio.h"
#include "../string/string.h"

static volatile uint16_t *video_memory;
static volatile uint16_t terminal_row;
static volatile uint16_t terminal_column;

uint16_t terminal_make_char(const char c, const enum VGA_COLOUR colour)
{
    return (colour << 8) | c;
}

void terminal_init()
{
    video_memory = (uint16_t *)(0xb8000);
    terminal_row = 0;
    terminal_column = 0;
    uint16_t filler_char = terminal_make_char(' ', 0);
    for (uint8_t y = 0; y < VGA_HEIGHT; ++y) {
        for (uint8_t x = 0; x < VGA_WIDTH; ++x) {
            terminal_print_char_x_y(filler_char, x, y);
        }
    }
}

void terminal_print_char_x_y(const uint16_t character, const uint16_t x, const uint16_t y)
{
    video_memory[(y * VGA_WIDTH + x) % (VGA_HEIGHT * VGA_WIDTH)] = character;
}

void terminal_put_char(const uint8_t character, const enum VGA_COLOUR colour)
{
    if (character == '\n') {
        terminal_row = (terminal_row + 1) % VGA_HEIGHT;
        terminal_column = 0;
        return;
    }

    terminal_print_char_x_y(terminal_make_char(character, colour), terminal_column++, terminal_row);

    if (terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        terminal_row = (terminal_row + 1) % VGA_HEIGHT;
    }
}

void terminal_print_string_x_y(const char *str, const enum VGA_COLOUR colour, const uint8_t x, const uint8_t y)
{
    size_t index = y * VGA_WIDTH + x;
    while (*str) {
        video_memory[index++] = terminal_make_char(*str++, colour);
        index %= (VGA_WIDTH * VGA_HEIGHT);
    }
}

void terminal_put_str(const char *str, const enum VGA_COLOUR colour)
{
    while (*str) {
        terminal_put_char(*str++, colour);
    }
}

void print(const char *str)
{
    terminal_put_str(str, 15);
}

void print_char(const char chr)
{
    terminal_put_char(chr, 15);
}
