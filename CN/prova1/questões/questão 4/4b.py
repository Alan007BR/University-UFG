import numpy as np
import matplotlib.pyplot as plt

# Definição da função
def f(x):
    return 5000*(1+x)**(24) - 8000

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


a = 0.0
b = 0.10
tol = 1e-5
modo_parada = "func"  # usando o criterio |x-e|< tol
p1, hist1, a_hist1, b_hist1 = bissecao_flex(f, a, b, tol=tol, mode=modo_parada)
print(f"Intervalo: [{a}, {b}]")
print(f"(critério 1) func     -> uma aproximação para raíz é: x ≈ {p1:.8f}, f(x) ≈ {f(p1): .2e}")
print("Evolução (func):")
for k, (ak, bk, pk) in enumerate(zip(a_hist1, b_hist1, hist1), start=1):
    print(f"  k={k:2d}: a={ak:.8f}, b={bk:.8f}, p={pk:.8f}, f(p)={f(pk): .2e}")