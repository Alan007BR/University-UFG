.section .rodata
fmt: .string "sum = %ld\n"
.data
.text
    .globl main
    .globl sum


#pilha
#nodes[1] -> 56
#nodes[2] -> 112
main:
    pushq %rbp
    movq %rsp, %rbp

    subq $112, %rsp

    leaq -112(%rbp), %rdi   #rdi = &nodes
    call init

    #sum(nodes, 2)
    leaq -112(%rbp), %rdi   #rdi = &nodes
    movl $2, %esi
    call sum

    movq $fmt, %rdi
    movq %rax, %rsi
    movl $0, %eax
    call printf

    movl $0, %eax

    leave
    ret

#rdi, esi
sum:
    pushq %rbp
    movq %rsp, %rbp

    subq $32, %rsp

    #salvando
    movq %r12,  -8(%rbp)    #rdi
    movq %r13, -16(%rbp)    #rsi
    movq %r14, -24(%rbp)    #i
    movq %r15, -32(%rbp)    #j

    movq %rdi, %r12   #r12 = *nodes
    movl %esi, %r13d  #r13 = size

    #r10 = h

    call new_sum
    movq %rax, %r10

    #i
    movl $0, %r14d
    for:
        cmpl %r13d, %r14d   #size, i
        jge afterfor        #i < size --> i >= size

        #j
        movl $0, %r15d
        for2:
            #nodes[i].used = (&nodes + (i*sizeof)) + offset.used 
            movq %r12, %r8         # r8 = &nodes
            movslq %r14d, %r9      # r9 = i
            imulq $56, %r9         #r9 = i*sizeOf nodes
            addq %r8, %r9

            movl 48(%r9), %r8d     #r8d = nodes[i].used used tem offset 48

            cmpl %r8d, %r15d    #nodes[i].used, j
            jge afterfor2       #j<nodes[i].used ---> j >= nodes[i].used


            movq %r10, %rdi       #1param
            #nodes[i].values[j] = (&nodes + (i*sizeof nodes)) + &values + (j*sizeOf values))
            #nodes[i].used = (&nodes + (i*sizeof)) 
            movq %r12, %r8         # r8 = &nodes
            movslq %r14d, %r9      # r9 = i
            imulq $56, %r9         # r9 = i*sizeOf nodes
            addq %r8, %r9          # r8 = &nodes[i]

            leaq 8(%r9), %r11      #&nodes[i].values
            movslq %r15d, %r8
            imulq $8, %r8
            addq %r11, %r8         #&nodes[i].values[j]

            movq (%r8), %rsi       #r11 = nodes[i].values[j] #2 param
            call add_sum

            incl %r15d
            jmp for2
        afterfor2:

        incl %r14d
        jmp for
    afterfor:

    movq %r10, %rdi
    call get_sum        # return get_sum(h)

    #restaurando
    movq  -8(%rbp), %r12
    movq -16(%rbp), %r13
    movq -24(%rbp), %r14    #i
    movq -32(%rbp), %r15    #j
    

    leave
    ret