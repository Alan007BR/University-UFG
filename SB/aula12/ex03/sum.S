.section .rodata



fmt: .string "Soma: %ld\n"



.data



# Definição das variáveis aqui...
    .globl sum
    .align 8
sum: .quad 0

    .globl vet
    .align 8
vet: .quad 10, 20, 30, 40, 50

    .globl i
    .align 4
i: .int 4

.text



.globl main

main:

   pushq %rbp

   movq  %rsp, %rbp



   # Inicializações de 'i' e 'ptr' aqui
   movl i, %ecx
   movl $0, i

   movq $vet, %r8 #parabéns, você é o novo ptr #movq pq ponteiro é quad (8)


   # Obs: utilize %ecx para 'i' e %r8 para 'ptr'



beginwhile:

   cmpl $5, %ecx

   jge  endwhile      # while() {



   # Bloco do while aqui...
    #sum = sum + *ptr
    # movq (%r8), %rax
    # addq %rax, sum
    # ou ?
    movq sum, %r10 #move sum pra um registrador

    movq (%r8), %r11 #move o valor apontado por ptr para r11
    addq %r11, %r10 #soma o valor de r11 com r10
    movq %r10, sum #move o resultado de volta para sum

    
    #ptr++
    addq $8, %r8
    #i++
    incl %ecx


   jmp beginwhile     # }

endwhile:



   movq $fmt, %rdi    # printf()

   movq sum, %rsi

   movl $0, %eax

   call printf



   movl $0, %eax      # return 0

   leave

   ret