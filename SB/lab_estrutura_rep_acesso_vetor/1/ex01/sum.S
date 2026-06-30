.data

    .globl s
    .align 4
s:  .long 0

    .globl nums
    .align 4
nums:   .long 65, -105, 111, 34

.text


.globl sum

sum:

    pushq %rbp

    movq  %rsp, %rbp

    #r8d -> i
    movl $0, %r8d

    while:
    #(i < 4) -> (i>=4)
    cmpl $4, %r8d
    jge afterwhile

    #corpo

    #nums[i] = &nums + (i*sizeof)
    movq $nums, %r9 # r9 = &nums
    movslq %r8d, %r10 #r10 = (long)i
    imulq $4, %r10      #i * sizeof(long)
    addq %r9, %r10     #&vet + i*sizeof

    movl (%r10), %eax #eax = r10 = nums[i]

    addl %eax, s

    #i++
    incl %r8d
    afterwhile:

    leave

    ret