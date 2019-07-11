for size in 1 3 5 7 9
do
cd zipf-${size}
echo ===========zipf-${size}======================
../skiplist_test_21 
cd ..
done
