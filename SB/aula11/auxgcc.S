	.file	"aux.c"
	.text
	.globl	c
	.data
	.type	c, @object
	.size	c, 1
c:
	.byte	-20
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	-256
	.globl	j
	.align 4
	.type	j, @object
	.size	j, 4
j:
	.long	512
	.globl	l
	.align 8
	.type	l, @object
	.size	l, 8
l:
	.quad	128
	.globl	us
	.align 2
	.type	us, @object
	.size	us, 2
us:
	.value	111
	.globl	ui
	.align 4
	.type	ui, @object
	.size	ui, 4
ui:
	.long	1024
	.globl	ul
	.align 8
	.type	ul, @object
	.size	ul, 8
ul:
	.quad	2048
	.text
	.globl	aux
	.type	aux, @function
aux:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$68000, j(%rip)
	movq	$4096, l(%rip)
	movl	j(%rip), %eax
	movl	%eax, i(%rip)
	movl	i(%rip), %eax
	addl	$5, %eax
	movl	%eax, j(%rip)
	movl	i(%rip), %eax
	leal	(%rax,%rax), %edx
	movl	j(%rip), %eax
	leal	5(%rax), %ecx
	movl	%edx, %eax
	subl	%ecx, %eax
	movl	%eax, i(%rip)
	movl	i(%rip), %eax
	movl	%eax, ui(%rip)
	movzbl	c(%rip), %eax
	movsbl	%al, %eax
	movl	%eax, j(%rip)
	movl	ui(%rip), %eax
	movl	%eax, %eax
	movq	%rax, ul(%rip)
	movq	ul(%rip), %rax
	movw	%ax, us(%rip)
	movl	i(%rip), %eax
	movl	%eax, %edx
	movl	j(%rip), %eax
	addl	%edx, %eax
	movb	%al, c(%rip)
	leaq	l(%rip), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	$128, (%rax)
	leaq	i(%rip), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %edx
	movl	j(%rip), %eax
	addl	%edx, %eax
	movl	%eax, j(%rip)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	aux, .-aux
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
