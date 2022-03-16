#include <stdbool.h>
#include <stddef.h>
#include <kernel/tty.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();

    // for (size_t y=0; y < VGA_HEIGHT; y++) 
	for (size_t y=0; y < 100; y++) {
		terminal_writestring("Hello, kernel World!\n");
	}
	while (true) {
		terminal_writestring("Check.\n");
	}
}