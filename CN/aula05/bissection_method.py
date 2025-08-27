
import numpy as np
import matplotlib.pyplot as plt

# Definição da função
def f(x):
    if x < 0:
        return None  # indefinido para x < 0
    return np.sqrt(x) - 5*np.exp(-x)

# def f(x):
#     f = lambda x: x * np.log10(x) - 1
#     return f
def bissecao1Crit1(a, b, precision):
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) e f(b) devem ter sinais opostos.")
    
    print(f"{'a':>6} | {'b':>10} | {'p':>10}")

    historico = []  # lista para armazenar os pontos médios

    while (b - a) / 2 > precision:
        p = (a + b) / 2
        print(f"{a:6.2f} | {b:6.2f} | {p:6.2f}")
        historico.append(p)  # armazenar o ponto médio
        if f(p) == 0: #já é a raiz
            print(f"Raiz exata encontrada: {p}")
            return p
        if f(a) * f(p) < 0:
            b = p
        else:
            a = p
    return (a + b) / 2, historico

def bissecao1Crit2(a, b, precision):
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) e f(b) devem ter sinais opostos.")
    
    print(f"{'a':>6} | {'b':>10} | {'p':>10}")

    historico = []  # lista para armazenar os pontos médios

    # Critério de parada: |f(p)| < precision (2º critério)
    while True:
        p = (a + b) / 2
        print(f"{a:6.2f} | {b:6.2f} | {p:6.2f}")
        historico.append(p)  # armazenar o ponto médio

        # Para se o valor absoluto da função for menor que a precisão
        fp = f(p)
        if fp is None:
            raise ValueError("f(p) é indefinida neste intervalo. Ajuste [a,b].")
        if abs(fp) < precision:
            return p, historico

        if f(a) * fp < 0:
            b = p
        else:
            a = p

def bissecao2Crit1(a, b, precision):

    #se b-a for menor que a precisão, retorna o ponto médio
    if (b - a) < precision:
        return (a + b) / 2
    
    #caso o contrário
    k = 1
    while (b-a) >= precision:
        p = (a + b) / 2 #ponto médio
        if f(a) * f(p) > 0:
            a = p
        else:
            b = p
        k += 1
        if(b-a < precision):
            return (a + b) / 2
        else:
            k += 1
def bissecao2Crit2(a, b, precision):
    # usando Critério de parada: |f(p)| < precision (2º critério)
    
    if f(a) * f(b) >= 0:
        raise ValueError("f(a) e f(b) devem ter sinais opostos.")
    
    k=1
    while k:
        p = (a + b) / 2
        if f(a) * f(p) > 0:
            a = p
        else:
            b = p
        k += 1
        if(abs(f(p)) < precision):
            return (a + b) / 2
        else:
            k += 1

print(bissecao1Crit1(0, 10, 0.001))
print(bissecao1Crit2(0, 10, 0.001))
print(bissecao2Crit1(0, 10, 0.001))
print(bissecao2Crit2(0, 10, 0.001))