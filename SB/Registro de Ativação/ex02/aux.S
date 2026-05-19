.section .rodata
fmt: .string "Iteração %d, v = %d\n"

.data
    .globl i
    .align 4
i: .long 0

    .globl v
    .align 2
v:  .word 0

    .globl vetA
    .align 2
vetA: .short 28, 42, 16, 23, 47

    .globl vetB
    .align 4
vetB:   .long 0, 0, 0, 0, 0


.text
    .globl aux

aux:

pushq %rbp
movq %rsp, %rbp

subq $16, %rsp

#i -> %ecx
movl $0, %ecx
while:
    cmpl $5, %ecx
    jge afterwhile

    #vetA[i] 

    movq $vetA, %r8 # &vetA
    movslq %ecx, %r9 # i
    imulq $2, %r9   #i * sizeOF
    addq %r8, %r9   #&vetA[i]
    movw (%r9), %r10w   # r10w = vetA[i]

    shlw $2, %r10w  #vetA[i] << 2;
    movw %r10w, v  # v = vetA[i] << 2;

    # salva i
    movq %rcx, -8(%rbp)

    #printf("Iteração %d, v = %d\n", i, (int)v);
    movq $fmt, %rdi
    movl %ecx, %esi # 2 param SI
    movswl v, %edx
    movl $0, %eax
    call printf

    #restaura i
    movq -8(%rbp), %rcx

    #&vetB[i]
    movq $vetB, %r8
    movslq %ecx, %r9
    imulq $4, %r9
    addq %r8, %r9 # &vetB[i]

    #Process
    movl %ecx, %edi
    movw v, %si
    movq %r9, %rdx

    # salva i
    movq %rcx, -8(%rbp)

    call process

    # restaura i
    movq -8(%rbp), %rcx

    incl %ecx
    jmp while
afterwhile:

    movq $vetB, %rdi
    movq $5, %rsi
    call show


movl $0, %eax
leave
ret