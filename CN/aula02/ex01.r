# conversão binário -> decimal (soma a esquerda)

# Converte um vetor de bits (0/1) em inteiro decimal.
bin_to_dec <- function(bits, msb_left = TRUE) {
    # Validações simples
    if (length(bits) == 0) return(0L)
    if (!all(bits %in% c(0, 1))) stop("'bits' deve conter apenas 0 ou 1")

    # Se os bits vierem com LSB à esquerda, invertê-los opcionalmente
    if (!msb_left) bits <- rev(bits)

    # Acumulador: percorre da esquerda para a direita (MSB -> LSB)
    acc <- 0L
    for (b in bits) {
        acc <- 2L * acc + as.integer(b)
    }
    acc
}

# Cria uma string bonitinha com a expansão, e.g., 1*2^7 + 1*2^5 + ...
bin_expansion_string <- function(bits) {
    n <- length(bits)
    if (n == 0) return("0")
    exps <- (n - 1):0
    terms <- sprintf("%d*2^%d", bits, exps)
    # Opcional: mostrar só os termos com bit=1 para ficar mais limpo
    terms <- terms[bits == 1]
    if (length(terms) == 0) return("0")
    paste(terms, collapse = " + ")
}

# Exemplo de uso
bits <- c(1, 0, 1, 1, 1, 0, 0, 1)  # 10111001 (MSB à esquerda)
cat("Bits:           ", paste(bits, collapse = ""), "\n", sep = "")
cat("Expansão:       ", bin_expansion_string(bits), "\n", sep = "")
valor <- bin_to_dec(bits)
cat("Decimal (base10): ", valor, "\n", sep = "")