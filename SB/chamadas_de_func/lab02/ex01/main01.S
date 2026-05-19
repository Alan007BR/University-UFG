.section .rodata
fmt: .string "'a' maior do que 'b'\n"
fmt2:.string "Valor de 'b': %d\n"

.data
    .globl a
    .align 1
a:  .byte 97

    .globl b
    .align 1
b:  .byte 105


.text


.globl main

main:
   pushq %rbp
   movq  %rsp, %rbp

   # Seu código aqui...
   # int ret = maximo(a, b);
   # %dil, %sil

   movb a, %dil
   movb b, %sil
   call maximo
   # returno fica em ax
   #%esi -> ret
   movl %eax, %esi
   movsbl a, %r9d # (int)a
   if:
    #ret == a #isso pode, mas duas memorias e duas constantes não
    cmpl %r9d, %esi
    jne else
    
    #printf
    movq $fmt, %rdi
    movl $0, %eax
    call printf

    jmp afterif
   else:

    #printf
    movq $fmt2, %rdi
    movsbl b, %esi
    movl $0, %eax
    call print

   afterif:


   movl $0, %eax   # return 0
   leave
   ret