#ifndef KERNEL_INTERRUPTS_HEADER_123321
#define KERNEL_INTERRUPTS_HEADER_123321


void isr_0(void);
void isr_1(void);
void isr_2(void);
void isr_3(void);
void isr_4(void);
void isr_5(void);
void isr_6(void);
void isr_7(void);
void isr_8(void);
void isr_9(void);
void isr_10(void);
void isr_11(void);
void isr_12(void);
void isr_13(void);
void isr_14(void);
void isr_15(void);
void isr_16(void);
void isr_17(void);

struct InterruptFrame {
	unsigned long long r15,r14,r13,r12,r11,r10,r9,r8;
	unsigned long long rbp,rdi,rsi,rdx,rcx,rbx,rax;

	unsigned long long interrupt_vector,err_code;

	unsigned long long rip,cs,rflags,rsp,ss;
};

#endif
