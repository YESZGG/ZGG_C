

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [运算符重载](#运算符重载)
      - [运算符重载的定义](#运算符重载的定义)
      - [语法格式：](#语法格式)
      - [可重载运算符/不可重载运算符](#可重载运算符不可重载运算符)
      - [什么时候重载运算符时声明为友元？](#什么时候重载运算符时声明为友元)
      - [输出流和输出流重载](#输出流和输出流重载)
- [string 类](#string-类)
    - [构造函数(Constructors)](#构造函数constructors)
      - [语法:](#语法)
    - [操作符(Operators)](#操作符operators)
      - [语法:](#语法-1)

<!-- /code_chunk_output -->


# 运算符重载
重载就是赋予一个实物新的功能，重新载入，更新。以往的运算符只支持，**基本的数据类型操作`(char,short,int,fioat..)`，无法操作用户自定义的数据类型`(struct student,char buf[1024])`**，这时候我们就要**利用运算符重载赋予该运算符新的功能。**
#### 运算符重载的定义
运算符重载是指通过定义类的成员函数或全局函数，为已有的运算符赋予新的含义或功能。

#### 语法格式：
```cpp
返回类型 operator 运算符 (参数列表) {
    // 实现运算符重载的代码
}
```
**运算符函数可以作为成员函数或非成员函数进行重载 。**

作用：
1. 提供更自然的语法和更直观的操作，使得类对象可以像内置类型一样进行运算。
2. 增加代码的可读性和可维护性，使得代码更易于理解和使用。
3. 可以根据类的特性和需求，自定义运算符的行为，实现更灵活的功能。

特点：
1. 运算符重载是C++中的一项重要特性，可以使得类对象的使用更加直观和方便。
2. 运算符重载可以应用于内置类型和自定义类型，使得自定义类型的操作更像内置类型。
3. 运算符重载可以是成员函数形式或全局函数形式，根据需要选择合适的形式。
4. 运算符重载的函数名必须以`operator`关键字开头，后面跟着要重载的运算符。

#### 可重载运算符/不可重载运算符
下面是可重载的运算符列表：

| 双目算术运算符 | `+` (加)，`-` (减)，`*` (乘)，`/` (除)，`%` (取模) |
| :------------: | :------------------------ |
| 关系运算符   | `==` (等于)，`!=` (不等于)，`<` (小于)，`>` (大于)，`<=` (小于等于)，`>=` (大于等于) |
| 逻辑运算符   | `||` (逻辑或)，`&&` (逻辑与)，`!` (逻辑非) |
| 单目运算符   | `+` (正)，`-` (负)，`*` (指针)，`&` (取地址) |
| 自增自减运算符 | `++` (自增)，`--` (自减) |
| 位运算符     | `|` (按位或)，`&` (按位与)，`~` (按位取反)，`^` (按位异或), `<<` (左移), `>>` (右移) |
| 赋值运算符   | `=`，`+=`，`-=`，`*=`，`/=`，`%=`，`&=`，`|=`，`^=`，`<<=`，`>>=` |
| 空间申请与释放 | `new`，`delete`，`new[]`，`delete[]` |
| 其他运算符   | `()` (函数调用)，`->` (成员访问)，`,` (逗号)，`[]`(下标) |

下面是不可重载的运算符列表：

`.`：成员访问运算符
`.*`, `->*`：成员指针访问运算符
`::`：域运算符
`sizeof`：长度运算符
`?:`：条件运算符
`#`： 预处理符号


以下是一个运算符重载的示例代码，演示了如何重载加法运算符：

```cpp
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    Complex operator+(const Complex& c) {
        Complex result;
        result.real = this->real + c.real;
        result.imag = this->imag + c.imag;
        return result;
    }

    void display() {
        std::cout << real << " + " << imag << "i" << std::endl;
    }
};

int main() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3 = c1 + c2;

    c3.display();

    return 0;
}
```

在上述代码中，通过重载加法运算符`+`，使得两个Complex对象可以直接相加，得到新的Complex对象。运算符重载的函数`operator+`被定义为类的成员函数，用于实现加法运算符的功能。


#### 什么时候重载运算符时声明为友元？

在类中重载运算符时，需要将其声明为友元的情况包括：

1. 当重载的运算符函数不能通过类的成员访问私有或保护数据时，可以将该函数声明为友元。这允许函数访问类的私有或保护成员。

2. 如果重载的运算符函数需要访问另一个类的私有或保护成员，那么它也需要声明为友元。这样，两个类之间的成员才能互相访问私有或保护数据。

需要注意的是，不是所有的运算符重载都需要声明为友元。只有当需要访问其他类的私有或保护成员时，或者该函数无法通过类的成员来访问类的私有或保护成员时，才需要使用友元函数。否则，运算符重载函数可以直接作为类的成员函数进行定义和访问类的成员。

以下是一些常见的需要声明为友元的运算符：

1. 二元运算符（+、-、*、/、%、<、>等）：如果要重载一个二元运算符，其中一个操作数是当前类的对象，而另一个操作数是其他类的对象，而且需要访问该类的私有或保护成员，那么需要将这个运算符重载函数声明为友元。

2. 自增自减运算符（++、--）：当重载自增（++）和自减（--）运算符，需要对类的私有或保护成员进行修改，或者需要访问其他类的私有或保护成员时，需要将这些运算符重载函数声明为友元。

3. 索引运算符（[]）：如果重载索引运算符，并且需要访问其他类的私有或保护成员来实现索引功能，就需要将该运算符重载函数声明为友元。

4. 函数调用运算符（()）：当重载函数调用运算符，并且需要访问其他类的私有或保护成员以提供函数调用的实现时，需要将该运算符重载函数声明为友元。


#### 输出流和输出流重载
输出流（`<<`）和输入流（`>>`）是C++中常用的运算符，用于实现对象的输入和输出。它们可以通过运算符重载来实现对自定义类的对象进行输入和输出操作。

输出流重载 (`<<`)：
当你想以特定方式将自定义类的对象输出到标准输出或者其他输出流时，你可以重载输出流运算符 (`<<`)。

```cpp
#include <iostream>

class MyClass {
private:
    int data;

public:
    MyClass(int d) : data(d) {}

    friend std::ostream& operator<<(std::ostream& os, const MyClass& obj);
};

std::ostream& operator<<(std::ostream& os, const MyClass& obj) {
    return os << "MyClass object: " << obj.data;
}

int main() {
    MyClass myObj(42);
    std::cout << myObj << std::endl;  // 输出：MyClass object: 42

    return 0;
}
```

在上面的例子中，我们重载了 `operator<<` 作为 `MyClass` 的友元函数。该函数接受一个输出流对象 (`std::ostream&`) 和一个常量引用的 `MyClass` 对象作为参数，并将对象的信息输出到流中。在 `main` 函数中，我们使用 `cout` 输出流来打印 `myObj` 的信息。

输入流重载 (`>>`)：
类似地，当你想从标准输入或其他输入流中以特定方式读取数据到自定义类的对象中时，你可以重载输入流运算符 (`>>`)。

```cpp
#include <iostream>

class MyClass {
private:
    int data;

public:
    MyClass() : data(0) {}

    friend std::istream& operator>>(std::istream& is, MyClass& obj);
};

std::istream& operator>>(std::istream& is, MyClass& obj) {
    return is >> obj.data;
}

int main() {
    MyClass myObj;
    std::cout << "Enter an integer: ";
    std::cin >> myObj;

    std::cout << "You entered: " << myObj << std::endl;

    return 0;
}
```

在上面的例子中，我们重载了 `operator>>` 作为 `MyClass` 的友元函数。该函数接受一个输入流对象 (`std::istream&`) 和一个引用的 `MyClass` 对象作为参数，并从流中读取数据到对象的成员变量中。在 `main` 函数中，我们使用 `cin` 输入流来获取用户输入并将其存储到 `myObj` 的 `data` 成员变量中，随后输出该值。

通过运算符重载，我们可以自定义类的对象在输入和输出流中的行为，使其适应特定的需求和格式。

# string 类

### 构造函数(Constructors)
#### 语法: 
```c++
  string();
  string( size_type length, char ch );
  string( const char *str );
  string( const char *str, size_type length );
  string( string &str, size_type index, size_type length );
  string( input_iterator start, input_iterator end );
```

字符串的构造函数创建一个新字符串，包括: 

- 以`length`为长度的ch的拷贝（即`length`个`ch`） 
- 以`str`为初值 (长度任意), 
- 以`index`为索引开始的子串，长度为`length`, 或者 
- 以从`start`到`end`的元素为初值. 


### 操作符(Operators) 
#### 语法: 
```cpp
  ==
  >
  <
  >=
  <=
  !=    // 比较
  +     // 连接两个字符串
  +=    // 连接两个字符串
  []    // 取下标
```
 
你可以用 ==, >, <, >=, <=, and !=比较字符串. 可以用 + 或者 += 操作符连接两个字符串, 并且可以用[]获取特定的字符.
```c++
basic_string &append(const char *str)
// 将给定的C风格字符串附加到当前字符串的末尾。参数str是要附加的C风格字符串。

const char *c_str()
// 返回一个指向当前字符串内部字符数组的C风格字符串的指针。它用于在需要使用C风格字符串的情况下访问字符串的内容。

size_type copy(char *str, size_type num, size_type index)
// 将当前字符串中从索引index开始的num个字符复制到给定的字符数组str中。返回实际复制的字符数。

basic_string &erase(size_type index = 0, size_type num = npos)
// 从当前字符串中删除指定范围内的字符。可选地，可以指定要删除的起始索引index和删除的字符数num。如果不提供参数，则默认删除整个字符串。

size_type find(const char *str, size_type index)
// 在当前字符串中寻找第一次出现给定C风格字符串str的位置。可选地，可以指定要搜索的起始索引index。返回找到的位置索引，如果未找到则返回npos。

size_type rfind(const char *str, size_type index)
// 在当前字符串中逆向寻找最后一次出现给定C风格字符串str的位置。可选地，可以指定要反向搜索的起始索引index。返回找到的位置索引，如果未找到则返回npos。

basic_string &insert(size_type index, const char *str)
// 在当前字符串的指定索引位置插入给定的C风格字符串str。参数index是插入位置的索引。

size_type length()
// 返回当前字符串的长度（即字符的个数）。

basic_string &replace(size_type index, size_type num, const char *str)
// 用给定的C风格字符串str替换当前字符串中从索引index开始的num个字符。

basic_string substr(size_type index, size_type num = npos)
// 返回一个新的字符串，它是当前字符串中从索引index开始的连续num个字符组成。如果不提供num参数，则默认为从index到字符串末尾的所有字符。
```

下面是我的string类的实现：
[string类的实现](https://github.com/YESZGG/ZGG_C)
在c++中的string目录中.


