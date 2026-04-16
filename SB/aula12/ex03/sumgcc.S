	.file	"sum.c"
	.text
	.globl	sum
	.bss
	.align 8
	.type	sum, @object
	.size	sum, 8
sum:
	.zero	8
	.globl	vet
	.data
	.align 32
	.type	vet, @object
	.size	vet, 40
vet:
	.quad	10
	.quad	20
	.quad	30
	.quad	40
	.quad	50
	.section	.rodata
.LC0:
	.string	"Soma: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, -12(%rbp)
	leaq	vet(%rip), %rax
	movq	%rax, -8(%rbp)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	sum(%rip), %rax
	addq	%rdx, %rax
	movq	%rax, sum(%rip)
	addq	$8, -8(%rbp)
	addl	$1, -12(%rbp)
.L2:
	cmpl	$4, -12(%rbp)
	jle	.L3
	movq	sum(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.3) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
