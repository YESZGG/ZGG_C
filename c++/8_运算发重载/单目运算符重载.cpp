#include <iostream>

using namespace std;

class MyClass {
private:
    int value;

public:
    MyClass(int val) : value(val) {}

    MyClass& operator++() {       // 前置形式 ++
        value += 1;
        return *this;
    }

    MyClass operator++(int) {     // 后置形式 ++
        MyClass temp(value);      // 保存当前值
        value += 1;               // 增加值
        return temp;              // 返回先前值
    }

    MyClass& operator--() {       // 前置形式 --
        value -= 1;
        return *this;
    }

    MyClass operator--(int) {     // 后置形式 --
        MyClass temp(value);      // 保存当前值
        value -= 1;               // 减少值
        return temp;              // 返回先前值
    }

    int getValue() const {
        return value;
    }
};

int main() {
    MyClass obj(5);

    ++obj;  // 调用前置递增操作符 先++，后使用
    cout << "前置递增: " << obj.getValue() << endl;

    obj++;  // 调用后置递增操作符 先使用，后++
    cout << "后置递增: " << obj.getValue() << endl;

    --obj;  // 调用前置递减操作符 先--，后使用
    cout << "前置递减: " << obj.getValue() << endl;

    obj--;  // 调用后置递减操作符 先使用，后--
    cout << "后置递减: " << obj.getValue() << endl;

    return 0;
}
