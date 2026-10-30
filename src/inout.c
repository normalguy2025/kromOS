#include <inout.h>

unsigned char inb(unsigned short port) {
	unsigned char result=0;
	__asm__ volatile ("inb %1, %0" : "=a" (result) : "Nd" (port));
	return result;
}

