.section .rodata
.data
.text
    .globl calc

#di,si, dx, cx, r8, r9
calc:

pushq %rbp
movq %rsp, %rbp

// i --> %ecx
// j --> %r8d
movl $0, %ecx
movl $4, %r8d

# salvando registradores
movq %rcx, -48(%rbp)
movq %r8,  -56(%rbp)

leaq -24(%rbp), %rdi
movl $5, %esi
movl %ecx, %edx
call filli

#recuperando registradores
movq -48(%rbp), %rcx
movq -56(%rbp), %r8

# salvando registradores
movq %rcx, -48(%rbp)
movq %r8,  -56(%rbp)

leaq -34(%rbp), %rdi
movl $5, %esi
movl %r8d, %edx
call fills

#recuperando registradores
movq -48(%rbp), %rcx
movq -56(%rbp), %r8

movl $0, -4(%rbp)

for:
    cmpl $5, %ecx   #i < 5 --> i >= 5
    jge afterfor

    #vet[1] = addr + (i * sizeOf)
    leaq -24(%rbp), %r9
    movslq %ecx, %r10
    imulq $4, %r10
    addq %r9, %r10

    movl (%r10), %edi

    #vet[2] = addr + (i * sizeOf)
    leaq -34(%rbp), %r9
    movslq %r8, %r10
    imulq $2, %r10
    addq %r9, %r11

    movswl (%r11), %esi

    # sum + vet1[i]
    addl -4(%rbp), %edi
    addl %esi, %edi         # + vet2[j]
    movl %edi, -4(%rbp)     # sum = ...

    incl %ecx
    decl %r8d
    jmp for
afterfor:


movl -4(%rbp), %eax
leave
ret