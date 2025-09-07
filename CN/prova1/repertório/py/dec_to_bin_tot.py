def decimal_para_binario_total(x: float, max_frac_bits: int = 20, tol: float = 1e-12) -> str:
    """
    Converte um número decimal não negativo para binário (inteiro + fracionário) como string.
    Logs no estilo do slide:
      - Parte inteira: n = 2*q + r (MSB à esquerda)
      - Parte fracionária: 2*r_{k-1} = d_k + r_k
    """
    if x < 0:
        raise ValueError("Use números não negativos.")

    int_part = int(x)
    frac_part = x - int_part

    print("=== Conversão decimal → binário (total) ===")
    print(f"x = {x:.12f} = {int_part} + {frac_part:.12f}")
    print("")
    # Parte inteira (divisões por 2)
    print("Parte inteira (n = 2*q + r):")
    if int_part == 0:
        int_bits = '0'
        print("n0: 0 (sem passos)")
    else:
        ib = []
        n = int_part
        k = 0
        while n > 0:
            q = n // 2
            r = n % 2
            ib.insert(0, str(r))
            print(f"n{k}: {n} = 2*{q} + {r}")
            n = q
            k += 1
        int_bits = ''.join(ib)
    print(f"Parte inteira em binário (MSB à esquerda): {int_bits}")
    print("")
    # Parte fracionária (multiplicações por 2)
    print("Parte fracionária (2*r_{k-1} = d_k + r_k):")
    if frac_part <= tol or max_frac_bits <= 0:
        print("r0 = 0, sem parte fracionária relevante.")
        return int_bits
    rk = frac_part
    print(f"r0 = {rk:.12f}")
    fb = []
    k = 1
    while rk > tol and k <= max_frac_bits:
        wk = 2 * rk
        dk = int(wk)
        rk_next = wk - dk
        fb.append(str(dk))
        print(f"2 * r{k-1} = {wk:.12f} = d{k} + r{k}")
        print(f"d{k} = {dk}, r{k} = {rk_next:.12f}")
        rk = rk_next
        k += 1
    frac_bits = ''.join(fb) if fb else '0'
    print(f"Parte fracionária em binário: {frac_bits}")
    print("")
    print(f"Resultado: ({int_bits},{frac_bits})_2")
    return int_bits + '.' + frac_bits

# Executando a função
print(decimal_para_binario_total(273.15625))