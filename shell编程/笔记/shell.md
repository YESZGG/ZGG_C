## shell编程
Shell编程是一种脚本编程语言，用于自动化任务和批处理脚本。下面是一些常见的Shell编程语法规则：

#### 1.注释：
使用#符号来注释一行代码。注释可以提供代码的解释和说明，不会被Shell解释器执行。

```shell
# This is a comment

# 多行注释
<< 'COMMENT'
....
COMMENT
```

#### 2.变量：
`shell`中的变量可以存储值和字符串，无需显式声明。变量的命名遵循以下规则：

#### 3.变量名必须以字母或下划线 _ 开头，后跟字母、数字或下划线。
#### 4.变量名区分大小写。
```shell
name="John"
age=25

str=hello #正确
str="hello" #正确
str=hello world #不正确
str="hello world" #正确
```
##### 5.获取变量的值：
使用$符号来获取变量的值。

```shell
name="shell"
echo "My name is $name"
```

##### 6.命令执行：
使用反引号 ``` 或$()` 来执行命令，并将输出结果赋给变量。

```shell
output=`ls`
output=$(ls)

echo "today is date"
echo "today is `date`" #反向引导
```

#### 7.输入输出重定向：
> 输出重定向    >   >>   
    命令的输出结果通常提交到标准输出设备（终端），但是也可以重新定个方向到其他位置，比如用一个文件来代替，这叫做输出重定向。在命令后添加>filename ，该命令(脚本)的输出就会写入到filename这个文件中，而不是写入终端。

##### 7.1.使用&gt;符号将命令的输出重定向到文件。
##### 7.2.使用&gt;&gt;符号将命令的输出追加到文件。
```shell
# 标准输出
china@ubuntu:~/shelldir$ ls  ---命令解析的结果输出在终端上
1.sh  2.sh  a.txt
china@ubuntu:~/shelldir$ ls >a.txt   ---命令的输出结果重定向到文件a.txt中
china@ubuntu:~/shelldir$ cat a.txt   
1.sh
2.sh
a.txt
china@ubuntu:~/shelldir$ ls >>a.txt  ---以追加的方式重定向到文件a.txt中 
china@ubuntu:~/shelldir$ cat a.txt 
1.sh
2.sh
a.txt
1.sh
2.sh
a.txt
china@ubuntu:~/shelldir$ echo "hello world">a.txt  --将一个字符串"hello world" 输出重定向到文件a.txt中
china@ubuntu:~/shelldir$ cat a.txt 
hello world

# 标准出错
china@ubuntu:~/shelldir$ asdsds 2>a.txt  --把出错信息重定向到文件a.txt中
china@ubuntu:~/shelldir$ cat a.txt 
asdsds：未找到命令
说明：
    2的右边不能有空格
gec@ubuntu:/mnt/hgfs/GZFX2308/9_shell编程/01/code$ bling > 1.txt  #错误写法没有2  
```
##### 7.3.使用&lt;符号将文件的内容作为输入传递给命令。
命令的输入通常是从标准输入设备(键盘)中请求的，但是也可以重新定个方向到其他位置，比如从一个文件中请求，这叫做输入重定向。命令<filename  该命令所有的输入请求都来自filename。
```shell
read str <1.txt # 从1.txt中读取数据，存储到变量str中
                # 但是只能读取一行数据

ls > files.txt 
# 将当前目录下的文件和文件夹列表输出到名为files.txt的文件中。
# >符号表示重定向，将输出结果写入文件而不是显示在屏幕上

echo "Hello" >> greetings.txt 
# 使用echo命令将字符串"Hello"追加到名为greetings.txt的文件中。
# >>符号表示追加，如果文件不存在则创建新文件，并将内容追加到文件末尾。

sort < input.txt 
# 执行了sort命令，将名为input.txt的文件中的内容作为输入，并将排序后的结果显示在屏幕上。
# <符号表示从文件中读取输入。
```

#### 8.算术运算命令expr
expr 是一个用于执行数值和字符串表达式求值的命令。它可以执行基本的算术运算、字符串操作和逻辑运算。以下是一些常见的 expr 命令的用法和示例：

1.算术运算：
* 加法：`expr $num1 + $num2`
* 减法：`expr $num1 - $num2`
* 乘法：`expr $num1 \* $num2` （乘法运算符 * 需要用反斜杠 \ 转义）
* 除法：`expr $num1 / $num2`
* 取余数：`expr $num1 % $num2`
  
例如，计算两个数的和：
```shell
   result=$(expr 10 + 5)
   echo $result  # 输出：15
```
2.字符串操作：
* 拼接字符串：`expr $string1 . $string2` （用点号 . 连接两个字符串）
* 字符串长度：`expr length $string`
* 提取子字符串：`expr substr $string $start $length `（从给定字符串中提取指定起始位置和长度的子字符串）

例如:
```shell
# 计算字符串长度
    string="Hello, World!"
    length=$(expr length "$string")
    echo $length  # 输出：13

    string="Hello, World!"
    length=${#string}
    echo $length  # 输出：13

# 连接两个字符串
    result=$(expr "Hello, " . "World!")
    echo $result  # 输出：Hello, World!
```

3.逻辑运算：
* 逻辑非：`expr ! $boolean`
* 逻辑与：`expr $boolean1 \&\&; $boolean2` （逻辑与运算符 &amp;&amp; 需要用反斜杠 \ 转义）
* 逻辑或：`expr $boolean1 \|\| $boolean2` （逻辑或运算符 || 需要用反斜杠 \ 转义）

例如，进行逻辑非运算：
```shell
   result=$(expr ! 0)
   echo $result  # 输出：1
```
需要注意的是，expr 命令在进行数值计算时，如果表达式中包含特殊字符（如 *、/ 等），需要使用反斜杠 \ 进行转义。此外，expr 命令的运算结果会被输出到标准输出，并可以通过变量捕获或通过管道传递给其他命令进行进一步处理。

通配符：

`*`  代表任意长度的任意字符
`？` 代表一个长度的任意字符
`[a-z]`: 代表一个长度的a-z之内的字符
``[az]``:  代表一个长度，只能匹配a或者z的内容
``[^az]``: 代表一个指定范围a/z之外的字符    与`[az]`相反！

`%`: 从右到左尽可能匹配少的字符
`%%`: 从右到左尽可能匹配多的字符
`#`: 从左到右尽可能匹配少的字符
`##`: 从左到右尽可能匹配多的字符

下面详细解释每个操作符的含义和用法：

- 1.`*`：代表任意长度的任意字符。使用通配符*可以匹配任意长度的任意字符序列。例如，abc*可以匹配以abc开头的任意字符序列。
- 2.`?`：代表一个长度的任意字符。使用通配符?可以匹配单个任意字符。例如，a?c可以匹配一个字符长的以a开头和c结尾的字符串。
- 3.`[a-z]`：代表一个长度的a-z之间的字符。使用字符范围`[a-z]`可以匹配一个字符长度的a-z之间的任意字符。例如，`[a-z]`bc可以匹配一个字符长的字母加上bc的字符串。
- 4.`[az]`、`[^az]`：`[az]`代表一个长度，只能匹配a或者z的内容；`[^az]`代表一个指定范围a/z之外的字符，与`[az]`相反。例如，`[az]`bc可以匹配一个字符长的a或者z加上bc的字符串；`[^az]`bc可以匹配一个字符长的不是a或者z开头加上bc的字符串。
- 5.`%`：从右到左尽可能匹配少的字符。使用 ` % ` 可以从变量的右边开始删除尽可能少的字符，直到匹配的字符为止。例如，`string="%Hello, World!%"echo "${string%Wo*}"`会输出%Hello,，因为它从右边开始删除，直到匹配到Wo为止。
- 6.`%%`：从右到左尽可能匹配多的字符。使用 ` %% ` 可以从变量的右边开始删除尽可能多的字符，直到匹配的字符为止。例如，`string="%Hello, World!%" echo "${string%%Wo*}"`会输出%Hello,，因为它从右边开始删除，直到匹配到最后一个Wo为止。
- 7.`#`：从左到右尽可能匹配少的字符。使用#可以从变量的左边开始删除尽可能少的字符，直到匹配的字符为止。例如，`string="%Hello, World!%" echo "${string#*o}"`会输出o, World!，因为它从左边开始删除，直到匹配到第一个o为止。
- 8.`##`：从左到右尽可能匹配多的字符。使用##可以从变量的左边开始删除尽可能多的字符，直到匹配的字符为止。例如，`string="%Hello, World!%" echo "${string##*o}"`会输出orld!，因为它从左边开始删除，直到匹配到最后一个o为止。

这些操作符可用于字符串匹配和替换，以及提取字符串的特定部分。可以根据具体的需求和上下文，选择适当的操作符来实现所需的字符串操作。

#### 9.test语句

test语句可以测试三种对象：字符串、整数、文件属性

##### 1、字符串测试
```shell
=           # 测试两个字符串内容是否完全一样
!=          # 测试两个字符串内容是否不一样
-Z(zero)    # 测试字符串是否为空，为空，返回true
-n(null)    # 测试字符串是否不为空，不为空，返回tru
```
在测试字符串变量时，需要防止字符串为空的技巧:
引用变量后加一个额外的字符: 
 ```shell
 test ${A}x = ${B}x
 ```
##### 2、整数测试
**下面是常用的比较操作符：**
> a -eq b: **equal**      测试两个整数是否**相等**
> a -ne b: **not equal**  测试两个是否**不相等**
> a -gt b: **greater** 测试a是否**大于**b
> a -ge b: **greater or equal** 测试a是否**大于等于**b
> a -lt b: **little** 测试a是否**小于**b
> a -le b: **little or equal** 测试a是否**小于等于**b

##### 3、文件测试
> -d name 测试name是否是一个目录(dir) //  if  test -d  1.   txt; then
> -f name 测试name是否是一个普通文件(file)
> -L name 测试name是否为符号链接文件(Link)
> -r name 测试name文件是否存在并可读(read)
> -w name 测试name文件是否存在并可写(write)
> -x name 测试name文件是否存在并可执行(excute)
> -s name 测试name文件是否存在并且长度不为o(size)
> -e name 测试name文件是否存在并且长度不为0(size)
> f1 -nt f2 测试f1 是否比f2更新(newer than)
> f1 -ot f2 测试f1 是否比f2更旧(older than)

![Alt text](/笔记/image/image_1.png)

test命令可以用`[ ]`来简写

> test expression --->  [ expression ]

##### test的复合表达式
组合了两个或两个以上的表达式称为复合表达式，你可以用test([])内置的的操作符，也可以用条件操作符(&& || !)来实现
- 1.使用test内置的操作符
```shell
test expr1 "test_buildin" expr2
    test_buildin:
            -a  and
            -o  or
```
- 2.使用条件操作符(&& || !)
```shell
# 这里的op 表示比较操作符
test expr1 "op" test expr2
```
比如：
```shell
test $A = '1' && test $B = '1'
    [ $A = '1' ] && [ $B = '1' ] 
```   

```shell
# 判断变量值是否相等
if [ "$var1" -eq "$var2" ]; then
    echo "Variables are equal."
fi

# 判断字符串是否相等
if [ "$str1" = "$str2" ]; then
    echo "Strings are equal."
fi

# 判断数值大小关系
if [ "$num1" -gt "$num2" ]; then
    echo "num1 is greater than num2."
fi
```
#### 10.条件语句：
使用条件语句来进行逻辑判断和分支执行。
##### if语句格式：
- 第一种：
> if command ; then
     ...语句列表
fi
- 第二种：
> if command ; then
    ...语句列表
else
  ...语句列表
fi
- 第三种：
> if command ; then
    ...语句列表
elif command ; then
  ...语句列表
else
    ...语句列表
fi

示例：
```shell
if [ $age -gt 18 ]; then
    echo "You are an adult."
else
    echo "You are a minor."
fi
```
1.比较两个数值大小
```shell
read -p "请输入两个整数：" val1 val2 
#if  [ $val1 -gt $val2 ];then
if  test $val1 -gt $val2;then
    echo "max:$val1"
else
    echo "max:$val2"
fi
```
2.判断一个文件是否存在，若存在则打印文件的内容，不存在则输出字符串报错

```shell
read -p "请输入文件名：" filename
if test -s $filename;then
    echo "`cat $filename`"
else 
    echo "该文件不存在"
fi
```
##### case多路分支语句格式
case语句是一种多路分支语句，它允许根据不同的条件执行不同的操作。以下是case语句的基本语法：
> case expression in
    pattern1)
        command1
        ;; # 这里的 ;; 不能省略，类似于switch case 的break;
    pattern2)
        command2
        ;;
    pattern3)
        command3
        ;;
    *)
        default_command
        ;;
esac

`expression`是要比较的值或变量。`pattern`用于指定匹配的模式，如果`expression`与某个pattern匹配，则执行相应的command。每个`pattern`后面以括号结束，并以两个分号 ;; 表示命令块的结束。最后的`*)`表示默认情况，即当没有任何`pattern`匹配时将执行`default_command`。

下面是一个示例，将演示如何使用case语句根据用户输入显示不同的消息：

```shell
#!/bin/bash

echo "请选择一种水果："
echo "1) 苹果"
echo "2) 香蕉"
echo "3) 橙子"
read choice

case $choice in
    1)
        echo "您选择了苹果。"
        ;;
    2)
        echo "您选择了香蕉。"
        ;;
    3)
        echo "您选择了橙子。"
        ;;
    *)
        echo "无效的选择。"
        ;;
esac
```
在这个示例中，根据用户输入的数值选择不同的分支。根据用户的选择，将显示相应的消息。如果用户输入的值不是1、2或3，则显示"无效的选择"。
case语句是一种有效的控制流程工具，可以用于在脚本中实现逻辑分支和条件操作。你可以根据具体的需求添加更多的分支和相应的操作。

#### 11.循环：
使用循环结构来重复执行一段代码。常见的循环有for循环和while循环。

##### 11.1 for循环
```shell
for i in 1 2 3 4 5; 
do
    echo $i
done
```
###### 1.利用for循环，求1+...+100的和
```shell
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
```
##### 11.2 while循环
示例：
```shell
counter=0
while [ $counter -lt 5 ]; 
do
    echo $counter
    counter=$((counter+1))
done
```

##### 11.3 until
until是一种循环结构，它在条件为假（false）时执行一段代码块。与while循环不同，until循环会一直执行，直到条件为真（true）为止。
以下是until循环的基本语法：
```shell
until condition
do
    # Code block to be executed
done
```
`condition`是一个判断条件，只有在`condition`为假时，才会执行循环内的代码块。在每次循环执行之前，会先判断condition的值。如果`condition`为假，那么循环会继续执行，直到`condition`为真为止。

下面是一个示例，演示如何使用`until`循环来计算一个数的阶乘：
```shell
#!/bin/bash

echo "请输入一个正整数："
read number

fact=1
counter=1

until [ $counter -gt $number ]
do
    fact=$((fact * counter))
    counter=$((counter + 1))
done

echo "阶乘 $number! = $fact"
```

在这个示例中，用户被要求输入一个正整数。然后，通过until循环计算了该数的阶乘，将结果存储在fact变量中。

循环中的condition检查counter是否大于输入的数字number。如果是，那么条件为真，循环结束。否则，执行循环内的代码块，计算阶乘并递增counter的值。
until循环非常有用，可以在需要在条件为假时执行一段代码块的情况下使用。可以根据不同的条件编写更复杂的逻辑来控制循环的执行。

until与while功能相似，所不同的是只有当测试的命令或表达式的值为假时，才执行循环体中的命令列表。若条件成立则退出循环。这一点与while恰好相反。

##### 11.4 break 和 continue
`break n`    跳出n层循环
`continue n` 跳到n层循环语句的下一轮循环去
`break` 和 `continue` 后面不加n,则和C语言里面的含义一样

#### 11.函数：
使用函数来封装一段可重用的代码。

1.函数定义
```shell
function greet() {
    echo "Hello, $1!"
}
```
2.函数调用
`greet "John"`

注意:
1、函数的返回值的大小不超过一个字节
2、SHELL没有变量作用域，如果出现重复变量名会认为是同一个。

示例：
```shell
# 实现比较两个数的最大值并且返回
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
```