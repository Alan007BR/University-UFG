import numpy as np

def f(x):
    return x**2 + x - 6
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

def secante_duplo_criterio(f, x0, x1, eps1=1e-6, eps2=1e-6, max_iter=50):
    """
    Método da Secante com dois critérios de parada:
      - |f(x_{k+1})| < eps1
      - |x_{k+1} - x_k| < eps2
    Retorna (raiz_aprox, histórico de x, iteração de parada, critério usado)
    """
    historico = [x0, x1]
    for k in range(max_iter):
        fx0, fx1 = f(x0), f(x1)
        denom = fx1 - fx0
        if denom == 0:
            raise ZeroDivisionError("Secante falhou: f(x1) - f(x0) = 0.")
        x2 = x1 - fx1 * (x1 - x0) / denom
        historico.append(x2)
        crit1 = abs(f(x2)) < eps1
        crit2 = abs(x2 - x1) < eps2
        print(f"x{k+2} = {x2}")
        if crit1:
            return x2, historico, k+1, 'funcional (|f(x)| < eps1)'
        if crit2:
            return x2, historico, k+1, 'intervalar (|x_{k+1} - x_k| < eps2)'
        x0, x1 = x1, x2
    return x2, historico, max_iter, 'máximo de iterações'


# Exemplo de uso

# Procurando intervalos com raízes para f(x)
# Exemplo: f(x) = x^2 + x - 6, chutes x0=1.5, x1=1.7 (slides professor)
intervalos = encontra_intervalos(f, -4, 4, h=1)

# Seleciona primeiro um intervalo com raiz exata, se existir; caso contrário, o primeiro com mudança de sinal
intervalo_valido = None
# 1) Prioridade: raiz exata (o algoritmo marca como (r, r))
for (a, b) in intervalos:
    if a == b and f(a) == 0:
        intervalo_valido = (a, b)
        break
# 2) Fallback: primeira mudança de sinal
if intervalo_valido is None:
    for (a, b) in intervalos:
        if a != b and f(a) * f(b) < 0:
            intervalo_valido = (a, b)
            break

if intervalo_valido is not None:
    a, b = intervalo_valido
    # Se for raiz exata, reporta diretamente; secante exige dois pontos distintos
    if a == b and f(a) == 0:
        print(f"Intervalo: [{a}, {b}] (raiz exata)")
        print(f"Raiz exata encontrada: x = {a}")
        print("Histórico: [x]")
        print("Critério: raiz exata detectada no varrimento")
    else:
        raiz, hist, iter_stop, crit_stop = secante_duplo_criterio(f, a, b)
        print(f"Intervalo: [{a}, {b}]")
        print(f"Raiz aproximada: {raiz}")
        print(f"Histórico: {hist}")
        print(f"Parou na iteração: {iter_stop} pelo critério: {crit_stop}")
else:
    print("Nenhum intervalo válido encontrado.")