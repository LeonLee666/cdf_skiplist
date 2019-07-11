for i in {1..10}
do
	cd normal-$i
	echo =======normal $i============
	../skiplist_test_21 ${alg}
	cd ..
done
