#include <stdio.h>

#if 1
int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个函数指针
    int (*functionPtr)(int, int);

    // 将函数指针指向具体的函数
    functionPtr = add;

    // 使用函数指针调用函数
    int result = functionPtr(3, 4);

    printf("Result: %d\n", result);

    return 0;
}
#endif


#if 0
typedef int (*OperationFuncPtr)(int, int);

int add(int a, int b) {
    return a + b;
}

int main() {
    // 声明一个别名为 OperationFuncPtr 的函数指针
    OperationFuncPtr operation;

    // 将函数指针指向具体的函数
    operation = add;

    // 使用函数指针调用函数
    int result = operation(3, 4);

    printf("Result: %d\n", result);

    return 0;
}

#endif