# Sorteia número entre 1 e 50
numero_secreto <- sample(1:50, 1)
# Contador de tentativas
tentativas <- 0
# Primeira leitura do usuário
palpite <- as.integer(readline(prompt = "Tente adivinhar o número (1 a 50): "))
tentativas <- tentativas + 1
# Estrutura de repetição while
while (palpite != numero_secreto) {
if (palpite > numero_secreto) {
print("Tente um número menor")
}else{
print("Tente um número maior")
}
palpite <- as.integer(readline(prompt = "Digite novamente: "))
tentativas <- tentativas + 1
}
# Mensagem de acerto
cat("Parabéns! Você acertou em", tentativas, "tentativas.\n")
