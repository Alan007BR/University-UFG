def modDiv(num, modx):
    div = num / modx
    return ((num/modx) - int(div))*modx


#ou então resolver usando strings
def modString(num, modx):
    div = num / modx
    div = str(div)
    i = 0
    while i < len(div):
        if div[i] == '.':
            save = i; 
            break
        i+=1
    div = div[:save]
    return ((num/modx)-int(div))*modx


num = int(input('Digite o numero: '))
modx = int(input('digite o divisor: '))


print('o resultado é: {:.2f}'.format(modDiv(num, modx)))
print('o resultado é: {:.2f}'.format(modString(num, modx)))





