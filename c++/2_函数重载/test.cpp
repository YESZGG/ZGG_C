#include <iostream>
#include <cstring>
using namespace std;

char* get_mem(int size)
{
    char* ptr = new char[size];
    return ptr;
}

char* req_mem(int size)
{
    char* ptr = new char[size];
    return ptr;
}

int main()
{
    char* ptr = get_mem(100);
    const char* p = "hello world";
    memcpy(ptr, p, strlen(p));
    cout << ptr << endl;

    char* mptr = req_mem(100);
    memcpy(mptr, p, strlen(p));
    cout << mptr << endl;

    delete[] ptr; // 释放动态分配的内存
    delete[] mptr; // 释放动态分配的内存

    return 0;
}
