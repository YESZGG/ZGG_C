#!/bin/bash
###
 # @Description: 
 # @version: 1.80.1
 # @Author: ZGG
 # @Date: 2023-08-17 10:25:56
 # @LastEditors: ZGG
 # @LastEditTime: 2023-08-17 23:23:48
### 


# 直接键盘输入
# read val
# echo $val

# ls > files.txt
# echo "Hello" >> 1.txt
# sort < 1.txt
# 提示输入
read -p "input data:" val1 val2 val3
echo $val1 $val2 $val3

# 多行注释的写法
#<< 'COMMENT'
# 输入重定向
read str < 1.txt #获取文本数据  (只能从文本中获取一行数据)

echo $str
#COMMENT

read -p "请输入姓名 年龄 分数"  name1 age1 score1
read -p "请输入姓名 年龄 分数"  name2 age2 score2
read -p "请输入姓名 年龄 分数"  name3 age3 score3

 
printf  "%-10s %-8s %-4s\n" 姓名  年龄  分数
printf  "%-10s %-8s %-4s\n" $name1  $age1  $score1
printf  "%-10s %-8s %-4s\n" $name2  $age2  $score2
printf  "%-10s %-8s %-4s\n" $name3  $age3  $score3