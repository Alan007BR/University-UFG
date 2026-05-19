.section .rodata
.data
.text
    .globl fat

# di, si, dx, cx, r8, r9
#ax - return
fat:
    pushq %rbp
    movq %rsp, %rbp

    subq $16, %rsp #rsp controla alocação da pilha alinha em multiplos de 16

    if:
        cmpl $0, %edi   #n>0 --> n<=0
        jle afterif

        movq %rdi, -8(%rbp) # antes de chamar func salvar registradores chamadora

        #fat(n-1) * n;
        decl %edi  # n - 1
        call fat

        movq -8(%rbp), %rdi

        imull %edi, %eax #return automatico
        jmp afterret
    afterif:

    movl $1, %eax

    afterret:
    leave
    ret