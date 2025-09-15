import numpy as np
import math

def f(x):
    # f = e^(x/2) - 5
    return math.exp(x/2) - 5

def secante_duplo_criterio(f, x0, x1, eps1=1e-6, eps2=1e-6, max_iter=50, mode: str = "ambos"):
    """
    Método da Secante com critérios de parada selecionáveis:
      - mode="func": para quando |f(x_{k+1})| < eps1
      - mode="passo": para quando |x_{k+1} - x_k| < eps2
      - mode="ambos": para quando (|f(x_{k+1})| < eps1) OU (|x_{k+1} - x_k| < eps2)
    Retorna (raiz_aprox, histórico de x, iteração de parada, critério usado)
    """
    historico = [x0, x1]
    for k in range(max_iter):
        fx0, fx1 = f(x0), f(x1) # pega f(x0) e f(x1)
        denom = fx1 - fx0 # calcula o denominador
        if denom == 0: #verificação se o denominador é zero
            raise ZeroDivisionError("Secante falhou: f(x1) - f(x0) = 0.")
        x2 = x1 - fx1 * (x1 - x0) / denom
        historico.append(x2)
        crit1 = abs(f(x2)) < eps1
        crit2 = abs(x2 - x1) < eps2
        print(f"x{k+2} = {x2}")
        if mode == "func":
            if crit1:
                return x2, historico, k+1, 'funcional (|f(x)| < eps1)'
        elif mode == "passo":
            if crit2:
                return x2, historico, k+1, 'intervalar (|x_{k+1} - x_k| < eps2)'
        else:  # mode == "ambos"
            if crit1 or crit2:
                criterio = 'funcional (|f(x)| < eps1)' if crit1 else 'intervalar (|x_{k+1} - x_k| < eps2)'
                return x2, historico, k+1, criterio
        x0, x1 = x1, x2
    return x2, historico, max_iter, 'máximo de iterações'


# Exemplo de uso

modo_parada = "func"  # usando o primeiro critério
eps_passo = 0.00001
raiz, hist, iter_stop, crit_stop = secante_duplo_criterio(f, 6.0, 4.0, mode=modo_parada, eps1=eps_passo, eps2=eps_passo)
print("Evolução das aproximações:")
print(" ".join(f"{x:.6f}" for x in hist))
print(f"Raiz aproximada: {raiz:.6f}")
print(f"Iterações: {iter_stop} (critério: {crit_stop})")