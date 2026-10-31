#ifndef KERNEL_PIC_123321_HEADER
#define KERNEL_PIC_123321_HEADER

void PIC_remap(void);
void PIC_disable(void); 
void PIC_sendEOI(unsigned char irq);
void irq_set_mask(unsigned char irq);
void irq_clear_mask(unsigned char irq);

#endif
