# conversão decimal para binário
#usando esse algo N0 = 347 = 2*173 +1 -> a0=1 N1 = 173 = 2*86 + 1-> a1 = 1 assim endiante....
decimal_to_binary <- function(x) {
    k <- 0
    resto <- c()
    cat("Conversão de decimal para binário:\n")
    cat("n: ", x, "\n")
    while (x > 0) {
        resto <- c(x %% 2, resto)
        x <- x %/% 2
        next_x <- x %/% 2

        cat(paste0("n", k, ": ", x, " = ", "2*", next_x, " + ", resto[1], "\n"))
        k <- k + 1
    }
    return(resto)
}

result <- decimal_to_binary(2021)
print(result)