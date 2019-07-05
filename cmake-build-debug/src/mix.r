size=2097152/2
x <- rnorm(size,0,10)
y <- rnorm(size,100,10)
sink("key.txt")
for( i in 1:size)
	cat(x[i],"\n")
for( i in 1:size)
	cat(y[i],"\n")
sink()