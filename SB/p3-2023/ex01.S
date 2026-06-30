.section .rodata
fmt: .string "value = %f, factor = %d\n"
        .align 8
const0: .double 0.0
        .align 8
const1: .double 8 1.0
.data
.text
    .globl process

process:
    pushq %rbp
    movq %rsp, %rbp

    subq $192, %rsp

    #double i 0.0
    movsd const0, %xmm10
    movsd %xmm10, -8(%rbp)

    #salvar
    movq    %rdi,  -176(%rbp)  #factor
    movq    %rsi,  -184(%rbp)  #old
    movsd   %xmm0, -192(%rbp) #limit

    leaq    -168(%rbp), %rdi
    call init

    #restaurar
    movq    -176(%rbp), %rdi
    movq    -184(%rbp), %rsi
    movsd   -192(%rbp), %xmm0

    for:
        movsd   -8(%rbp), %xmm5   # i
        ucomisd %xmm0, %xmm5    # i<limit
        jp  afterfor            # NaN
        jae afterfor            # i < limit --> i >= limit

        #int tmp = (int)i
        cvttsd2si %xmm5, %r11d #tmp = r11d = (int)i

        #old[tmp].sl
        movslq  %r11d, %r10      #(long)tmp
        imulq   $32, %r10         #(long)tmp*sizeOf Test
        addq    %rsi, %r10         #&old + (long)tmp*sizeOf Test

        movq    24(%r10), %r8      #old[tmp].sl

        #new[tmp].sd
        leaq    -168(%rbp), %rcx   #&new
        movslq  %r11d, %r10      #(long)tmp
        imulq   $32, %r10         #(long)tmp * sizeOf test
        addq    %rcx, %r10         #&new + (long)tmp * sizeOf test

        movsd    8(%r10), %xmm9       #new[tmp].sd

        #double value = (old[tmp].sl / new[tmp].sd);
        cvtsi2sdq %r8, %xmm8    #(double)old[tmp].sl
        divsd   %xmm9, %xmm8    #value = sl/sd

        #salvar
        movq    %rdi,  -176(%rbp)  #factor
        movq    %rsi,  -184(%rbp)  #old
        movsd   %xmm0, -192(%rbp) #limit

        movl %edi, %esi     #factor
        movq $fmt, %rdi    #string
        movsd %xmm8, %xmm0  #value
        movl $0, %eax
        call printf

        #restaurar
        movq    -176(%rbp), %rdi
        movq    -184(%rbp), %rsi
        movsd   -192(%rbp), %xmm0

        if:
            testl    $0x40, %r11d
            jz      afterif

            #limit = values - tmp
            cvtsi2sd %r11d, %xmm9   #(double)tmp
            subsd %xmm9, %xmm8
            movsd %xmm8, %xmm0
        afterif:

        #i+1.0
        movsd   -8(%rbp), %xmm10
        addsd   const1, %xmm10
        movsd   %xmm10, -8(%rbp)

        jmp for
    afterfor:

    #(float)limit
    cvtsd2ss %xmm0, %xmm1

    #new[2].sf
    leaq    -168(%rbp), %rcx    #&new
    movq    $2, %r10            #(long)tmp
    imulq   $32, %r10           #(long)tmp * sizeOf test
    addq    %rcx, %r10          #&new + (long)tmp * sizeOf test

    movss    16(%r10), %xmm9     #new[tmp].sf


    cvtsi2ss %edi, %xmm2

    movss %xmm1, %xmm0
    addss %xmm9, %xmm0
    subss %xmm2, %xmm0


    leave
    ret

#pilha
# i     ->  -8
# new   ->  -168
# rdi   ->  -176
# rsi   ->  -184
# xmm0  ->  -192


#Test   align 8
# si    -> 0    0..3
# p     -> 4    4..7
# sd    -> 8    8..15
# sf    -> 16   16..20
# p     -> 20   20..23
# sl    -> 24   24..31
# tam 32