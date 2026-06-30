	.data
    .globl c
    .align 1
c:  .byte 67

    .globl s
    .align 2
s:  .short 23

    .globl i
    .align 4
i:  .long 0

	.globl j
	.align 4
j: 	.long 0

    .globl l
    .align 8
l:  .quad 1023

    .globl ui
    .align 4
ui: .long 2047

    .globl ul
    .align 8
ul: .quad 4095

	.globl ptr
	.align 8
ptr: .short	0

	.text



#---------------------------------------------------------------------------------

	.globl atribuicoes

atribuicoes:

	pushq %rbp

	movq  %rsp, %rbp



	# Se necessário, usar apenas os registradores (ou suas variações) abaixo:

	# %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11



	# Seu código aqui...
    movb $93, c
    movw $75, s
    movl $52, j
    movq $7265, l

    #i = j;
    movl j, %r10d
    movl %r10d, i



	leave

	ret



#---------------------------------------------------------------------------------

	.globl cast

cast:

	pushq %rbp

	movq  %rsp, %rbp



	# Se necessário, usar apenas os registradores (ou suas variações) abaixo:

	# %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11



	# Seu código aqui...
    #ui = i
    movl i, %r10d
    movl %r10d, ui

    #j = s
    movswl s, %r10d #pega s (16bits) e faz sign extension pra 32bits
    movl %r10d, j #armazena em j

    # ul = ui
    movl ui, %edx # zero extension 
    movq %rdx, ul

    #s = c + j
    movsbl c, %r10d
    addl j, %r10d
    movw %r10w, s
    
	leave

	ret



#---------------------------------------------------------------------------------

	.globl expressoes

expressoes:

	pushq %rbp

	movq  %rsp, %rbp



	# Se necessário, usar apenas os registradores (ou suas variações) abaixo:

	# %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11



	# Seu código aqui...
	#i = j * s
	movswl s, %r10d #16bits to 32bits
	imull j,%r10d
	movl %r10d, i

	#j = 1 + (s*3)
	movswl s, %r10d #16 to 32
	imull $3, %r10d
	addl $1, %r10d
	movl %r10d, j

	#ui = 2 * (i + s * 2)
	movswl s, %r10d #16 to 32
	imull $2, %r10d
	addl i, %r10d
	imull $2, %r10d
	movl %r10d, ui

	#ul = (l + j * 3) - (s + 1024)
	movslq j, %rax # j -> 64 bits (sign)
	movq l, %r11
	imulq $3, %rax # J * 3
	addq %r11, %rax # l + J * 3 
	
	movswq s, %r10 # s -> 64 bits (sign)
	addq $1024, %r10 # s + 1024

	subq %r10, %rax # expre 1 - expre 2
	movq %rax, ul # salvar tudo em ul


	leave

	ret



#---------------------------------------------------------------------------------

	.globl bitAbit

bitAbit:

	pushq %rbp

	movq  %rsp, %rbp



	# Se necessário, usar apenas os registradores (ou suas variações) abaixo:

	# %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11



	# Seu código aqui...
	# c = c & 0x0F;
	movb c, %cl
	andb $0x0F, %cl
	movb %cl, c

	# s = s | 0x80
	movw s, %ax
	orw $0x80, %ax
	movw %ax, s

    # i = i ^ 0x55;
	movl i, %r10d
	xorl $0x55, %r10d
	movl %r10d, i

    # j = (j | s) ^ c;
	movl j, %r10d
	movswl s, %r11d # 16bits to 32bits
	movswl c, %r9d #8bits to 32bits

	orl %r11d, %r10d
	xorl %r9d, %r10d
	movl %r10d, j

	# l = l >> 2;
	movq l, %r11
	sarq $2, %r11
	movq %r11, l

	# ui = ui << 1;
	movl ui, %r11d
	shll $1, %r11d
	movl %r11d, ui

    # ul = ul >> 4;
	movq ul, %r11
	shrq $4, %r11
	movq %r11, ul

	leave

	ret



#---------------------------------------------------------------------------------

	.globl ponteiros

ponteiros:

	pushq %rbp

	movq  %rsp, %rbp



	# Se necessário, usar apenas os registradores (ou suas variações) abaixo:

	# %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11



	# Seu código aqui...
	# short *ptr;
	movq $ptr, %r11 #parabéns, você é o ptr

	#ptr = &s;
	movq $s, %r11
	movq %r11, ptr

	#*ptr = 128
	movw $128, (%r11)

	#finalmente
	leave

	ret