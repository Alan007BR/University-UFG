	.file	"macro.c"
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "Linha 1: a = %d, b = %d\12\0"
.LC1:
	.ascii "Linha 2: a = %d, b = %d\12\0"
.LC2:
	.ascii "Linha 3: a = %d, b = %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movl	$10, -4(%rbp)
	movl	$20, -8(%rbp)
	cmpl	$15, -4(%rbp)
	jle	.L2
	addl	$1, -4(%rbp)
.L2:
	addl	$1, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	leaq	.LC0(%rip), %rcx
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movl	$10, -4(%rbp)
	movl	$20, -8(%rbp)
	addl	$1, -8(%rbp)
	addl	$1, -8(%rbp)
	movl	-8(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	leaq	.LC1(%rip), %rcx
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movl	$10, -4(%rbp)
	movl	$20, -8(%rbp)
	movl	-4(%rbp), %eax
	addl	$11, %eax
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %edx
	movl	-4(%rbp), %eax
	leaq	.LC2(%rip), %rcx
	movl	%edx, %r8d
	movl	%eax, %edx
	call	printf
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev8, Built by MSYS2 project) 15.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
