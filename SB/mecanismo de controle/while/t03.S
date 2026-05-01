.section .rodata
.data

    .globl i
    .align 4
i:  .long 0

    .globl j
    .align 4
j:  .long 0

        .globl total
        .align 4
total:  .long 0

.text
.globl ex03
ex03:
pushq %rbp
movq %rsp, %rbp

### Seu código aqui...
# Dica: Comece zerando %ecx (i) e %eax (total)

movl i, %ecx
movl total, %eax
movl j, %edx

loop_i:
    #(i<3)
    cmpl $3, %ecx
    jge afterloop_i #(i>=3)
    #corpo
    #j = 0
    movl $0, %edx

    loop_j:
        # (j<2)
        cmpl $2, %edx
        jge afterloop_j

        #corpo
        #total = total + i;
        addl %ecx, %eax
        
        #j++
        addl $1, %edx
        jmp loop_j
    afterloop_j:
        # movl %edx, j desnecessário aqui, pq é resetado n, movid para afterloop_i

    #i++
    addl $1, %ecx
    jmp loop_i
afterloop_i:
    movl %ecx, i
    movl %eax, total
    movl %edx, j


leave
ret