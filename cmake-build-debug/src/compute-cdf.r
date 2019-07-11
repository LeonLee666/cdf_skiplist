size=334863
x <- scan('key.txt')
cdf <- ecdf(x)
#plot(cdf)
sink("dataset.txt")
for( i in 1:size) 
	cat(x[i],",",cdf(x[i]),"\n")
sink()
