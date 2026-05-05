        .section .rodata



        .data
            .globl v1
            .align 2
        v1: .word 32, 34, 27, 4

            .globl v2
            .align 4
        v2: .long 12, 22, 31, 23, 6

            .globl v3
            .align 1
        v3: .byte 0, 0, 0, 0

            .globl v4
            .align 8
        v4: .quad 0, 0, 0, 0, 0, 0, 0, 0

            .globl i
            .align 4
        i:  .long 0

            .globl j
            .align 2
        j:  .short 0

        .text

        .globl aux

aux:

        pushq %rbp

        movq  %rsp, %rbp



        # Seu código aqui...

        movl i, %eax
        for:
        #condição (i<4) -> (i>=4)
        cmpl $4, %eax
        jge afterfor

        #corpo
        movw j, %cx
        movw $0, %cx

            #while
            while:
            #condição (j< 5) -> (j>=5)
            cmpw $5, %cx
            jge afterwhile

            #corpo
                if:
                    #condição (i == j) -> (i !== j)
                    movswl %cx, %ecx
                    cmpl %ecx, %eax
                    jne else

                    #corpo (vetores)
                    #v1[i]
                    movq $v1, %r8       # r8 = &v1
                    movslq %eax, %r9    # (long)i
                    imulq $2, %r9       # i*sizeOf
                    addq %r8, %r9       # &v1 + (i*sizeOf)
                    movswl (%r9), %edi  # edi = v1[i] #era pra ser movw, mas dps precisamos alargar pra long, simplificando

                    #v2[j]
                    movq $v2, %r10
                    movslq %ecx, %r11
                    imulq $4, %r11
                    addq %r10, %r11
                    movl (%r11), %r10d   #r10 já cumpriu sua função anterior então podemos reutilizar

                    #v1[i] + v2[j] (ambos estão como long)
                    addl %r10d, %edi

                    #v3[i] = v1[i] + v2[j]; -> v3[i] = %rdi
                    movq $v3, %r8
                    movslq %eax, %r11
                    imulq $1, %r11
                    addq %r8, %r11   #r11 = &v3[i]

                    movb %dil, (%r11)

                    jmp afterif
                else:

                    movswl %cx, %ecx
                    #corpo
                    #vetores
                    #v1[i]
                    movq $v1, %r8       # r8 = &v1
                    movslq %eax, %r9    # (long)i
                    imulq $2, %r9       # i*sizeOf
                    addq %r8, %r9       # &v1 + (i*sizeOf)
                    movswl (%r9), %edi  # edi = v1[i] #era pra ser movw, mas dps precisamos alargar pra long, simplificando

                    #v2[j]
                    movq $v2, %r10
                    movslq %ecx, %r11
                    imulq $4, %r11
                    addq %r10, %r11
                    movl (%r11), %r10d   #r10 já cumpriu sua função anterior então podemos reutilizar

                    #v1[i] + v2[j]
                    addl %r10d, %edi

                    #v4[i+j]
                    #i + j
                    movl %ecx, %edx
                    addl %eax, %edx     # edx = i + j

                    movq $v4, %r8
                    movslq %edx, %r11
                    imulq $8, %r11
                    addq %r8, %r11      # r11 = &v4[i+j]

                    movslq %edi, %rdi
                    addq %rdi, (%r11)   # (%r11) -> conteúdo do addr apontado por %r11
                    

                afterif:

            #j++
            incw %cx
            movw %cx, j
            jmp while
            afterwhile:

        #i++
        incl %eax
        movl %eax, i
        jmp for
        afterfor:
        # um grande nada


        leave

        ret