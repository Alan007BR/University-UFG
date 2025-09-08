def bin_int_or_frac_to_decimal(number_bin: str) -> float:
    """
    Converte base 2 (com parte inteira e/ou fracionária) para base 10 e
    imprime a forma polinomial no estilo do slide:
      (0, d1 d2 ... dj ...)_2 = d1*2^-1 + d2*2^-2 + ... + dj*2^-j + ...
    Exemplos aceitos: '100010001,100001', '0,01011', '101.101'.
    """
    # Normaliza vírgula para ponto
    s = number_bin.strip().replace(',', '.')
    print("=== Conversão (forma polinomial) binário → decimal ===")
    print(f"Entrada: {number_bin} → normalizado: {s}")
    # Separa parte inteira e fracionária
    if '.' in s:
        int_part, frac_part = s.split('.', 1)
    else:
        int_part, frac_part = s, ''
    int_part = int_part or '0'
    # Validação dos dígitos
    if not all(ch in '01' for ch in int_part):
        raise ValueError('Apenas dígitos 0/1 são permitidos na parte inteira.')
    if not all(ch in '01' for ch in frac_part):
        raise ValueError('Apenas dígitos 0/1 são permitidos na parte fração.')
    print(f"Partes: inteira = '{int_part}', fração = '{frac_part}'")
    print("")
    # Parte inteira: notação posicional Σ b_k * 2^k
    int_val = int(int_part, 2) if int_part else 0
    if int_part == '':
        int_bits = '0'
    else:
        int_bits = int_part
    int_len = len(int_bits)
    termos_int = [f"{b}*2^{int_len-1-i}" for i, b in enumerate(int_bits)]
    print(f"Parte inteira: ({int_bits})_2 = " + " + ".join(termos_int))
    print(f"Valor da parte inteira: {int_val}")
    print("")
    # Parte fração: (0, d1 d2 ...)_2 = Σ d_i * 2^-i
    frac_val = 0.0
    if frac_part:
        termos_frac = [f"{ch}*2^-{i}" for i, ch in enumerate(frac_part, start=1)]
        print(f"Parte fração: (0,{frac_part})_2 = " + " + ".join(termos_frac))
        for i, ch in enumerate(frac_part, start=1):
            contrib = int(ch) * (2 ** -i)
            frac_val += contrib
            print(f"  d{i}={ch} → {ch}*2^-{i} = {contrib:.12f}")
        print(f"Valor da parte fração: {frac_val:.12f}")
    else:
        print("Parte fração: (0,)_2 = 0")
        print("Valor da parte fração: 0")
    print("")
    total = int_val + frac_val
    print(f"Resultado: ({int_bits},{frac_part})_2 = {int_val} + {frac_val:.12f} = {total:.12f}")
    return total

# Executando a função
print(bin_int_or_frac_to_decimal('100010001,100001'))
# print(bin_int_or_frac_to_decimal('0,01011'))
# print(bin_int_or_frac_to_decimal('101.101'))