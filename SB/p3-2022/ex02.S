.section .rodata
.data
.text
    .globl foo
    .globl init

# void foo(char a, long b, short c)
# a -> %dil
# b -> %rsi
# c -> %dx
foo:
    pushq %rbp
    movq %rsp, %rbp

    # Aloca 112 bytes para manter a pilha alinhada a 16 (112 é múltiplo de 16)
    subq $112, %rsp

    movq %r15, -8(%rbp)

    # j = 0
    movw $0, -10(%rbp)

    # i = 0
    movl $0, %r15d

    movb %dil, -88(%rbp)        # a
    movq %rsi, -96(%rbp)        # b
    movw %dx, -104(%rbp)        # c

    # struct Y *ptr = init(vet, i)
    leaq -80(%rbp), %rdi        # 1 param: &vet
    movl %r15d, %esi            # 2 param: i
    call init

    # ptr = retorno
    movq %rax, %rcx             # ptr fica em %rcx

    movb -88(%rbp), %dil        # a
    movq -96(%rbp), %rsi        # b
    movw -104(%rbp), %dx        # c

while:
    # while (ptr->flag > a)  => cmp(a, ptr->flag) <= 0 sai
    cmpb %dil, 8(%rcx)
    jle afterwhile

    # ptr->flag = (char)(b * j);
    movswq -10(%rbp), %r8       # r8 = (long)j
    imulq %rsi, %r8             # r8 = b * j
    movb %r8b, 8(%rcx)          # ptr->flag = (char)r8

if:
    # _if (ptr->values[j] == c)
    movswq -10(%rbp), %r9       # r9 = (long)j
    movw 10(%rcx, %r9, 2), %r10w # r10w = ptr->values[j]
    
    cmpw %dx, %r10w
    jne afterif

    # ptr = &vet[i]
    leaq -80(%rbp), %r8         # r8 = &vet
    movslq %r15d, %r9           # r9 = (long)i
    imulq $32, %r9              # r9 = i * sizeof(struct Y)
    addq %r8, %r9               # r9 = &vet[i]
    
    movq %r9, %rcx              # ptr = &vet[i]

    # i++
    incl %r15d

afterif:
    # j++
    incw -10(%rbp)

    # process(ptr, c, a)
    
    movq %rcx, -112(%rbp)

    movb -88(%rbp), %dl         # 3 param: a (char z)
    movw -104(%rbp), %si        # 2 param: c (short w)
    movq %rcx, %rdi             # 1 param: ptr (struct Y *v)
    
    call process

    movq -112(%rbp), %rcx
    movb -88(%rbp), %dil
    movq -96(%rbp), %rsi
    movw -104(%rbp), %dx

    jmp while

afterwhile:
    # restaurando callee-saved
    movq -8(%rbp), %r15

    leave
    ret


init:
    # A função init pode ser MUITO mais simples. 
    movslq %esi, %rax           # rax = (long)pos
    imulq $32, %rax             # rax = pos * 32 (tamanho da struct)
    addq %rdi, %rax             # rax = &v + (pos * 32)
    ret

# Pilha:
# -8(%rbp)   -> r15 (callee-saved, 8 bytes)
# -10(%rbp)  -> j (short, 2 bytes)
# -16(%rbp)  -> padding (6 bytes para alinhar o vet em múltiplo de 8)
# -80(%rbp)  -> vet[2] (64 bytes -> começa no -80 e vai até o -17)
# -88(%rbp)  -> a (salvo, 8 bytes)
# -96(%rbp)  -> b (salvo, 8 bytes)
# -104(%rbp) -> c (salvo, 8 bytes)
# -112(%rbp) -> backup do rcx(ptr) antes da chamada process

# struct Y  align 8     tam
# limit -> offset 0     0..7
# flag  -> offset 8     8
# p     -> offset 9     9
# values-> offset 10    10..25
# p     -> offset 26    26..32 

