for size in 15 18 21 24
do
cd unif-${size}
echo ============unif-${size}==========================
../skiplist_test_${size} 
cd ..
done
