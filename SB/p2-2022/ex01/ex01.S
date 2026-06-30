.section .rodata
#nada
.data
    .globl vet
    .align 4
vet: .long 10,20,10,40,20

.text
    .globl calc

calc:
#param 1: int*resp (rdi)
#param 2: int mark (esi)

pushq %rbp
movq %rsp, %rbp

#i --> %edx
movl $0, %edx

while:
cmpl $5, %edx # (i < 5) --> i>=5
jge afterwhile

#vet[i]
movq $vet, %r8
movslq %edx, %r9
imulq $4, %r9
addq %r8, %r9

movl (%r9), %r10d #vet[i]

if:
cmpl %esi, %r10d # (vet[i] == mark --> vet[i] != mark)
jne else

movl %r10d, (%rdi)

jmp afterif
else:

movl (%rdi), %esi

afterif:

incl %edx
jmp while
afterwhile:

#void sem retorno
leave
ret