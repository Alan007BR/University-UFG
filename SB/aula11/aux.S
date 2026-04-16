.data
    # Variáveis globais
    .globl c
    .align 1
c:  .byte -20

    #int i = -256;
    .globl i
    .align 4
i:  .int -256

    # int j = 512
    .globl j
    .align 4
j: .int 128

    #long l = 512;
    .globl l
    .align 8
l:  .quad 128

    # unsigned short us = 111;
    .globl us
    .align 2
us: .short 111

    # unsigned int ui = 1024;
    .globl ui
    .align 4
ui: .int 1024

    # unsigned long ul = 2048;
    .globl ul
    .align 8
ul: .quad 2048

.text



.globl aux

aux:

    pushq %rbp

    movq  %rsp, %rbp



    # Se necessário, usar apenas os registradores (ou suas variações) abaixo:

    # %rax, %rcx, %rdx, %rdi, %rsi, %r8, %r9, %r10, %r11


    # Seu código aqui...
    # j = 68000
    movl $68000, j
    movq $4096, l

    # não pode memória - memória, então mover para os registradores
    movl j, %rax
    movl %rdi, i

    // artiméticas - o resultado só pode ficar no registrador
    // se for necessário dar mov pra memória
    #   j = 10 + i - 5;
    movl i, %eax    # cópia de i para o registrador eax
    addl $10, %eax  # +10
    subl $5, %eax   # -5
    movl %eax, j    # mover o valor final copiado no registrado para j

    #  i = (i * 2) - (j + 5);
    movl i, %rcx
    imull $2, %rcx

    movl j, %edx
    addl $5, %edx

    subl %edx, %ecx # = edx - ecx

    movl %edx, i

    # ui = i;
    movl i, %edx
    movl %edx, ui

    # j = c
    movsbl c, %eax

    #ul = ui
    movl ui, %r8
    movq %r8, %ul

    #us = ul; truncamento
    movq ul, %rax
    movw %ax, us #ax é um pedçao de rax, os 16 bits menos significativos, então estamos pegando os dois bytes menos significativos de ul e movendo para us, que é um short (2 bytes), então é um truncamento

    # c = i + j;

    # long *ptr;  ponteiros
    #acesso indireto
    movq $l, %r10  #r10 recebe o endereço de l
    movq $128, (%r10) #l recebe 128, usando acesso indireto

    #int *iptr;        // Utilize um registrador para representar 'iptr'
    #iptr = &i;
    #j = j + *iptr;

    movq $i, %r11 # r11 recebe o endereço de i
    movl (%r11), %eax # eax recebe o valor de i, usando acesso indireto
    addl %eax, j # j recebe j + valor de i


    leave

    ret