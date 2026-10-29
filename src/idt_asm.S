.intel_syntax noprefix

// helper functions to get idt working

.global load_idt
.type load_idt, @function

.global get_cs
.type get_cs, @function

load_idt:
	cli
	lidt [rdi]
	ret

get_cs:
	mov ax,cs
	ret
