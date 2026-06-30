.section .rodata



.data
    .globl v1
    .align 2
v1: .word  32, 34, 27, 4

    .globl v2
    .align 4
v2: .long  12, 22, 31, 23, 6

    .globl v3
    .align 1
v3: .byte  0, 0, 0, 0

    .globl v4
    .align 8
v4: .quad  0, 0, 0, 0, 0, 0, 0, 0

    .globl i
    .align 4
i:  .long  0

    .globl j
    .align 2
j:  .word  0
.text

.globl aux

aux:
pushq %rbp
movq  %rsp, %rbp

movl $0, i
for:
cmpl $4, i # i < 4 --> i >= 4
jge afterfor

movl $0, j

    while:
    cmpw $5, j
    jge afterwhile

        if:
        movswl j, %edx
        cmpl %edx, i # i == j --> i != j
        jne else

        #v1[i]
        movq $v1, %r8
        movslq i, %r9
        imulq $2, %r9 #(i * sizeOf)
        addq %r8, %r9 #&v1 + (i * sizeOf)
        movw (%r9), %r10w  #v1[i]

        #v2[j]
        movq $v2, %rcx
        movslq %edx, %rsi
        imulq $4, %rsi      #(j * sizeOf)       
        addq %rcx, %rsi     #&v2 + (j * sizeOf)
        movl (%rsi), %r8d   #v2[j]

        # v3[i]
        movq $v3, %rax
        movslq i, %rdi
        imulq $1, %rdi
        addq %rax, %rdi
        movb (%rdi), %r11b #v3[i]

        movswl %r10w, %r10d
        addl %r10d, %r8d  #(v1[i] + v2[j])

        movb %r8b, (%rdi)  #v3[i] = v1[i] + v2[j];
        

        jmp afterif
        else:

        #v1[i]
        movq $v1, %r8
        movslq i, %r9
        imulq $2, %r9 #(i * sizeOf)
        addq %r8, %r9 #&v1 + (i * sizeOf)
        movw (%r9), %r10w  #v1[i]

        #v2[j]
        movq $v2, %rcx
        movslq %edx, %rsi
        imulq $4, %rsi      #(j * sizeOf)       
        addq %rcx, %rsi     #&v2 + (j * sizeOf)
        movl (%rsi), %r8d   #v2[j]

        #v4[i + j]

        # v4[i+j]
        movl i, %eax
        addl %edx, %eax     # eax = i + j
        movq $v4, %rax
        movslq %edx, %rdi
        imulq $8, %rdi
        addq %rax, %rdi
        movb (%rdi), %r11 #v4[i+j]

        movswl %r10w, %r10d
        addl %r10w, %r8d  #(v1[i] + v2[j])

        movslq %r8d, %r8
        addq   %r8, (%rdi)    # v4[i+j] += (long)(v1[i] + v2[j])

        afterif:


    incw j
    jmp while
    afterwhile:


incl i
jmp for
afterfor:


leave
ret 