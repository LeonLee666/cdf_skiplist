sink("dataset.txt")
size=16777126
x <- runif(size)
cdf <- ecdf(x)
for( i in 1:size)
	cat(x[i],",",cdf(x[i]),"\n")
sink()
