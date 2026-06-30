.section .rodata
.data
.text
    .globl compare_guid

compare_guid:
pushq %rbp
movq %rsp, %rbp

#id1 %rdi
#_1d2 %rsi

if_1:
    movl (%rdi), %r11d      #part1 offset 0
    movl (%rsi), %r10d
    cmpl %r10d, %r11d
    jg afterif_1
    jmp return_0
afterif_1:

    if_2:
        movw 4(%rdi), %r11w   #part1 offset 4
        movw 4(%rsi), %r10w   #part2 offset 4
        cmpw %r10w, %r11w
        jg afterif_2
        jmp return_0
    afterif_2:

        if_3:
            movw 6(%rdi), %r11w   #part1 offset 6
            movw 6(%rsi), %r10w   #part2 offset 6
            cmpw %r10w, %r11w
            jg afterif_3
            jmp return_0
        afterif_3:

movl $0, %ecx
for:
    cmpl $8, %ecx
    jge afterfor

    if:
        # id1->part4[i]     #&id1.part4 + (i*sizeOf)
        movq %rdi, %r10
        addq $16, %r10      #&id1.part4
        movslq %ecx, %r9    #(long)i
        imulq  $4, %r9      #i*sizeof
        addq %r10, %r9

        movb (%r9), %r9b
        
        #id2->part4[i]
        movq %rsi, %r10
        addq $16, %r10      #&id2.part4
        movslq %ecx, %r9    #(long)i
        imulq  $1, %r9      #i*sizeof
        addq %r10, %r9

        movb (%r10), %r11b

        cmpb %r11b, %r9b
        jg afterif

        jmp return_0

    afterif:

    incl %ecx
    jmp for
afterfor:
jmp return_1

return_0:
movl $0, %eax
jmp exit

return_1:
movl $1, %eax

exit:
leave
ret