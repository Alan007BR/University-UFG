from typing import Callable, List, Tuple


def secante(
    f: Callable[[float], float],
    x0: float,
    x1: float,
    precisao: float = 1e-6,
    max_iter: int = 100,
) -> Tuple[float, List[float]]:
    """
    Método da Secante para encontrar raiz de f(x)=0.

    Parâmetros:
    - f: função alvo
    - x0, x1: chutes iniciais (devem ser distintos)
    - precisao: tolerância de parada (por passo e/ou por |f(x)|)
    - max_iter: número máximo de iterações

    Retorna:
    - (raiz_aprox, historico_de_x)
    """
    if x0 == x1:
        raise ValueError("x0 e x1 devem ser distintos.")

    historico: List[float] = [x0, x1]
    print(f"{'k':>3} | {'x_{k-1}':>12} | {'x_k':>12} | {'x_{k+1}':>12} | {'f(x_k)':>12} | {'|Δ|':>10}")

    for k in range(1, max_iter + 1):
        fx0 = f(x0)
        fx1 = f(x1)
        denom = fx1 - fx0
        if denom == 0:
            raise ZeroDivisionError("f(x_k) - f(x_{k-1}) = 0; método da secante falhou.")

        x2 = x1 - fx1 * (x1 - x0) / denom
        erro = abs(x2 - x1)

        print(
            f"{k:3d} | {x0:12.6f} | {x1:12.6f} | {x2:12.6f} | {fx1:12.6e} | {erro:10.3e}"
        )

        historico.append(x2)

        # Critérios de parada: passo pequeno ou valor da função pequeno
        if erro <= precisao or abs(f(x2)) <= precisao:
            return x2, historico

        x0, x1 = x1, x2

    # Se não convergir dentro do limite, retorna melhor aproximação atual
    return x1, historico


if __name__ == "__main__":
    # Exemplo simples: f(x) = x^2 - 2   (raiz ~ 1.414213562...)
    def f_exemplo(x: float) -> float:
        return x * x - 2.0

    raiz, hist = secante(f_exemplo, 1.0, 2.0, precisao=1e-6, max_iter=50)
    print(f"\nRaiz aproximada: {raiz}")
    print(f"Iterações: {len(hist) - 2}")
