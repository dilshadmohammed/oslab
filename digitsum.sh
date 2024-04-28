read -p "Enter a number: " n
sum=0
while ((n!=0))
do
    sum=$((sum+n%10))
    n=$((n/10))
done
echo "sum = $sum"