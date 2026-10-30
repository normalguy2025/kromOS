#include <limine.h>
#include <print.h>
#include <interrupts.h>
#include <inout.h>
#include <bootinfo.h>
#define NULL ((void*)0)
#define size_t unsigned long long

void hfe(void) { 
	__asm__ volatile ("cli");
	for(;;) __asm__ volatile ("hlt");
}

static struct InterruptDescriptor idt[256] = { 0 };

void kmain(void) {
	struct BootInfo* bootinfo = get_bootinfo();
	if (!(LIMINE_BASE_REVISION_SUPPORTED(bootinfo->base_revision))) hfe();

	if (bootinfo->framebuffer_request->response == NULL || bootinfo->framebuffer_request->response->framebuffer_count < 1 ) hfe();

	fill_InterruptDescriptor((struct InterruptDescriptor*)(&idt[3]),&isr_3,get_cs(),0,0x8E);
	fill_InterruptDescriptor(&idt[0], &isr_0, get_cs(), 0, 0x8E);

	struct IDTR64 idtr = {
		4095,
		(unsigned long long)&idt[0]
	};

	load_idt(&idtr);

	struct limine_framebuffer *framebuffer = bootinfo->framebuffer_request->response->framebuffers[0];
	init_print(framebuffer);
        printk("I like kebab",~0);
	

	hfe();
}
