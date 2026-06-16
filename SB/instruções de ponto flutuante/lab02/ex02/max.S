.section .rodata
         .align 8
const01: .double 0.0
.data
.text
    .globl max_prod

#di
#produto_s
#id offset 0
#value offset 8
#size: 16
max_prod:
    pushq %rbp
    movq %rsp, %rbp

    #double m = 0.0; --> xmm7
    movsd const01, %xmm7

    movq %rdi, %r8  # r8 = *ptr

    while:
        #ptr->id = &ptr + offset de Id
        cmpl $0, (%r8)
        je  afterwhile

        #double tmp = floor(ptr->values)
        movsd 8(%r8), %xmm0
        call floor
        
        if:
            ucomisd %xmm0, %xmm7
            jae afterif

            #m = tmp
            movsd %xmm0, %xmm7
        afterif:       

        addq $16, %r8 

        jmp while
    afterwhile:

    movsd %xmm7, %xmm0
    leave
    ret

