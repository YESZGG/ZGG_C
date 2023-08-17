#!/bin/bash

#加法 +
a=10
b=20
val=`expr $a + $b` #(注意：操作数与运算符，前后至少要有一个空格)
echo "val:$val"  #--->val:30


#乘法 \*
a=10
b=20        
val=`expr $a + $b \* 4`  # (且不支持括号)
echo "val:$val"  #--->val:90