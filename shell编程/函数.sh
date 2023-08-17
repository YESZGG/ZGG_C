compare()
{
    max=0

    if test $1 -gt $2;then
        max=$1
    else
        max=$2
    fi
    return $max
}

read -p "请输入两个整数：" a b
compare $a $b
echo "max:$max"

get_sum()
{
    return $((sum=`expr $a + $b`))
}
read -p "请输入两个整数：" a b
get_sum $a $b
echo "sum:$sum"