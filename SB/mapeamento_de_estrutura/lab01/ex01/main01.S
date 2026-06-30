.section .rodata
fmt: .string "color: %ld, filled: %d\n"
.data

.align 8
c1:
    .long 0 # +0: x
    .long 0 # +4: y
    .byte 0 # +8: filled
    .zero 7 # padding
    .quad 0 # +16: color

.text
    .globl main

main:
    pushq %rbp
    movq  %rsp, %rbp

    #c1
    movq $c1, %r10
    #c1.x
    movl $10, (%r10)
    #c1.y
    movl (%r10), %eax
    imull $2, %eax
    movl %eax, 4(%r10)
    #c1.filled
    movb $1, 8(%r10)

    if: # c1.y > 15 ==> c1.y <= 15
        cmpl $15, 4(%r10)
        jle else

        #c1.color = RED
        movq $2, 16(%r10)

        jmp afterif
    else:
        #c1.color = BLUE
        movq $1, 16(%r10)
    afterif:

    movq $fmt, %rdi       #1 param fmt
    movq 16(%r10), %rsi   #2 param c1.color
    movsbl 8(%r10), %edx  #3 param (int)c1.fill
    movl $0, %eax
    call printf

    movl $0, %eax
    leave
    ret