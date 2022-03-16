#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "kernel/vga.h"


static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

static inline unsigned char vga_to_char(uint16_t vga) {
	return (unsigned char) (vga & 255);
}

void terminal_initialize(void) {
    setup_cursor();
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}


void terminal_clearrow(size_t row) {
	for (size_t x = 0; x < VGA_WIDTH; x++) {
		const size_t index = row * VGA_WIDTH + x;
		terminal_buffer[index] = vga_entry(' ', terminal_color);
	}
}


void terminal_moveup() {
	// memmove(terminal_buffer, terminal_buffer+VGA_WIDTH, sizeof(uint16_t) * VGA_WIDTH * (VGA_HEIGHT-1));
	terminal_clearrow(0);
	memmove(terminal_buffer, terminal_buffer+VGA_WIDTH, sizeof(uint16_t) * VGA_WIDTH * (VGA_HEIGHT-1));
	terminal_column = 0;
	terminal_row = VGA_HEIGHT-1;
	terminal_clearrow(terminal_row);
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{ 
	bool new_line = false;
	if (c == '\n') {
		new_line = true;
		terminal_column = 0;
		++terminal_row;
	}
	else {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
	if ((terminal_row >= VGA_HEIGHT-1 && terminal_column == VGA_WIDTH) || terminal_row > VGA_HEIGHT-1)
	{
		terminal_moveup();
	}
	if (!new_line){
		terminal_column++;
	}
    if (terminal_column == VGA_WIDTH && !new_line) {
        terminal_column = 0;
        ++terminal_row;
    }
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++) {
		terminal_putchar(data[i]);
	}
}

void terminal_writestring(const char* data) {
    update_cursor(terminal_row, terminal_column);
	terminal_write(data, strlen(data));
}


void remove_cursor() {
    disable_cursor();
}

void setup_cursor(){
    enable_cursor(0, 16);
    update_cursor(0, 0);
}
