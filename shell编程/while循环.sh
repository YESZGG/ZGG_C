# 从键盘上获取一个最小值和最大值，打印出两个之间的所有取值

<< 'COMMENT'
read -p "min:" min
read -p "max:" max

# while test $min -le $max
# while [ $min -le $max ]
while((min <= max))
do 
    # echo "$min" # 换行打印
    echo -n "$min " # 不换行打印
    if((min == max));then
        echo "完成"
    fi
    min=`expr $min + 1`
done

i=1
# while((i<=100))
# while [ $i -le 100 ]
while test $i -le 100
do
    sum=$((sum+i))
    i=$((i+1))
done

echo "sum:$sum"

i=1
sum=0
# until((i>=100))
# until [ $i -gt 100 ]
# until 为假时一直执行，为真时跳出循环
until test $i -gt 100
do
    sum=$((sum+i))
    i=$((i+1))
done

echo "sum:$sum"
COMMENT

while true; do
    read -p "请输入数据: " input

    if [[ "$input" == "exit" ]]; then
        echo "退出"
        break
    # elif ((input < 100)); then
    elif test $input -lt 100;then
        echo "值: $input"
    else
        echo "other"
    fi
done