for i in {1..10}
do
echo ===================
for alg in {0..3}
do
cd $i
	../skiplist_test ${alg}
cd ..
done
done
