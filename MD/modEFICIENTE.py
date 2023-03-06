import math

def modDiv(num, modx):
    div = num / modx
    return ((num/modx) - int(div))*modx

def modFast(base, num, m):
    #base^num mod m    
    M = base
    num = format(num, 'b')#transformando em binario
    
    #invertendo o numero bin para ficar na ordem certa
    num = str(num)
    rev = list(reversed(num))
    
    result = []
    i = 0
    for i in range(len(rev)):#conseguir potencias para gerar o numero
        if(rev[i] == '1'):
            result.append(math.pow(2, i))
    print('potências: ', result)
    
    
    
    #calculando as potencias de base^result[i] mod m
    i = 2
    #for i in range(result[len(result)-1]):
    res = 1
    aux = modDiv(math.pow(base, 1), m)
    if 1 in result:
        res *= aux
        
    while i <= result[len(result)-1]:
        log = math.log(i) / math.log(2)
        if(int(log) == log):#verifica se o numero é potencia de dois
            aux = round(modDiv(math.pow(aux, 2), m))#faz o calculo do M intercaldo pelas potencias de 2
            if i in result:
                res *= aux#se a potencia de 2 for parte do resultado, o valor entra e multiplica
            i+=1
        else: 
            i+=1
            continue
    return round(modDiv(res, m))#mod do valor multiplicado, final

base = int(input())
num = int(input())
m = int(input())

print(modFast(base, num, m))