
#ifndef KERNEL_IDT_HEADER_123321
#define KERNEL_IDT_HEADER_123321

struct InterruptDescriptor {
	unsigned short offset_1;		//offset bits 15-0
	unsigned short selector;		//code segment selector
	unsigned char  ist;			//bits 2-0 have ist offset rest are zero
	unsigned char  type_attrib;		//gate type,dpl and p fields
	unsigned short offset_2;		//offset bits 31-16
	unsigned int   offset_3;		//offset bits 63-32
	unsigned int   zero;			//reserved zero
} __attribute__((packed));

struct IDTR64 {
	unsigned short size;
	unsigned long long offset;
} __attribute__((packed));

void fill_InterruptDescriptor(struct InterruptDescriptor* IDptr,void* offset,unsigned short selector,unsigned char ist, unsigned char type_attribute);

void load_idt(struct IDTR64* idtr);
unsigned short get_cs();

#endif
