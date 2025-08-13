# Solicita ao usuário um número inteiro
n <- as.integer(readline(prompt = "Digite um número inteiro: "))
# Percorre de 1 até n
for (i in 1:n) {
# Verifica se é múltiplo de 3
if (i %% 3 == 0) { # %% pega o resto da divisão
print(i)
}
}
# Fim do código