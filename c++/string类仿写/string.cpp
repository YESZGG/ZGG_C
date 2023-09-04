#include "string.h"

using namespace std;

// 重载拷贝函数 实现将初始化的字符串拷贝到字符串对象中
Mystring::Mystring(const char *str)
{
    size_t i = 0;
    this->length = mystrlen(str);
    this->str = new char[this->length + 1];
    for (i = 0; i < this->length; i++)
    {
        this->str[i] = str[i];
    }
    this->str[i] = '\0';
}

// 深拷贝
Mystring::Mystring(const Mystring &other)
{
    size_t i = 0;
    this->length = other.length;
    this->str = new char[this->length + 1];
    for (i = 0; i < this->length; i++)
    {
        this->str[i] = other.str[i];
    }
    this->str[i] = '\0';
}

/* 将指定长度的字符从 str 中复制到字符串对象中，并在最后添加一个 null 字符 ('\0') 来表示字符串的结束。 */
Mystring::Mystring(const char *str, size_type length)
{
    size_t i = 0;
    this->length = length;
    this->str = new char[this->length + 1];
    for (i = 0; i < this->length; i++)
    {
        this->str[i] = str[i];
    }
    this->str[i] = '\0';
}

/* 从给定的索引位置开始，连续复制指定长度的字符到字符串对象中。如果指定的索引位置超过了源字符串的长度，
或者指定的长度超出了源字符串可用范围，则只会复制源字符串中剩余的部分。 */
Mystring::Mystring(Mystring &str, unsigned index, unsigned length)
{
    // 如果索引位置超过源字符串长度时，不进行复制
    if (index > str.length)
    {
        // 如果超过了，说明没有字符需要复制，所以直接创建一个空字符串对象。
        this->length = 0;
        this->str = new char[1];
        this->str[0] = '\0';
    }
    else
    {
        unsigned maxLength = str.length - index;
        this->length = (length < maxLength) ? length : maxLength; // 确定要复制的字符数，确保不会超出源字符串的可用范围
        this->str = new char[this->length + 1];

        // 进行拷贝
        for (unsigned i = 0; i < this->length; i++)
        {
            this->str[i] = str.str[index + i];
        }

        this->str[this->length] = '\0';
    }
}

// 将指定的字符 str 重复 length 次赋值给该字符串。
Mystring::Mystring(size_type length, const char str)
{
    size_t i = 0;
    this->length = length;
    this->str = new char[this->length + 1];
    for (i = 0; i < this->length; i++)
    {
        this->str[i] = str;
    }
    this->str[i] = '\0';
}

/*-----------------------------工具---------------------------------*/
// 计算字符串类的长度
size_type Mystring::mystrlen(const char *str)
{
    size_type len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

/*----------------------------成员函数-------------------------------*/
// 返回以 NULL 字符('\0') 结尾的 C 风格字符串指针
const char *Mystring::c_str()
{
    return str;
}

/*
    size_type copy(char* str, size_type num, size_type index)

    str：指向将存储复制字符的目标字符数组的指针。
    num：要从字符串复制的最大字符数。它表示目标字符数组的长度。
    index：字符串中应从复制过程开始的起始位置。
    返回值：
        返回从字符串复制的实际字符数。
*/
size_type Mystring::copy(char *str, size_type num, size_type index)
{
    // 计算可用于复制的字符数
    size_type ablecp_num = length - index;
    size_type chars_to_cp = (num < ablecp_num ? num : ablecp_num);

    for (size_t i = 0; i < chars_to_cp; i++)
    {
        str[i] = this->str[index + i];
    }
    return chars_to_cp;
}

// 以追加方式添加字符串到字符串对象中
Mystring &Mystring::append(const char *str)
{
    // 计算要追加的字符串长度
    size_type strLength = mystrlen(str);

    // 分配新的内存空间
    char *newStr = new char[length + strLength + 1];

    // 复制原始字符串到新的空间中
    for (size_t i = 0; i < length; i++)
    {
        newStr[i] = this->str[i];
    }

    // 追加要添加的字符串到新的空间中
    for (size_t i = 0; i < strLength; i++)
    {
        newStr[length + i] = str[i];
    }
    newStr[length + strLength] = '\0';

    // 释放原有的字符串内存空间并更新指针和长度
    delete[] this->str;
    this->str = newStr;
    this->length += strLength;

    return *this;
}

// 插入 从 index 位置插入 str 字符串
Mystring &Mystring::insert(size_type index, const char *str)
{
    if (index > length)
    {
        return *this;
    }

    // 计算要插入的字符串的长度
    size_type strLength = mystrlen(str);

    // 分配新的空间
    char *newStr = new char[this->length + strLength + 1];

    size_t i = 0;
    // 复制原始字符串到新的空间中
    for (i = 0; i < index; i++)
    {
        newStr[i] = this->str[i];
    }
    // 插入字符串到新的空间中
    for (size_t j = 0; j < strLength; i++, j++)
    {
        newStr[i] = str[j];
    }
    // 复制原始字符串中的剩余字符
    for (; i < length + strLength; i++)
    {
        newStr[i] = this->str[i - strLength];
    }

    // 释放原有的字符串内存空间并更新指针和长度
    delete[] this->str;
    this->str = newStr;
    this->length += strLength;

    return *this;
}

// 删除从 index 索引开始的 num 个字符，返回 *this
Mystring &Mystring::erase(size_type index, size_type num)
{
    // 检查是否超过源字符串的长度
    if (index >= this->length)
    {
        // 如果索引值大于等于字符串长度，则没有字符需要删除，直接返回原始字符对象
        return *this;
    }
    // 要移动的字符数目限制在 length 中
    size_type chars_to_del = (num == npos) ? length - index : (num < length - index ? num : length - index);
    if (chars_to_del > 0)
    {
        for (size_t i = index; i < length - chars_to_del; i++)
        {
            str[i] = str[i + chars_to_del];
        }
    }
    // 更新 字符串对象 的字符串长度
    length -= chars_to_del;
    str[length] = '\0';

    return *this;
}

// 在从指定索引位置开始的子字符串中搜索指定的字符串，并返回第一次出现的位置索引。
size_type Mystring::find(const char *str, size_type index)
{
    // 计算要搜索的字符串的长度
    size_type searchLength = mystrlen(str);

    if (searchLength == 0)
    {
        return index;
    }

    if (index >= length || searchLength > length - index)
    {
        return npos;
    }

    for (size_type i = index; i <= length - searchLength; i++)
    {
        bool found = true;
        for (size_type j = 0; j < searchLength; j++)
        {
            if (str[j] != this->str[i + j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return i;
        }
    }

    return npos;
}

// 在从指定索引位置开始的子字符串中搜索另一个字符串对象，并返回第一次出现的位置索引。
size_type Mystring::find(const Mystring &str, size_type index)
{
    size_type searchLength = str.length;

    if (searchLength == 0)
    {
        return index;
    }

    if (index >= length || searchLength > length - index)
    {
        return npos;
    }

    for (size_type i = index; i <= length - searchLength; i++)
    {
        bool found = true;
        for (size_type j = 0; j < searchLength; j++)
        {
            if (str.str[j] != this->str[i + j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            return i;
        }
    }

    return npos;
}

// 返回最后一个与str中的某个字符匹配的字符，从index开始查找。如果没找到就返回string::npos
size_type Mystring::rfind(const char *str, size_type index)
{
    // 计算要搜索的字符串的长度
    int searchLength = mystrlen(str);

    if (searchLength == 0)
    {
        return index;
    }
    // 检查 index 是否超过字符串对象的长度 和
    if (index >= length || searchLength > length - index)
    {
        return npos;
    }

    size_type start = (index < length - searchLength) ? index : length - searchLength;

    for (size_t i = start; i > 0; i--)
    {
        bool find = true;
        for (size_t j = 0; j < searchLength; j++)
        {
            if (str[j] != this->str[i + j])
            {
                find = false;
                break;
            }
        }
        if (find)
        {
            return i;
        }
    }
    return npos;
}

// 在从指定索引位置的子字符串中从后往前搜索另一个字符串对象，并返回第一次出现的位置索引。
size_type Mystring::rfind(const Mystring &str, size_type index)
{
    // 计算要搜索的字符串的长度
    int searchLength = str.length;

    if (searchLength == 0)
    {
        return index;
    }
    // 检查 index 是否超过字符串对象的长度 和
    if (index >= this->length || searchLength > this->length - index)
    {
        return npos;
    }

    size_type start = (index < this->length - searchLength) ? index : this->length - searchLength;

    for (size_t i = start; i > 0; i--)
    {
        bool find = true;
        for (size_t j = 0; j < searchLength; j++)
        {
            if (str.str[j] != this->str[i + j])
            {
                find = false;
                break;
            }
        }
        if (find)
        {
            return i;
        }
    }
    return npos;
}

// 用str中的num个字符（从index开始）替换本字符串中的字符
Mystring &Mystring::replace(size_type index, size_type num, const char *str)
{
    size_type strLength = mystrlen(str);

    if (num > 0 && index < length)
    {
        // 计算要替换的字符数
        size_type replaceLength = (num <= length - index) ? num : length - index;

        // 计算修改后字符串的结果长度
        size_type newLength = length + strLength - replaceLength;

        // 为修改后的字符串分配新的内存
        char *newStr = new char[newLength + 1];

        // 复制开始索引之前的字符
        for (size_type i = 0; i < index; i++)
        {
            newStr[i] = this->str[i];
        }

        // 从替换字符串中复制字符
        for (size_type i = 0; i < strLength; i++)
        {
            newStr[index + i] = str[i];
        }

        // 复制替换部分后的剩余字符
        for (size_type i = index + strLength, j = index + replaceLength; i < newLength; i++, j++)
        {
            newStr[i] = this->str[j];
        }

        // 以空结束新字符串
        newStr[newLength] = '\0';

        // 释放原始字符串的内存并更新指针和长度
        delete[] this->str;
        this->str = newStr;
        this->length = newLength;
    }

    return *this;
}

// 用str对象中的num个字符（从index开始）替换本字符串中的字符
Mystring &Mystring::replace(size_type index, size_type num, const Mystring &str)
{
    size_type strLength = mystrlen(str.str);

    if (num > 0 && index < length)
    {
        // 计算要替换的字符数
        size_type replaceLength = (num <= length - index) ? num : length - index;

        // 计算修改后字符串的结果长度
        size_type newLength = length + strLength - replaceLength;

        // 为修改后的字符串分配新的内存
        char *newStr = new char[newLength + 1];

        // 复制开始索引之前的字符
        for (size_type i = 0; i < index; i++)
        {
            newStr[i] = this->str[i];
        }

        // 从替换字符串中复制字符
        for (size_type i = 0; i < strLength; i++)
        {
            newStr[index + i] = str.str[i];
        }

        // 复制替换部分后的剩余字符
        for (size_type i = index + strLength, j = index + replaceLength; i < newLength; i++, j++)
        {
            newStr[i] = this->str[j];
        }

        // 以空结束新字符串
        newStr[newLength] = '\0';

        // 释放原始字符串的内存并更新指针和长度
        delete[] this->str;
        this->str = newStr;
        this->length = newLength;
    }

    return *this;
}

// 返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，将是默认值 string::npos。
Mystring Mystring::substr(size_type index, size_type num)
{
    if (index >= length)
    {
        //  如果索引超出范围，则返回空字符串
        return "";
    }

    size_type subLength;
    // 如果未指定，则设置 num 的默认值或设置为 npos
    if (num == npos || index + num > length)
    {
        subLength = length - index;
    }
    else
    {
        subLength = num;
    }

    // 创建新字符串以存储子字符串
    char *subStr = new char[subLength + 1];

    for (size_type i = 0; i < subLength; i++)
    {
        subStr[i] = this->str[index + i];
    }

    subStr[subLength] = '\0';

    Mystring result(subStr);
    delete[] subStr;

    return result;
}

/*--------------------------重载运算符-------------------------------*/
// 重载 < 关系运算符
bool operator<(const Mystring ch1, const Mystring ch2)
{
    size_t i = 0;
    while (ch1.str[i] != '\0' && ch2.str[i] != '\0')
    {
        if (ch1.str[i] < ch2.str[i])
        {
            return true;
        }
        else if (ch1.str[i] > ch2.str[i])
        {
            return false;
        }
        i++;
    }

    // 如果前面的字符都相等，则根据长度来判断大小
    if (ch1.length < ch2.length)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 重载 > 关系运算符
bool operator>(const Mystring ch1, const Mystring ch2)
{
    size_t i = 0;
    while (ch1.str[i] != '\0' && ch2.str[i] != '\0')
    {
        if (ch1.str[i] > ch2.str[i])
        {
            return true;
        }
        else if (ch1.str[i] < ch2.str[i])
        {
            return false;
        }
        i++;
    }

    // 如果前面的字符都相等，则根据长度来判断大小
    if (ch1.length > ch2.length)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 重载 == 关系运算符
bool operator==(const Mystring ch1, const Mystring ch2)
{
    if (ch1.length != ch2.length)
    {
        return false;
    }

    for (size_t i = 0; i < ch1.length; i++)
    {
        if (ch1.str[i] != ch2.str[i])
        {
            return false;
        }
    }

    return true;
}

// 重载 += 赋值运算符
Mystring &Mystring::operator+=(const Mystring &ch1)
{
    size_type ch_Length = ch1.length;

    // 为合并后的字符串分配内存
    char *combined = new char[length + ch_Length + 1];

    // 将第一个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < length; i++)
    {
        combined[i] = str[i];
    }

    // 将第二个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < ch_Length; i++)
    {
        combined[length + i] = ch1.str[i];
    }

    // 以空结束组合字符串
    combined[length + ch_Length] = '\0';

    // 释放原始字符串的内存并更新指针和长度
    delete[] str;
    str = combined;
    length += ch_Length;

    return *this;
}

// 重载 += 赋值运算符
Mystring &Mystring::operator+=(const char *str)
{
    size_type strLength = mystrlen(str);

    // 为合并后的字符串分配内存
    char *combined = new char[length + strLength + 1];

    // 将第一个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < length; i++)
    {
        combined[i] = str[i];
    }

    // 将第二个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < strLength; i++)
    {
        combined[length + i] = str[i];
    }

    // 以空结束组合字符串
    combined[length + strLength] = '\0';

    // 释放原始字符串的内存并更新指针和长度
    delete[] this->str;
    this->str = combined;
    length += strLength;

    return *this;
}

// 重载 + 双目运算符 实现拼接
Mystring operator+(const Mystring &ch1, const Mystring &ch2)
{
    size_type len1 = ch1.length;
    size_type len2 = ch2.length;

    // 为合并后的字符串分配内存
    char *combined = new char[len1 + len2 + 1];

    // 将第一个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < len1; i++)
    {
        combined[i] = ch1.str[i];
    }

    // 将第二个字符串中的字符复制到组合字符串中
    for (size_type i = 0; i < len2; i++)
    {
        combined[len1 + i] = ch2.str[i];
    }

    // 以空结束组合字符串
    combined[len1 + len2] = '\0';

    // 创建一个新的 Mystring 对象来包装组合字符串
    Mystring result(combined);

    // 释放内存
    delete []combined;

    return result;
}

// 重载 [] 运算符
char& Mystring::operator[](size_type index)
{
    // 检查 index 是否超出范围
    if (index >= length)
    {
        throw out_of_range("Index out of range");
    }

    return str[index];
}


// 重载 输出流运算符
ostream &operator<<(ostream &os, const Mystring &mystr)
{
    os << mystr.str;
    return os;
}
