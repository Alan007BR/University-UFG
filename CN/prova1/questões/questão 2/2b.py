import numpy as np

def f(x):
    return x**4 - 2*x**3 - 13*x**2 + 14*x + 24

def df(x):
    return (4*(x**3)) - (6*x**2) - (26*x) + 14
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

def newton_raphson_duplo_criterio(f, df, x0, eps1=1e-6, eps2=1e-6, max_iter=50, mode: str = "ambos"):
    """
    Método de Newton-Raphson com critérios de parada selecionáveis:
      - mode="func": para quando |f(x_{k+1})| < eps1
      - mode="passo": para quando |x_{k+1} - x_k| < eps2
      - mode="ambos": para quando (|f(x_{k+1})| < eps1) OU (|x_{k+1} - x_k| < eps2)

    Retorna (raiz_aprox, histórico de x, iteração de parada, critério usado)
    """
    x = x0
    historico = [x0]
    for k in range(max_iter):
        fx = f(x)
        dfx = df(x)
        if dfx == 0:
            raise ZeroDivisionError("Derivada zero. Método falhou.")
        x_new = x - fx/dfx
        historico.append(x_new)
        crit1 = abs(f(x_new)) < eps1
        crit2 = abs(x_new - x) < eps2
        if mode == "func":
            if crit1:
                return x_new, historico, k+1, 'funcional (|f(x)| < eps1)'
        elif mode == "passo":
            if crit2:
                return x_new, historico, k+1, 'intervalar (|x_{k+1} - x_k| < eps2)'
        else:  # mode == "ambos" (OR)
            if crit1 or crit2:
                criterio = 'funcional (|f(x)| < eps1)' if crit1 else 'intervalar (|x_{k+1} - x_k| < eps2)'
                return x_new, historico, k+1, criterio
        x = x_new
    return x, historico, max_iter, 'máximo de iterações'

modo_parada = "ambos"  # queremos usar ambos os critérios

raiz, hist, iter_stop, crit_stop = newton_raphson_duplo_criterio(f, df, -5, eps1=1e-5, eps2=1e-2, mode=modo_parada)
print("Evolução das aproximações = ", " ".join(f"{x:.6f}" for x in hist))
print(f"Raiz aproximada: {raiz:.6f}")
print(f"Parou na iteração: {iter_stop} usando {modo_parada} os critérios, parou pelo critério: {crit_stop}")