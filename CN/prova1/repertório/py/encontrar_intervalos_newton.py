import numpy as np

def f(x):
    return x**2 + x - 6

def df(x):
    return 2*x + 1
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

# USANDO A FUNÇÃO f E df DEFINIDAS ACIMA
# Integra o encontrador de intervalos para definir automaticamente o chute x0
intervalos = encontra_intervalos(f, -4, 4, h=1)

# Seleciona: (1) raiz exata, se houver; (2) primeiro intervalo com mudança de sinal
intervalo_sel = None
for (a, b) in intervalos:
    if a == b and f(a) == 0:
        intervalo_sel = (a, b)
        break
if intervalo_sel is None:
    for (a, b) in intervalos:
        if a != b and f(a) * f(b) < 0:
            intervalo_sel = (a, b)
            break

if intervalo_sel is None:
    raise RuntimeError("Nenhum intervalo adequado encontrado para iniciar Newton.")

a, b = intervalo_sel

# Escolhe x0
if a == b and f(a) == 0:
    r = a
    # Gera x0 próximo de r para testar precisão; evita dfx≈0
    delta = 1e-3
    max_tries = 6
    tried = 0
    while tried < max_tries:
        x0 = r + delta
        if abs(df(x0)) > 1e-14:
            break
        delta *= 10
        tried += 1
    origem = f"raiz exata em [{a}, {b}]"
else:
    # Pega ponto médio do intervalo com mudança de sinal
    x0 = 0.5 * (a + b)
    # Se derivada muito pequena, desloca levemente para dentro do intervalo
    if abs(df(x0)) <= 1e-14:
        eps = 1e-3
        cand1 = min(max(a + eps, a), b)
        cand2 = min(max(b - eps, a), b)
        x0 = cand1 if abs(df(cand1)) > abs(df(cand2)) else cand2
    origem = f"mudança de sinal em [{a}, {b}] (x0 = ponto médio)"

print(f"Intervalo escolhido: {origem}")
print(f"Chute inicial para Newton: x0 = {x0}")

# Selecione o modo de parada: "ambos" (OR), "func" (apenas |f(x)|), ou "passo" (apenas |Δx|)
modo_parada = "ambos"

raiz, hist, iter_stop, crit_stop = newton_raphson_duplo_criterio(f, df, x0, mode=modo_parada)
print(f"Raiz aproximada: {raiz}")
print(f"Parou na iteração: {iter_stop} pelo critério: {crit_stop}")
print(f"Histórico: {hist}")