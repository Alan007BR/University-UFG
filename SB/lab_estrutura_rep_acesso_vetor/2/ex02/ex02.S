.data

    .globl letters
    .align 1
letters: .string "abcdefghij"

    .globl even
    .align 4
even: .long 0

    .globl odd
    .align 4
odd: .long 0


.text



.globl ex02

ex02:

    pushq %rbp

    movq  %rsp, %rbp



    # Seu código aqui...
    # unsigned int count -> %eax
    movl $0, %eax



    while:

    #letters[i] = &letters + (count*sizeof)
    movq $letters, %r8
    movl %eax, %r9d #deveria ser movzlq %eax, %r9 mas não existe em c
    imulq $1, %r9
    addq %r8, %r9    #soma

    movb (%r9), %al #al = letters[count]

    # while (letters[count]) ou seja, (letters[count] != 0)
    cmpb $0, %al
    je end_while

    #corpo
        #_if (letters[count++] & 1)
        #tmp = count
        #count++
        #letters[temp]

        movl %eax, %edx
        incl %eax
        movq $letters, %r8
        movl %edx, %r9d #deveria ser movzlq %eax, %r9 mas não existe em c
        imulq $1, %r9
        addq %r8, %r9    #soma 

        movb (%r9), %al #al = letters[count]

        if:
            testb $1, %al
            je else

            #corpo
            #odd++
            incl odd

            jmp endif
        else:
            incl even
        endif:    

    jmp while
    end_while:



    leave

    ret