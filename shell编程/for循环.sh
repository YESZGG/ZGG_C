#!/bin/bash

# 方法一：
sum=0

for num in {1..100}
do
    sum=$((sum + num))
done

echo "1到100的和是：$sum"


# 方法二：
sum=0

for ((i=1; i<=100; i++))
do
    # sum=$((sum + i))
    sum=`expr $sum + $i`
done

echo "1到100的和是：$sum"
