sink("dataset.dat")
size=2097152
x <- rnorm(size,10,10)
cdf <- ecdf(x)
for( i in 1:size)
	cat(x[i],",",cdf(x[i]),"\n")
sink()
