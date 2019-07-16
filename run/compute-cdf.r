size=334863
x <- scan('key.dat')
cdf <- ecdf(x)
#plot(cdf)
sink("dataset.dat")
for( i in 1:size) 
	cat(x[i],",",cdf(x[i]),"\n")
sink()
