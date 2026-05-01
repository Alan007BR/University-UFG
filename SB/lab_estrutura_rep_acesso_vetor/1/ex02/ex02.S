.data
    .globl last
    .align 8
last: .quad 0

    .globl values
    .align 8
values:   .quad 50, -10, 60, -20, 70

.text


.globl sum

sum:

    pushq %rbp

    movq  %rsp, %rbp
    
    #j = 4
    movq $4, %edx

    #i = 0
    movq $0, %ecx
    # Seu código aqui...
    for:
        # _if(i<j)
        cmpl %edx, %ecx
        jge afterfor

        #corpo

        #long tmp -> %r8

        #long tmp = values[i]
        #values[i] = &values + (i*sizeof)
        movq $values, %rdi # rdi = &values
        movslq %ecx, %rsi  # rsi = (long)i
        imulq $8, %rsi     # rsi = i * sizeof(long)
        addq %rdi, %rsi    # rsi = &nums[i]
        
        movq (%rsi), %r8   # r8 = tmp = nums[i]

        # values[i] = values[j]

        movq $values, %r9  #r9 = &values
        movslq %edx, %r10  #r10 = (long)j
        imulq $8, %r10     #r10 = j*sizeof(long)
        addq %r9, %r10

        movq (%r10), %r11  # r11 = values[j]

        movq $values, %rdi # rdi = &values
        movslq %ecx, %rsi  # rsi = (long)i
        imulq $8, %rsi     # rsi = i * sizeof(long)
        addq %rdi, %rsi    # rsi = &values[i]

        movq %r11, (%rsi)  # values[i] = r11

        #values[j] = tmp
        movq $values, %r9  #r9 = &values
        movslq %edx, %r10  #r10 = (long)j
        imulq $8, %r10     #r10 = j*sizeof(long)
        addq %r9, %r10

        movq %r8, (%r10)

        #i++
        addq $1, %ecx
        #j--
        decq $1, %edx

        jmp for
    afterfor:

    #last = values [4]
    movq last, %r9
    movq $values, %r10
    movq 32(%r10), %r9
    movq %r9, last

    leave
    ret