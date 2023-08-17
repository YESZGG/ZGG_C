#!/bin/bash
string="%Hello, World!%"
echo "${string%Wo*}"  # 输出：%Hello, 

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
read -p "请输入两个整数：" val1 val2 
#if  [ $val1 -gt $val2 ];then
if  test $val1 -gt $val2;then
    echo "max:$val1"
else
    echo "max:$val2"
fi

# 判断一个文件是否存在，若存在则打印文件的内容，不存在则输出字符串报错

read -p "请输入文件名：" filename
if test -s $filename;then
    echo "`cat $filename`"
else 
    echo "该文件不存在"
fi

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


# case指令类似于switch case
# read val
# case $val  in
#     1)
#         echo "one"
#         ;;
#     2)
#         echo "two"
#         ;;
#     *)
#         echo "error"
#         ;;
# esac

# read -p "input data:" val
# case $val in
#     [0-9])
#         echo "this is 0-9"
#         ;;
#     [a-d]|[m-z])
#         echo "this is a-d m-z"
#         ;;   
#     h*)
#         echo "h....."
#         ;;
#     [-]*)
#         echo "---------"
#         ;;
#     *)
#         echo "other"
#         ;;
# esac

# 如果没有进行命令行传参数，则进行提示
if [ $# -ne 1 ];then
    echo "请先传递参数:文件名"
fi

# 判断文件是否存在并且判断数据大小
if [ -s $1 ];then
    # 有数据
    fileContent=`cat $1`
    case $fileContent in
        10)
            echo "large"
            ;;
        5)
            echo "middle"
            ;;
        1)
            echo "small"
            ;;
        *)
            echo "other"
            ;;
    esac
else
    echo "该文件不存在或者没有数据"
fi