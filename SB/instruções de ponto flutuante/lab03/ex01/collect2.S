.section .rodata
fmt: .string "Fail: sum = %f, limit = %f, count = %d\n"

        .align 4
const0: .float 0.0
.data
.text
    .globl collect

collect:

    pushq %rbp
    movq %rsp, %rbp

    subq $80, %rsp

    #salvando verdes
    movq %rbx, -64(%rbp)

    movss const0, %xmm6
    movss %xmm6, -4(%rbp)   # sum = 0.0
    movss %xmm0, -72(%rbp)

    movss %xmm7, -4(%rbp)

    # ebx --> i
    movl $0, %ebx

    #salvando antes de chamar
    movq %rdi, -40(%rbp)
    movq %rsi, -48(%rbp)
    movq %xmm7,-56(%rbp)
    movq %xmm0,-72(%rbp)

    leaq -32(%rbp), %rdi
    call t_init

    #restaurando
    movq -40(%rbp), %rdi
    movq -48(%rbp), %rsi
    movq -56(%rbp), %xmm7
    movq -72(%rbp), %xmm0


    while:
        cmpl %esi, %ebx     #esi --> count ebx --> i
        jae afterwhile

        #ptr[i].sum < limit
        #ptr[i].sum
        movq    %rdi, %r8      #&ptr
        movslq  %ebx, %r9      #(long)i
        imulq   $8, %r9        #(long)i * sizeOf
        addq    %r8, %r9       #&ptr + (long)i

        movss (%r9), %xmm2     #xmm2 = ptr[i].sum

        if_01:
            movss -72(%rbp), %xmm8
            ucomiss %xmm8, %xmm2
            jp  else_01
            jae else_01

            #sum = sum + (t.repeated * ptr[i].sum);
            #t.repeated
            movl -16(%rbp), %r10d    #%r10d = -32+16(offset do repeated)

            cvtsi2ss %r10d, %xmm7    #xmm7 = (float)t.repeated
            mulss %xmm2, %xmm7       #xmm7 = (t.repeated * ptr[i].sum)

            movss -4(%rbp), %xmm11
            addss %xmm7, %xmm11     #sum = sum + (t.repeated * ptr[i].sum)
            movss %xmm11, -4(%rbp) 

            jmp afterif_01
        else_01:

            #salvando antes de chamar
            movq %rdi, -40(%rbp)
            movq %rsi, -48(%rbp)
            movq %xmm7,-56(%rbp)
            movq %xmm0,-72(%rbp)

            movq $fmt, %rdi
            movl $2, %eax
            movl -48(%rbp), %esi

            cvtss2sd %xmm0, %xmm1  #(double)limit
            cvtss2sd %xmm2, %xmm0  #(double)ptr[i].sum
            call printf

            #restaurando
            movq -40(%rbp), %rdi
            movq -48(%rbp), %rsi
            movq -56(%rbp), %xmm7
            movq -72(%rbp), %xmm0

            #ptr[i].sum
            movq    %rdi, %r8      #&ptr
            movslq  %ebx, %r9      #(long)i
            imulq   $8, %r9        #(long)i * sizeOf
            addq    %r8, %r9       #&ptr + (long)i

            movl 4(%r9), %r11d     #r11d = ptr[i].fail

            incl %r11d
            movl %r11d, 4(%r9)

        afterif_01:

        incl %ebx
        jmp while
    afterwhile:


    #restaurando verdes
    movq -64(%rbp), %rbx

    movss -4(%rbp), %xmm0

    leave
    ret

#pilha
# sum   -> -4       
# t     -> -32
# rdi   -> -40
# rsi   -> -48
# xmm7  -> -56
# ebi   -> -64
# xmm0  -> -72

#temperatura    align 8
# scale     -> 0    0
# padding   -> 1    1..7
# value     -> 8    8..15
# repated   -> 16   16..19
# padding   -> 20   20..23   
# tamanho = 24 bytes

#data   align 4
# sum   -> 4
# fail  -> 8
# tamanho = 8 bytes