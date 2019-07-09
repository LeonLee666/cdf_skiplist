for size in 1 3 5 7 9
do
cd zipf-${size}
echo ===========================================
for i in 0 1 2 3
do 
../skiplist_test_21 $i
done
cd ..
done
