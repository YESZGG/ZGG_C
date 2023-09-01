#include <iostream>

using namespace std;

/*
In function ‘int main()’:
error: call of overloaded ‘test()’ is ambiguous //定义模糊
     test(); //产生歧义
          ^
note: candidate: void test()  //候选项 能够匹配
 void test()
      ^
note: candidate: void test(int) //候选项 能够匹配
 void test(int x = 10)

*/
void test()
{
    cout << "void test()" << endl;
}

// namespace space
// {
//     void test()
//     {
//         cout << "void test()" << endl;
//     }
// }

void test(int x = 10)
{
    cout << "void test(int x=10)" << endl;
}

int main()
{

    // test(11);

    test(); //产生歧义

    return 0;
}