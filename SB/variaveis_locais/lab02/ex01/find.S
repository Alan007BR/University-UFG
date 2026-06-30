.section .rodata
fmt: .string "Objeto local [1] igual!\n"
fmt2: .string "Objeto global igual!\n"
.data
    .globl gObj
    .align 4
gObj: .zero 24
.text
    .globl find
#1 param: guid_t *id → %rdi
find:
pushq %rbp
movq %rsp, %rbp
subq $80, %rbp
 
movl $0, -4(%rbp) # found = 0

# salva callee-saved
movq %r12, -72(%rbp)
movq %r13, -80(%rbp)
movq %rdi,  %r12        # r12 = id

#init_obj(&gObj, 0);
movq $gObj, %rdi
movl $0, %esi
call init_obj

#init_obj(&lObj[0], 1);
leaq -52(%rbp), %rdi
movl $1, %esi
call init_obj

#init_obj(&lObj[1], 2);
leaq -28(%rbp), %rdi
movl $2, %esi
call init_obj

# init_pins(pins);
leaq -62(%rbp), %rdi
call init_pins

if_compare_guid_1:
#compare_guid(&lObj[1].id, id)
leaq -28(%rbp), %rdi
addq $4, %rdi        #lobj[1].id
movq %r12, %rsi
call compare_guid

cmpl $0, %eax
je afterif_compare_guid_1

#printf("Objeto local [1] igual!\n");
movq $fmt, %rdi
movl $0, %eax
call printf 

afterif_compare_guid_1:

if_compare_guid_2:
movq %r12, %rdi
movq $gObj, %rsi
addq $4, %rsi
call compare_guid
cmpl $0, %eax
je afterif_compare_guid_2

#printf("Objeto global igual!\n");
movq $fmt2, %rdi
movl $0, %eax
call printf

afterif_compare_guid_2:

movl $0, -64(%rbp)    # i = 0
movl $0, -68(%rbp)    # j = 0

for:
cmpl $2, -64(%rbp)
jge afterfor

    for2:
        cmpl $5, -68(%rbp)
        jge afterfor2

        if_of_for:

            #pins[j]
            leaq -62(%rbp), %r13
            movslq -68(%rbp), %r10
            imulq $2, %r10
            addq %r13, %r10

            movswl (%r10), %r13d  #pins[j]

            #lObj[i].pin
            leaq   -28(%rbp), %r10     # &lObj[0]
            movslq -64(%rbp), %rdx
            imulq  $24, %rdx           # i * sizeof(rfid_object_t)
            addq   %rdx, %r10          # &lObj[i]
            movw   20(%r10), %cx       # lObj[i].pin (offset 20, short)

            cmpw %cx, %r13w
            jne afterif_of_for

            #found = 1
            movl $1, -4(%rbp)

            #goto saida
            jmp saida

        afterif_of_for:

        incl -68(%rbp)
        jmp for2
    afterfor2:

incl -64(%rbp)
jmp for
afterfor:


saida:
movl -4(%rbp), %eax

#recupera os verdes
movq -72(%rbp), %r12
movq -80(%rbp), %r13

leave
ret
    # pilha:
    # -4(%rbp)  found (int)
    # -28(%rbp) lObj[0] (rfid_object_t, 24)
    # -52(%rbp) lObj[1] (rfid_object_t, 24)
    # -62(%rbp) pins[5] (short[5], 10 bytes)
    # -64(%rbp) i (int)
    # -68(%rbp) j (int)