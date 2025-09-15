import numpy as np
import math
def f(x):
    #f = 500(1+x)^24 - 8000
    return 5000*(1+x)**(24) - 8000

def encontra_intervalos(f, a, b, h=0.5, amostragem=20):
    """
    Encontra intervalos de comprimento h que contenham raízes de f(x).
    
    - f: função alvo
    - a, b: limites de busca
    - h: comprimento do intervalo
    - amostragem: nº de subdivisões dentro do intervalo para detectar múltiplas raízes
    """
    intervalos_raizes = []
    pontos = np.arange(a, b+h, h)

    print(f"{'Intervalo':>15} | {'f(a)':>10} | {'f(b)':>10} | {'Raiz?':>8}")
    print("-"*55)

    for i in range(len(pontos)-1):
        x0, x1 = float(pontos[i]), float(pontos[i+1])
        f0, f1 = f(x0), f(x1)
        
        # subdivisão interna para garantir unicidade
        xs = np.linspace(x0, x1, amostragem)
        fs = [f(float(x)) for x in xs]
        
        # conta quantas vezes o sinal muda dentro do intervalo
        mudancas = np.sum(np.sign(fs[:-1]) * np.sign(fs[1:]) < 0)
        
        raiz_flag = "Não"
        if f0 == 0:
            intervalos_raizes.append((x0, x0))
            raiz_flag = "Raiz exata"
        elif f1 == 0:
            intervalos_raizes.append((x1, x1))
            raiz_flag = "Raiz exata"
        elif mudancas == 1:   # uma única raiz
            intervalos_raizes.append((x0, x1))
            raiz_flag = "Sim (única)"
        elif mudancas > 1:   # mais de uma raiz
            raiz_flag = f"{mudancas} raízes"
        
        print(f"[{x0:5.2f}, {x1:5.2f}] | {f0:10.4f} | {f1:10.4f} | {raiz_flag:>8}")
    
    return intervalos_raizes

intervalos_raizes = encontra_intervalos(f, -1, 2, h=0.1)