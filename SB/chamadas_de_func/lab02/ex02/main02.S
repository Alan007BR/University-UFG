.section .rodata
fmt: .string "Iteração %d, v = %d\n"


.data
    .globl i
    .align 4
i:  .long  0

    .globl v
    .align 2
v:  .word  0

    .globl vetA
    .align 2
vetA: .word 28, 42, 16, 23, 47

    .globl vetB
    .align 4
vetB: .long 0,0,0,0,0


.text



.globl main

main:

   pushq %rbp
   movq  %rsp, %rbp

    movl i, %ecx

   # Seu código aqui...

    while:
        #_if (i< 5)
        cmp $5, %ecx
        jge afterwhile

        #v = vetA[i] << 2

        #vetA[i] = &vetA + (i * sizeOf)
        movq $vetA, %r8
        movslq %ecx, %r9
        imulq $2, %r9
        addq %r8, %r9

        movw (%r9), %r10w

        shl $2, %r10w #v
        movw %r10w, v

        #printf
        movq $fmt, %rdi
        movl %ecx, %esi
        movswl, %r10w, %edx
        movl $0, %eax
        call printf

        #void process(int x, short v, int *pos);
        movq  $vetB, %r8
        movslq %ecx, %r9
        imulq $4, %r9           # int = 4 bytes
        addq  %r8, %r9
        
        movl %ecx, %edi
        movq  %r9, %rdx         # &vetB[i]
        movw v %si
        call   process
        movl   i, %ecx         # recarrega após call


        incl %ecx
        jmp while
    afterwhile:
        movl %ecx, i
        #void show(int *vet, long size);
        movq $vetB, %rdi
        movq $5, %rsi
        call show

   movl $0, %eax   # return 0
   leave
   ret