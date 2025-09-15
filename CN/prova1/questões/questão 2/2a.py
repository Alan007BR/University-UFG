import numpy as np

# Definição da função
def f(x):
    return x**4 - 2*x**3 - 13*x**2 + 14*x + 24

def encontra_intervalos(f, a, b, h=0.5, amostragem=20):
    """
    Encontra intervalos de comprimento h que contenham raízes de f(x).
    
    - f: função alvo
    - a, b: limites de busca
    - h: comprimento do intervalo
    - amostragem: nº de subdivisões dentro do intervalo para detectar múltiplas raízes
    """
    intervalos_raizes = []
    intervalos = []
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
        
        print(f"Intervalo atual: [{x0}, {x1}]")
        raiz_flag = "Não"
        if f0 == 0:
            intervalos_raizes.append((x0, x0))
            intervalos.append((x0, x1))
            raiz_flag = "Raiz exata"
        elif f1 == 0:
            intervalos_raizes.append((x1, x1))
            intervalos.append((x0, x1))
            raiz_flag = "Raiz exata"
        elif mudancas == 1:   # uma única raiz
            intervalos_raizes.append((x0, x1))
            intervalos.append((x0, x1))
            raiz_flag = "Sim (única)"
        elif mudancas > 1:   # mais de uma raiz
            raiz_flag = f"{mudancas} raízes"
        
        print(f"[{x0:5.2f}, {x1:5.2f}] | {f0:10.4f} | {f1:10.4f} | {raiz_flag:>8}")
        
    
    return intervalos_raizes, intervalos


# Exemplo de uso
intervalos_raizes, intervalos = encontra_intervalos(f, -10, 10, h=0.5)
print("\nIntervalos com possíveis raízes:", [(float(a), float(b)) for (a,b) in intervalos])
print("\nestimando raízes exatas a partir dos intervalos:", [(float(a), float(b)) for (a,b) in intervalos_raizes])