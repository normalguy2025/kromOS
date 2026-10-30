

#include <interrupts.h>

void fill_InterruptDescriptor(struct InterruptDescriptor* IDptr,void* offset,unsigned short selector,unsigned char ist,
unsigned char type_attribute) {
	if(IDptr==((void*)0)) return; //do nothing if IDptr is NULL
	IDptr->offset_1 = (unsigned long long)offset & 0xFFFF;
	IDptr->selector = selector;
	IDptr->ist = ist & 0x07;
	IDptr->type_attrib = type_attribute;
	IDptr->offset_2 = ((unsigned long long)offset >> 16) & 0xFFFF;
	IDptr->offset_3 = ((unsigned long long)offset >> 32) & 0xFFFFFFFF;
	IDptr->zero = 0;
	return;
}

void load_idt(struct IDTR64* idtr) {
	__asm__ volatile ("cli");
	__asm__ volatile ("lidt %0" : :  "m"(*idtr) : "memory");

}

unsigned short get_cs(void) {
	unsigned short ax;

	__asm__ volatile ("mov %%cs, %0" : "=r"(ax));
	return ax;
}

