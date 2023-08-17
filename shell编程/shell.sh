#!/bin/bash

# Shell语法知识点示例

### 一、shell变量
# shell语法中为变量赋值时，等号的左右两边不允许有空格
# 变量的引用，需要在变量前加入美元符号$

# echo $str 或 echo ${str}

# 变量的种类
# 1.自定义变量
# 2.系统环境变量
# 3.位置变量

# 获取命令行传递的参数
name=$1  
echo "Hello $name"  # 输出 hello world
# 获取变量
str=helloworld
echo $str

# 要空格，必须有" "
# str=hello #正确
# str="hello" #正确
# str=hello world #不正确
# str="hello world" #正确

# 在" "内可以对变量进行引用
str=hello
echo "$str world"

# 3.在" "内部是可以使用shell命令，但是使用shell命令需要使用反引导` `来括住命令
echo "today is date"
echo "today is `date`" #反向引导

# 单引号  在单引号里面的内容，看做是纯粹的字符串
# echo `today is date` # 结果： today is date
# echo `$str world`    # 结果： $str world 不能在单引号里面引用变量,需加""

# 给变量赋值的几种方式：
# 1.直接赋值
# str=helloworld
# 2.传参
# echo $1
# 3.输入重定向(通过read来赋值)
# read str < 1.txt 

### 二、算术运算命令expr
# expr主要是用于简单的整数计算，包括 加(+)、减(-)、乘(\*)、除(/)、取余(%)
#加法 +
a=10
b=20
val=`expr $a + $b` #(注意：操作数与运算符，前后至少要有一个空格)
echo "加法 val:$val"  #--->val:30


#乘法 \*
a=10
b=20        
val=`expr $a + $b \* 4`  # (且不支持括号)
echo "乘法 val:$val"  #--->val:90

### 三、字符串处理

str="hello world"
echo "hello world字符串长度为：${#str}"

# 通配符
# *  代表任意长度的任意字符
# ？ 代表一个长度的任意字符
# [a-z]: 代表一个长度的a-z之内的字符
# [az]:  代表一个长度，只能匹配a或者z的内容
# [^az]: 代表一个指定范围a/z之外的字符    与[az]相反！

# %: 从右到左尽可能匹配少的字符
# %%: 从右到左尽可能匹配多的字符
# #: 从左到右尽可能匹配少的字符
# ##: 从左到右尽可能匹配多的字符

### 四、read
<< 'COMMENT'
read val1
read -p "input data:" val1 val2 val3
read val<1.txt //从文本输入    
COMMENT

### 五、test语句

# test语句可以测试三种对象：字符串、整数、文件属性
# 1、字符串测试
# =         测试两个字符串内容是否完全一样
# !=          测试两个字符串内容是否不一样
# -Z(zero)    测试字符串是否为空，为空，返回true
# -n(null)    测试字符串是否不为空，不为空，返回true

# 在测试字符串变量时，需要防止字符串为空的技巧:
# 引用变量后加一个额外的字符: 
# test ${A}x = ${B}x
# 2、整数测试
# a -eq b: equal测试两个整数是否相等
# a -ne b: not equal 测试两个是否不相等
# a -gt b: greater 测试a是否大于b
# a -ge b: greater or equal 测试a是否大于等于b
# a -lt b: little 测试a是否小于b
# a -le b: little or equal 测试a是否小于等于b
# 3、文件测试
# -d name 测试name是否是一个目录(dir) //  if  test -d  1.txt;then
# -f name 测试name是否是一个普通文件(file)
# -L name 测试name是否为符号链接文件(Link)
# -r name 测试name文件是否存在并可读(read)
# -w name 测试name文件是否存在并可写(write)
# -x name 测试name文件是否存在并可执行(excute)
# -s name 测试name文件是否存在并且长度不为o(size)
# -e name 测试name文件是否存在并且长度不为0(size)
# f1 -nt f2 测试f1 是否比f2更新(newer than)
# f1 -ot f2 测试f1 是否比f2更旧(older than)


# read -p "input data:" val
# if test ` expr $val %  2 ` -eq 0 ;then
#     echo "偶数"
# else
#     echo "奇数"
# fi

# read -p "input str:" str
# if [ $str = "hello" ];then
#     echo "yes"
# else
#     echo "no"
# fi


# 比较两个数值大小
# read -p "请输入两个整数：" val1 val2 
# #if  [ $val1 -gt $val2 ];then
# if  test $val1 -gt $val2;then
#     echo "max:$val1"
# else
#     echo "max:$val2"
# fi

### 六、if分支语句
<< 'COMMENT'
第一种：
if command ; then
     ...语句列表
fi
第二种：
if command ; then
    ...语句列表
else
  ...语句列表
fi
第三种：
if command ; then
    ...语句列表
elif command ; then
  ...语句列表
else
    ...语句列表
fi
COMMENT

# 判断一个文件是否存在，若存在则打印文件的内容，不存在则输出字符串报错

# read -p "请输入文件名：" filename
# if test -s $filename;then
#     echo "`cat $filename`"
# else 
#     echo "该文件不存在"
# fi

# 用shell编写脚本程序：读取变量dir，如果该变量代表的值是目录，则切换到该目录下，
# 并在该目录下创建空文件file.txt，将“hello  world ”写到该文件中
# 如果该目录不存在则创建该目录并切换过去，并显示当前绝对路径

# read -p "请输入目录名：" dir #这里注意需要空格
# if test -d $dir;then
#     cd $dir
#     touch file.txt
#     echo "hello world" > file.txt
# else
#     mkdir $dir
#     cd $dir
#     pwd # 显示当前绝对路径
# fi

### 七、多分支语句
<< 'COMMENT'
case  expression   in
    pattern1)
        ...语句列表
        ;; //作用类似与C语言的break,这里;;不能省
    pattern2)
        ....语句列表
        ;;
    patternn)
        ....语句列表
        ;;
   *)   ---其他值
        ....语句列表
        ;;
esac
COMMENT

# 总结
# 1）expression 既可以是一个变量、一个数字、一个字符串，还可以是一个数学计算表达式，或者是命令的执行结果，只要能够得到 expression 的值就可以。
# 2）pattern 可以是一个数字、一个字符串，甚至是一个简单的正则表达式。    
# 3）case语句真正的功能强大之处在于它可以使用模式而不是固定的字符串匹配。一个模式是由一串正规字符和特殊的通配符组成的字符串，该模式可以用正则表达式。

# case指令类似于switch case
echo "case分支语句"
read -p "请输入1或2:(否则输出error)" val
case $val  in
    1)
        echo "one"
        ;;
    2)
        echo "two"
        ;;
    *)
        echo "error"
        ;;
esac

### 八、循环
### 8.1、for循环
# 格式
# for 变量名 in 单词表
# do
#     语句列表
# done

echo " 利用for循环，求1+...+100的和 "
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

### 8.2、while循环
# 格式
# while 命令或表达式
# do
#     语句列表    
# done
# ===>也可以用C语言的while风格
# while(())
# do
#     语句列表
# done


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
COMMENT

echo " 利用while循环，求1+...+100的和 "
i=1
sum=0
# while((i<=100))
# while [ $i -le 100 ]
while test $i -le 100
do
    sum=$((sum+i))
    i=$((i+1))
done

echo "1到100的和是:$sum"

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

echo "1到100的和是:$sum"


###  8.3、until
# 格式：
# until 命令或表达式
# do
# done
# until与while功能相似，所不同的是只有当测试的命令或表达式的值为假时，才执行循环体中的命令列表。若条件成立则退出循环。这一点与while恰好相反。

# 8.4、break 和 continue
# break n跳出n层循环
# continue n 跳到n层循环语句的下一轮循环去
# break 和 continue 后面不加n,则和C语言里面的含义一样

i=1
sum=0
# until((i>=100))
# until [ $i -gt 100 ]
# until 为假时一直执行，为真时跳出循环
echo " 利用until，求1+...+100的和"
until test $i -gt 100
do
    sum=$((sum+i))
    i=$((i+1))
done

echo "1到100的和是:$sum"


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

### 九、函数 
# 函数的定义
echo " 输入两个数，定义函数求和 "
get_sum()  
{
    return `expr $1 + $2`
}
read var1 var2
get_sum $var1 $var2 # 函数的调用
echo $? # 获取函数的返回值
# 注意:
# 1、函数的返回值的大小不超过一个字节
# 2、SHELL没有变量作用域，如果出现重复变量名会认为是同一个。


# 编写一个脚本，封装一个函数实现比较两个数的最大值并且返回
echo " 输入两个整数比较两个数的最大值并且返回 "
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


# 编写一个脚本，实现一个函数求a+...+b的和     a:5     b=10
echo " 输入两个整数,实现一个函数求a+...+b的和 "   
sum=0
get_sum()
{   

    for((i=$a; i<=$b; i++))
    do
        sum=`expr $sum + $i`
    done
}
read -p "请输入两个整数：" a b
get_sum $a $b
echo "sum:$sum"


# 用正则表达式描述IPV4的网络地址
# asdsdss192.a.65.4ddgdgsgsfdg 123adsad 123  sa 676761234safd192.168.63.100fed 
# 987685dfgfdgf192.168.63.1dsabcd245345456 abcdefg
# ([0-9]{1,3}\.){3}[0-9]{1,3}