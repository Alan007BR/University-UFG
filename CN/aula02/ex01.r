# conversão binario para decimal
a <- c(1,0,1,0,1,1,0,1,1)
b <- numeric()
j <- length(a)

b[j] = a[j]
for(i in (j-1):1){
    b[i] = a[i] + 2*b[i+1]
}
b
print(b)