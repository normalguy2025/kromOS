#ifndef KERNEL_BOOTINFO_123321_HEADER
#define KERNEL_BOOTINFO_123321_HEADER

struct BootInfo {
	unsigned long long* base_revision;
	struct limine_framebuffer_request* framebuffer_request;
};

struct BootInfo* get_bootinfo();



#endif
