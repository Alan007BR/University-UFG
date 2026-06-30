.data



# Definição da variável 'str' aqui...
   .globl str
   .align 1
str: .string "BEBAMUITOCAFE"


.text

.globl process

process:

   pushq %rbp

   movq  %rsp, %rbp




   # ptr = str # se tem asterístico = *ptr se não tem, ptr
   
   # Inicialização de 'ptr' aqui (Obs: utilize %r8 como sendo 'ptr')
   movq $str, %r8 #r8 recebe endereço de l (r8 representa str) #parabén R8 vc é o ptr


beginwhile:

   cmpb $0, (%r8)

   je endwhile            # while() {



   # Bloco do while
   # *ptr = *ptr + 32
   movb (%r8), %al #r8 recebe o valor de str vá na memoria e pegue uma letra
   addb $32, %al # eax recebe eax + 32 some 32 em uma letra
   movb %al, (%r8) #mande de volta na memoria

   # isso tudo ou 
   # adb $32, %r8

   #ptr++
   addq $1, %r8 #addq para mover 1 posições em str (R8)

   


   jmp beginwhile         # }

endwhile:



   leave

   ret