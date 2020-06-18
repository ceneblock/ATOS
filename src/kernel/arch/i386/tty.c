#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/tty.h>
 
#include "vga.h"
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

/**
 * @brief initialize the terminal buffer and fill it with ' '
 */
void terminal_initialize(void) {
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
 
/**
 * @brief set the terminal color
 * @input color the desired color
 */
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
/**
 * @brief sets the location of the buffer for data to put in
 * @param c the character to enter
 * @param color the color to enter
 * @param x the x location
 * @param y the y location
 */
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
/**
 * @brief put the character at the next valid location in the buffer
 * @param c the character to place
 */
void terminal_putchar(char c) {
	unsigned char uc = c;
	terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

/**
 * @brief writes a fixed length data to the terminal buffer
 * @param data the array to write to the terminal buffer
 * @param size how long the array is
 */
void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
/**
 * @brief writes a string to the terminal buffer
 * @param data a string to write to the terminal buffer
 */
void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}
