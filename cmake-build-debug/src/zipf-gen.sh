for i in 1 3 5 7 9
do
	cd zipf-$i
	echo generating dataset 0.$i
	Rscript zipf.r
	cd ..
done
