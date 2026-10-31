#include <inout.h>

unsigned char inb(unsigned short port) {
	unsigned char result=0;
	__asm__ volatile ("inb %w1, %b0" : "=a" (result) : "Nd" (port) : "memory");
	return result;
}

void outb(unsigned short port,unsigned char value) {
	__asm__ volatile ("outb %b0, %w1" : : "a"(value), "Nd"(port) : "memory");
	return;
}

void io_wait(void) {
	outb(0x80,0);
	return;
}
