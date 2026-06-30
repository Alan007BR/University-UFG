.section .rodata
str: .string "Hello"


.data
    .globl val
    .align 4
val: .long 432

    .globl age
    .align 2
age: .word 4

    .globl r
    .align 4
r: .long 0

    .globl err
    .align 8
err: .quad 2048

.text

.globl main
#di,si,dx,cx,r8,r9
main:

   pushq %rbp

   movq  %rsp, %rbp

    movq $str, %rdi
    movl val, %esi
    movw age, %dx
    movq $r, %rcx
    call sum

    movl %eax, val

    movq err, %rdi
    movl val, %esi
    movl r, %edx

    movl $0, %eax
   leave
   ret