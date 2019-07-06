for size in 15 18 21 24
do
cd unif-${size}
echo ===========================================
for i in 0 1 2 3
do 
../skiplist_test_${size} $i
done
cd ..
done
