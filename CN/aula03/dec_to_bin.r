# Função que converte número decimal fracionário em binário (apenas parte fracionária)
decimal_para_binario <- function(r, max_iter = 20, tol = 1e-12) {
  # r = número decimal fracionário (0 <= r < 1)
  # max_iter = número máximo de iterações para evitar loop infinito
  if (r < 0 || r >= 1) {
    stop("'r' deve estar no intervalo [0, 1). Para valores gerais use 'decimal_para_binario_total()'.")
  }

  r_k <- r
  k <- 1
  binario <- c()

  while (r_k > tol && k <= max_iter) {
    # Passo 1: multiplicar por 2 (binário 10 = decimal 2)
    w_k <- 2 * r_k

    # Parte inteira (0 ou 1)
    z_k <- floor(w_k)

    # Guardar o bit
    binario <- c(binario, z_k)

    # Atualizar resto
    r_k <- w_k - z_k

    k <- k + 1
  }

  # Retornar resultado como string (apenas fração)
  frac_str <- if (length(binario) == 0) "0" else paste(binario, collapse = "")
  paste0("0.", frac_str)
}

# Conversor geral: parte inteira + parte fracionária
decimal_para_binario_total <- function(x, max_frac_bits = 20, tol = 1e-12) {
  if (x < 0) stop("Use números não negativos.")
  int_part <- floor(x)
  frac_part <- x - int_part

  # Parte inteira (divisões sucessivas por 2)
  if (int_part == 0) {
    int_bits <- "0"
  } else {
    ib <- c()
    n <- int_part
    while (n > 0) {
      ib <- c(n %% 2, ib)
      n <- n %/% 2
    }
    int_bits <- paste(ib, collapse = "")
  }

  # Parte fracionária (multiplicações por 2)
  if (frac_part < tol || max_frac_bits <= 0) {
    return(int_bits)
  } else {
    r_k <- frac_part
    fb <- c()
    k <- 1
    while (r_k > tol && k <= max_frac_bits) {
      w_k <- 2 * r_k
      z_k <- floor(w_k)
      fb <- c(fb, z_k)
      r_k <- w_k - z_k
      k <- k + 1
    }
    frac_bits <- if (length(fb) == 0) "0" else paste(fb, collapse = "")
    return(paste0(int_bits, ".", frac_bits))
  }
}

# Exemplos:
# Parte fracionária apenas
# print(decimal_para_binario(0.328125))

# Número geral (inteira + fracionária)
print(decimal_para_binario_total(0.328125))
