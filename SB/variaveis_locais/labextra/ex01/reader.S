.section .rodata
fmt1: .string "id1 = %d, id2 = %d, id3 = %d\n"
fmt2: .string "Person ID: %ld\n"
fmt3: .string "Car ID: %ld\n"
fmt4: .string "tipo = %d, ID = %ld, nome = '%s', idade = %d\n"
fmt5: .string "tipo = %d, ID = %ld, nome = '%s', cor = '%s'\n"

.data

.text
    .globl reader
    .globl showPerson
    .globl showCar

reader:
    pushq %rbp
    movq %rsp, %rbp

    #pilha
    # id1, id2, id3     4x4
    # p                 40
    # c[2]              40x2
    # di, si, dx, cx    8x5
    #tot= 168 alinhando a 16 -> 176
    #---------------
    #id1    -4
    #id2    -8
    #id3    -12
    #padding -16
    #p      -56
    #c[1]   -96
    #c[0]   -136
    #di     -144
    #si     -152
    #dx     -160
    #cx     -168
    subq $176, %rsp

    # salvar registradores
    movq %rdi, -144(%rbp)

    leaq -56(%rbp), %rdi        #1 param
    leaq -4(%rbp), %rsi         #2 param
    call readPerson             #readPerson(&p, &id1)

    leaq -136(%rbp), %rdi       #1 param
    leaq   -8(%rbp), %rsi       #2 param
    call readCar                #readPerson(&p, &id2)

    leaq -96(%rbp), %rdi        #1 param
    leaq -12(%rbp), %rsi        #2 param
    call readCar                #readPerson(&p, &id1)

    # restaurar registradores
    movq -144(%rbp), %rdi

    if: #(verbose != 0) --> verbose == 0
        cmpq $0, %rdi
        je  afterif

        #printf("id1 = %d, id2 = %d, id3 = %d\n", id1, id2, id3);
        movq $fmt1, %rdi
        movl -4(%rbp), %esi     #id1
        movl -8(%rbp), %edx     #id2
        movl -12(%rbp), %ecx    #id3
        movl $0, %eax
        call printf

        #printf("Person ID: %ld\n", p.ID);
        movq $fmt2, %rdi
        movq -48(%rbp), %rsi    #fiz -56+8, mas pq o professor usou leaq	-56(%rbp), %r8?
        movl $0, %eax
        call printf

        #printf("Car ID: %ld\n", c[0].ID);
        movq $fmt3, %rdi
        leaq -136(%rbp), %r9
        addq 8(%r9), %rsi
        movl $0, %eax
        call printf

        #printf("Car ID: %ld\n", c[1].ID);
        movq $fmt3, %rdi
        leaq -96(%rbp), %r9
        addq 8(%r9), %rsi
        movl $0, %eax
        call printf

    afterif:

    #showPerson(&p)
    leaq -56(%rbp), %rdi
    call showPerson

    #showCar(&c[0]);
    leaq -136(%rbp), %rdi
    call showCar

    #showCar(&c[1]);
    leaq -96(%rbp), %rdi
    call showCar

    #void
    leave
    ret

showPerson:
    pushq %rbp
    movq %rsp, %rbp

    #printf("tipo = %d, ID = %ld, nome = '%s', idade = %d\n",
    #person->type, person->ID, person->name, person->age);

    movl   (%rdi), %esi #2 param    (person->type)
    movq  8(%rdi), %rdx #3 param    (person->ID)
    leaq 16(%rdi), %rcx #4 param    (person->name)  movq pois é um vetor
    movl 32(%rdi), %r8d #5 param    (person->age)

    movq $fmt4, %rdi    #1 param
    movl $0, %eax
    call printf

    leave
    ret

showCar:
    pushq %rbp
    movq %rsp, %rbp

    #printf("tipo = %d, ID = %ld, nome = '%s', cor = '%s'\n",
    #car->type, car->ID, car->name, car->color);
    movl    (%rdi), %esi    #2 param    (car->type)
    movq   8(%rdi), %rdx    #3 param    (car->id)
    leaq  16(%rdi), %rcx    #4 param    (car->name)
    leaq  32(%rdi), %r8    #5 param    (car->color)

    movq $fmt5, %rdi    #1 param
    movl $0, %eax
    call printf

    leave
    ret