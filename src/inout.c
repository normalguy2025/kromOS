#include <inout.h>

unsigned char inb(unsigned short port) {
	unsigned char result=0;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

void outb(unsigned char value, unsigned short port) {
	__asm__ volatile ("outb %0, %1" : : "a"(value), "dN"(port));
	return;
}
