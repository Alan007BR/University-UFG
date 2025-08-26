decimal_to_binary_int <- function(n) {
  if (n == 0) return("0")
  restos <- c()
  while (n > 0) {
    restos <- c(n %% 2, restos)
    n <- n %/% 2
  }
  paste(restos, collapse = "")
}

decimal_to_binary_fraction <- function(x, precision = 10) {
    bin <- c()
    for (k in 1:precision) {
        frac <- x * 2
        inteiro <- floor(frac)
        if(frac >=1) {
            bin <- c(bin, 1)
        } else {
            bin <- c(bin, 0)
        }
        bin <- c(bin, inteiro)
        x <- frac - inteiro
        if (frac == 0) break
    }
    paste(bin, collapse = "")
}


main <- function(num, precisao = 4) {
  inteiro <- floor(num)
  fracao <- num - inteiro

  bin_inteiro <- decimal_to_binary_int(inteiro)
  print(paste("Parte inteira:", bin_inteiro))
  if (fracao > 0) {
    bin_fracao <- decimal_to_binary_fraction(fracao, precisao)
    print(paste("Parte fracionária:", bin_fracao))
    return(paste0(bin_inteiro, ".", bin_fracao))
  } else {
    return(bin_inteiro)
  }
}

print(main(0.2578125))