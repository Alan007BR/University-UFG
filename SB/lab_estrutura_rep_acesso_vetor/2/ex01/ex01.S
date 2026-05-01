.data

    .globl max
    .align 2
max: .word 0

    .globl vet
    .align 2
vet: .word 50, 10, 67, 42

.text

.globl ex01

ex01:

    pushq %rbp

    movq  %rsp, %rbp

    # r9d -> char i
    movb $0, %cl # já fazendo i do for

    for:
    #i<4
    cmpb $4, %cl
    jge afterfor

        # vet[i]>max #vet[i] = &vet + (i*sizeof)
        movq $vet, %r8     #r8w = &vet
        movsbq %cl, %rsi  #rsi = (long)i
        imulq $2, %rsi      #rsi = i*sizeof(long)
        addq %r8, %rsi     # rsi = &vet[i] #aqui pegamos o ponteiro

        movw (%rsi), %ax #ax = vet[i] #aqui pegamos o acesso do elemento
    #corpo
        #_if
        if:
        #(vet[i] > max)
        cmpw max, %ax
        jle afterif

        #corpo
        #max = vet[i]
        movw %ax, max

        afterif:

    #i++
    incb %cl

    jmp for
    afterfor:
    
    leave

    ret