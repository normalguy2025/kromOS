#include <limine.h>
#include <idt.h>
#include <print.h>
#include <interrupts.h>
#include <inouthelpers.h>
#define NULL ((void*)0)
#define size_t unsigned long long

__attribute__((used, section(".limine_requests_start"))) 
static volatile unsigned long long limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;


__attribute__((used, section(".limine_requests")))
static volatile unsigned long long limine_base_revision[] = LIMINE_BASE_REVISION(6);


__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
	.id=LIMINE_FRAMEBUFFER_REQUEST_ID,
	.revision=0
};	

__attribute__((used, section(".limine_requests_end"))) 
static volatile unsigned long long limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

void hfe(void) {
	for (;;) asm("hlt");
}



struct interrupt_frame;

__attribute__((interrupt)) void int3_handler(struct interrupt_frame* frame) {
	(void)frame;
	hfe();
}

const unsigned char scan_code_set1_us[128] = {
    0,    0x1B, '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  /* 0x00 - 0x09 */
    '9',  '0',  '-',  '=',  '\b', '\t', 'q',  'w',  'e',  'r',  /* 0x0A - 0x13 */
    't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\n', 0,    /* 0x14 - 0x1D (0x1D = LCtrl) */
    'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  /* 0x1E - 0x27 */
    '\'', '`',  0,    '\\', 'z',  'x',  'c',  'v',  'b',  'n',  /* 0x28 - 0x31 (0x2A = LShift) */
    'm',  ',',  '.',  '/',  0,    '*',  0,    ' ',  0,    0,    /* 0x32 - 0x3B (0x36 = RShift, 0x38 = LAlt, 0x3A = Caps) */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x3C - 0x45 (0x3B-0x44 = F1-F10, 0x45 = NumLock) */
    0,    0,    0,    0,    '-',  0,    0,    0,    '+',  0,    /* 0x46 - 0x4F (0x46 = ScrollLock) */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x50 - 0x59 (0x57 = F11, 0x58 = F12) */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x5A - 0x63 */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x64 - 0x6D */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    /* 0x6E - 0x77 */
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0     /* 0x78 - 0x81 */
};

static struct InterruptDescriptor idt[256] = { 0 };

void kmain(void) {
	if (!(LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision))) hfe();

	if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1 ) hfe();

	fill_InterruptDescriptor((struct InterruptDescriptor*)(&idt[3]),&int3_handler,get_cs(),0,0x8E);
	fill_InterruptDescriptor(&idt[0], &isr_0, get_cs(), 0, 0x8E);

	struct IDTR64 idtr = {
		4095,
		(unsigned long long)&idt[0]
	};

	load_idt(&idtr);

	for (unsigned long long i = 0;i<framebuffer_request.response->framebuffer_count;i++) {
		struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[i];

       
        	if (framebuffer->memory_model != LIMINE_FRAMEBUFFER_RGB || framebuffer->bpp != 32) hfe();
        
		init_print(framebuffer);
        	printk("I like kebab",~0);
	}

	unsigned char scancode = 0;
	unsigned char status_keyboard = inb(0x64);
	unsigned char keyboard_input = 0;

	for (;;) {
		status_keyboard = inb(0x64);
		if (status_keyboard&1) {
			scancode = inb(0x60);
		}

		if (scancode&0x80) {
			scancode=0;
			continue;
		}

		
		if (scancode!=0) draw_char(scan_code_set1_us[scancode],~0);
		scancode=0;
	}	

	hfe();
}
