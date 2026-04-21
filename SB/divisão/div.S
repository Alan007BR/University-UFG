# div para unsigned
# idiv para signed

#dividendo
# a cpu exige que se for dividir, dividendo deve ser colocado em dx:ax
# O dividendo deve ser o dobro de bits
# ex: byte -> word
# ex: word -> long
# ex: long -> quad
# ex: quad -> octo
# o divisior, quociente e resto continua sendo do tipo inicial

# eax e edx = 4 bytes
# divivendo = edx:eax (a junção de edx e eax), eax fica com as menores potencias de 2 e edx com as maiores potencias de 2
# divisor = 4 bytes
# quociente = eax
# resto = edx (módulo)
# 

divb, 
divw
divl
divq

#exemplo:
unsigned int x = 128;
unsigned int y = 3;
unsigned int r = 0;
r = x / y; 

#em assembly:
movl x, %eax
movl $0, %edx #compleeta a esquerda com zero
divl y  # 128/3
movl %eax, r

#divq
unsigned long x = 512;
unsigned long y = 5;
unsigned long r = 0;

r = x / y;

# usando rax e rdx
movq x, %rax 
movq $0, %rdx #completa a esquerda com zero
divq y # 512/5
movq %rax, r

# idiv
idivb
idivw
idivl
idivq
# somente pra numeros com sinal
# a grande questão é montar o dividendo, pois o bit mais significativo é o bit de sinal, ou seja, se for negativo, o bit mais significativo é 1 e se for positivo, o bit mais significativo é 0
#ctld: eax -> edx (convert long to double)
#cqtd: rax -> rdx (convert quad to double)

#exemplo:
int x = 64;
int y = 3;
int r = 0;
r = x / y;

#em assembly:
movl x, %eax
cltd # converte o valor de eax para edx, ou seja, se eax for
# positivo, edx fica com 0, se eax for negativo, edx fica com -1 (todos os bits 1)
idivl y # 64/3
movl %eax, r

#exemplo:
int x = -64;
int y = 3;
int r = 0;
r = x / y;

#em assembly:
movl x, %eax
cltd # converte o valor de eax para edx, ou seja, se eax for
# positivo, edx fica com 0, se eax for negativo, edx fica com -1 (todos os bits 1)
idivl y # 64/3
movl %eax, r

#exemplo:
long x = 64;
long y = 3;
long r = 0;
r = x / y;

#em assembly:
movl x, %rax
cqto # converte o valor de rax para rdx
# positivo, rdx fica com 0, se rax for negativo, rdx fica com -1 (todos os bits 1)
idivq y # 64/3
movl %rax, r