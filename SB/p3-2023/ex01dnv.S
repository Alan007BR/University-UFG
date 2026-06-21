.section .rodata
         .align 8
.const0: .double 0.0
         .align 8
.const1: .double 1.0

.fmt: .string "value = %f, factor = %d\n"
.data
.text
    .globl process

# chega: %xmm0 (limit)
#        %edi  (factor)
#        %rsi  (*old)
process:
    pushq %rbp
    movq %rsp, %rbp

    subq $208, %rbp

    #i = 0.0
    movsd const0, %xmm10
    addsd %xmm10, -168(%rbp)

    #salvando caller
    movsd   %xmm0, -176(%rbp)
    movq    %rdi, -184(%rbp)
    movq    %rsi, -192(%rbp)

    #init(new)
    leaq -160(%rbp), %rdi
    call init

    movsd   -176(%rbp), %xmm0
    movq    -184(%rbp), %rdi
    movq    -192(%rbp), %rsi

    for:
        movsd -168(%rbp), %xmm9   #xmm9 = i
        ucomisd %xmm0, %xmm9
        jp  afterfor
        jae afterfor

        #---------------------corpo

        cvttsd2si %xmm9, %r8d   #r8d = tmp = (int)i
        #old[tmp].sl = &old + ((long)tmp*sizeof) + offset de sl
        movslq %r8d, %r9
        imulq $32, %r9
        addq %rsi, %r9

        movq 24(%r9), %r10  #r10 = old[tmp].sl
        cvtsi2sdq %r10, %xmm2   #xmm2 = (double)old[tmp].sl

        #new[tmp].sd
        leaq -160(%rbp), %rcx
        movslq %r8d, %rdx
        imulq $32, %rdx
        addq %rcx, %rdx

        movsd 8(%rdx), %xmm1 #xmm1 = new[tmp].sd

        divsd %xmm1, %xmm2  #value = xmm2 = old[tmp].sl / new[tmp].sd
        

        #salvando caller
        movsd   %xmm0, -176(%rbp)
        movq    %rdi, -184(%rbp)
        movq    %rsi, -192(%rbp)
        movq    %xmm2, -200(%rbp)

        movq %edi, %esi
        movq $fmt, %rdi
        movq %xmm2, %xmm0
        movl $1, %eax
        call printf

        movsd   -176(%rbp), %xmm0
        movq    -184(%rbp), %rdi
        movq    -192(%rbp), %rsi
        movq    -200(%rbp), %xmm2

        if:
            movq -168(%rbp), %xmm9
            cvttsd2si %xmm9, %r8d   #refazer tmp pois pode ser sido substituido apos chamada
            testl $0x40, %r8d
            jz  afterif
            #-----------------
            #value - tmp
            cvtsi2sd %r8d, %xmm11   #destruncando (em c isso funcionaria assim, essa volta.)
            subsd   %xmm11, %xmm2
            cvttsd2si   %xmm2, %xmm0    #xmm0 = (float)limit

        afterif:

        #---------------------
        #i = i + 1.0
        movsd const1, %xmm10
        addsd %xmm10, -168(%rbp)
    afterfor:

        #new[tmp].sf
        leaq -160(%rbp), %rcx
        movq $2, %rdx
        imulq $32, %rdx
        addq %rcx, %rdx

        movss 16(%rdx), %xmm7 #xmm7 = new[2].sf
        addss %xmm7, %xmm0
        
        cvtsi2ss %esi, %xmm8
        subss %xmm8, %xmm0  #return

    leave
    ret

#pilha
# new   -> -160
# i     -> -168
# xmm0  -> -176
# rdi   -> -184
# rsi   -> -192
# xmm2  -> -200

#test
# si    ->  0
# sd    ->  8
# sf    ->  16
# p     ->  17  17..23
# sl    ->  24
# tam 32