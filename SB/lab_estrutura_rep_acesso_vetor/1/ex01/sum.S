.data
    .globl s
    .align 4
s:  .long 0

    .globl nums
    .align 4
nums: .long 65, -105, 111, 34

.text


.globl sum

sum:

    pushq %rbp

    movq  %rsp, %rbp
    #i = ecx
    movl $0, %ecx

    # Seu código aqui...

    #while
    loop:
        #_if (i < 4) -> afterloop
        cmpl $4, %ecx
        jge afterloop


        #nums[i] = &nums + (i * sizeOf)
        movq $nums, %r8   #r8 = &nums
        movslq %ecx, %r9  #r9 = (long)i
        imulq $4, %r9     #r9 = i * tam
        addq %rdx, %r9    #r9 = &nums[i]
        movl %r9, %eax    #eax = nums[i]

        addl %eax, s      #s = s + eax
        

        #i++
        addl $1, %eax

        jmp loop
    afterloop:
        movl %eax, i

    leave

    ret