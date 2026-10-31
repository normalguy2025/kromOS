#ifndef KERNEL_INOUT_HELPERS_123321
#define KERNEL_INOUT_HELPERS_123321

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);
void io_wait(void);

#endif

