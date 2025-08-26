# Função que converte número decimal fracionário em binário
decimal_para_binario <- function(r, max_iter = 20) {
  # r = número decimal (0 < r < 1)
  # max_iter = número máximo de iterações para evitar loop infinito
  r_k <- r
  k <- 1
  binario <- c()
  
  while (r_k != 0 && k <= max_iter) {
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
  
  # Retornar resultado como string
  paste0("0.", paste(binario, collapse = ""))
}

# Exemplos:
print(decimal_para_binario(0.9375))
