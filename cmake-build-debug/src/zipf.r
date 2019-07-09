library(methods)
library(stats4)
library(splines)
library(VGAM)

delta <- 0.1
bound <- 64000000
size <- 2097152
x <- rzipf(size,bound,delta)
# x <- sort(x)
sink("dataset.txt")
cdf <- ecdf(x)
for( i in 1:size)
	cat(x[i],",",cdf(x[i]),"\n")
sink()
