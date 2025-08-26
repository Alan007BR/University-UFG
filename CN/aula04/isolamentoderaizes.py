import numpy as np

# Função
def f(x):
    if x < 0:
        return None  # indefinido
    return np.sqrt(x) - 5*np.exp(-x)

pontos = np.linspace(0, 10, 100)  # 21 pontos de 0 a 10

print(f"{'x':>6} | {'f(x)':>10} | {'Sinal':>12}")
print("-"*32)

# Preenchendo a tabela
for x in pontos:
    y = f(x)
    if y is None:
        sinal = "Indefinido"
        y_str = "-"
    elif y > 0:
        sinal = "Positivo"
        y_str = f"{y:.4f}"
    elif y < 0:
        sinal = "Negativo"
        y_str = f"{y:.4f}"
    else:
        sinal = "Zero"
        y_str = "0.0000"
    print(f"{x:6.2f} | {y_str:>10} | {sinal:>12}")
