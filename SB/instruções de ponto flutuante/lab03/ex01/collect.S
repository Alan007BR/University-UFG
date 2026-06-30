.section .rodata
fmt: .string "Fail: sum = %f, limit = %f, count = %d\n"
fmt2: .string "oi"
        .align 4
const0: .float 0.0

.data
.text
    .globl collect

collect:
    pushq %rbp
    movq %rsp, %rbp

    subq $80, %rsp

    # salvando verdes
    movq %rbx, -40(%rbp)


    movss const0, %xmm5
    movss %xmm5, -4(%rbp)   #sum = 0.0

    movl $0, %ebx

    #salvando antes da chamada
    movq %rdi, -48(%rbp)
    movq %rsi, -56(%rbp)
    movss %xmm0, -64(%rbp)
    movq %rdx, -72(%rbp) 

    #t_init(&t)
    leaq -32(%rbp), %rdi
    call t_init

    #restaurando dps da chamada
    movq -48(%rbp), %rdi
    movq -56(%rbp), %rsi
    movss -64(%rbp), %xmm0
    movq -72(%rbp), %rdx
    
    while:
        cmpl %edx, %ebx #count, i
        jge afterwhile

        if:
            movq %rdi, %r8 #&ptr
            movslq %ebx, %r9
            imulq $8, %r9
            addq %r8, %r9

            movss (%r9), %xmm6 #xmm6 = ptr[i].sum

            ucomiss %xmm0, %xmm6
            jp  else
            jae else            # em xmm sempre se utiliza jb/ja

            #sum = sum + (t.repeated * ptr[i].sum);
            #t.repeated = &t + offset de repeated
            leaq -32(%rbp), %r8
            addq $16, %r8
            movl (%r8), %r11d    #r11 = t.repeated

            cvtsi2ss %r11d, %xmm7   #xmm7 = (float)t.repeated

            #(t.repeated * ptr[i].sum)
            mulss %xmm6, %xmm7  # xmm7 = (t.repeated * ptr[i].sum)
            movss -4(%rbp), %xmm8
            addss %xmm7, %xmm8
            movss %xmm8, -4(%rbp)    #?

            jmp afterif
        else:

            #salvando
            movq %rdi, -48(%rbp)
            movq %rsi, -56(%rbp)
            movss %xmm0, -64(%rbp)
            movq    %rdx,-72(%rbp) 


            movq $fmt, %rdi         #1 param
            cvtss2sd %xmm0, %xmm1   #3 param
            cvtss2sd %xmm6, %xmm0   #2 param
            movl %edx, %ecx         #4 param
            movl $0, %eax
            call printf


            #restaurando
            movq -48(%rbp), %rdi
            movq -56(%rbp), %rsi
            movss -64(%rbp), %xmm0
            movq  -72(%rbp), %rdx


            #ptr[i].fail++  = &ptr + offset + i*sizeof
            movq %rdi, %r8  #&ptr
            movslq %ebx, %r9
            imulq $8, %r9
            addq %r8, %r9
            addq $4, %r9    #ptr.fail

            movl (%r9), %r10d
            incl %r10d
            movl %r10d, (%r9)

        afterif:

        incl %ebx
        jmp while
    afterwhile:

    # restaurando verdes
    movq -40(%rbp), %rbx

    movss -4(%rbp), %xmm0

    leave
    ret

#pilha
# sum   ->  -4
# p     ->  -8
# t     ->  -32
# rbx   ->  -40
# rdi   ->  -48
# rsi   ->  -56
# xmm0  ->  -64
# rdx   ->  -72

#struct temperatura      align 8
# scale     -> 0..1     offset 0
# padding   -> 7        offset 1
# value     -> 8..15    offset 8
# repeated  -> 16..19   offset 16
# padding   -> 20..23   offset 20
# total                 24 bytes

#struct data align 4
# sum ->  0 0..3
# fail->  4 4..7
# total   8 bytes