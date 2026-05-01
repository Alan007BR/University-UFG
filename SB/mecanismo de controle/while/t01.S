.section .rodata

.data
    .globl i
    .align 4
i: .long 0

    .globl total
    .align 4
total: .long 0

.text

.globl t01

t01:
pushq %rbp
movq %rsp, %rbp
### Seu código aqui...

movl i, %eax
loop:
    # (i<5)
    cmpl $5, %eax
    jge afterloop

    #total = total + i
    movl total, %r10d
    addl %eax, %r10d
    movl %r10d, total
    
    #i++
    addl $1, %eax

    jmp loop #sempre volta pro inicio do loop
afterloop:
    movl %eax, i

leave
ret