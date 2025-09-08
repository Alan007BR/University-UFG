import numpy as np
import matplotlib.pyplot as plt

# Definição da função
def f(x):
    return 2*(x**3) - 10*(x**2) + 4*x + 12

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

def bissecao_flex(f, a, b, tol=10e-3, max_iter=100, mode="func"):
    """
    Bissecção com modos de parada:
      - mode="func": para quando |f(p)| < tol
      - mode="intervalo": para quando (b - a)/2 < tol
      - mode="ambos": para quando |f(p)| < tol OU (b - a)/2 < tol
    Retorna (p, historico, a_hist, b_hist)
    """
    if a > b:
        a, b = b, a
    fa, fb = f(a), f(b)
    if fa == 0:
        return a, [a], [a], [a]
    if fb == 0:
        return b, [b], [b], [b]
    if fa * fb > 0:
        raise ValueError("Intervalo não possui mudança de sinal (f(a)*f(b) > 0).")

    historico = []
    a_hist = []
    b_hist = []
    p = None
    for _ in range(max_iter):
        # registra intervalo atual antes do ponto médio
        a_hist.append(a)
        b_hist.append(b)
        p = 0.5 * (a + b)
        fp = f(p)
        historico.append(p)

        stop_func = abs(fp) < tol
        stop_intervalo = 0.5 * (b - a) < tol

        if mode == "func" and stop_func:
            return p, historico, a_hist, b_hist
        if mode == "intervalo" and stop_intervalo:
            return p, historico, a_hist, b_hist
        if mode == "ambos" and (stop_func or stop_intervalo):
            return p, historico, a_hist, b_hist

        if fa * fp < 0:
            b, fb = p, fp
        else:
            a, fa = p, fp
    return p, historico, a_hist, b_hist

# USANDO AS FUNÇÕES ACIMA

# Procurando intervalos com raízes para f(x)
intervalos = encontra_intervalos(f, 4, 4.5, h=1)

# pega o primeiro intervalo válido
intervalo_valido = None
for (a, b) in intervalos:
    if a != b and f(a) * f(b) < 0:
        intervalo_valido = (a, b)
        break

if intervalo_valido:
    a, b = intervalo_valido
    p1, hist1, a_hist1, b_hist1 = bissecao_flex(f, a, b, tol=10e-3, mode='func')
    p2, hist2, a_hist2, b_hist2 = bissecao_flex(f, a, b, tol=10e-3, mode='intervalo')
    p3, hist3, a_hist3, b_hist3 = bissecao_flex(f, a, b, tol=10e-3, mode='ambos')
    print(f"Intervalo: [{a}, {b}]")
    print(f"(critério 1) func     -> x ≈ {p1:.8f}, f(x) ≈ {f(p1): .2e}")
    print("Evolução (func):")
    for k, (ak, bk, pk) in enumerate(zip(a_hist1, b_hist1, hist1), start=1):
        print(f"  k={k:2d}: a={ak:.8f}, b={bk:.8f}, p={pk:.8f}, f(p)={f(pk): .2e}")

    print(f"\n(critério 2) intervalo-> x ≈ {p2:.8f}, f(x) ≈ {f(p2): .2e}")
    print("Evolução (intervalo):")
    for k, (ak, bk, pk) in enumerate(zip(a_hist2, b_hist2, hist2), start=1):
        print(f"  k={k:2d}: a={ak:.8f}, b={bk:.8f}, p={pk:.8f}, f(p)={f(pk): .2e}")

    print(f"\n(critério 3) ambos    -> x ≈ {p3:.8f}, f(x) ≈ {f(p3): .2e}")
    print("Evolução (ambos):")
    for k, (ak, bk, pk) in enumerate(zip(a_hist3, b_hist3, hist3), start=1):
        print(f"  k={k:2d}: a={ak:.8f}, b={bk:.8f}, p={pk:.8f}, f(p)={f(pk): .2e}")
else:
    print("Nenhum intervalo válido encontrado.")