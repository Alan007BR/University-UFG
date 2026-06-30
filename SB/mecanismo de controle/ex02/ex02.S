.section .rodata



.data
   .globl a
   .align 4
a: .long 0

   .globl b
   .align 8
b: .quad 2


.text

.globl ex02

ex02:

   pushq %rbp

   movq  %rsp, %rbp



   # Seu código aqui...
   # _if(a) = if (a != 0)
   movl a, %eax
   cmpl %eax, %eax
   jne end_if


   end_if:

      # _if (b<5) = b>=5
      movq b, %rax
      cmpq $5, %rax
      jge if2_else
         end_if2:
            # b = (a << 1) + (a * b);
            movslq a, %r10

            #(a<<1) r11 = a<<1
            movq %r10, %r11
            shlq $1, %r11

            #(a*b)   r9 =  (a*b)
            movq b, %r9
            imulq %r10, %r9

            # b = (a << 1) + (a * b);
            addq %r11, %r9
            movq %r9, b

            jmp depois_if
         if2_else:
            # a = b ^ 0x1FL;
            movq b, %r11
            xorq $0x1F, %r11
            movl %r11d, a

         depois_if:

   leave

   ret