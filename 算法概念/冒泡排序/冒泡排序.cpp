#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int comp_count = 0; // 数据比较次数
int swap_count = 0; // 数据交换次数

void show(int data[], int len)
{
    int count = 0;
    for (int i = 0; i < len; i++)
    {
        cout << data[i] << "\t";
        count++;
        if (count == 10)
        {
            cout << endl;
            count = 0;
        }
    }
    cout << endl;
}

// 交换
void swap(int &a, int &b)
{
    swap_count++;
    int temp = a;
    a = b;
    b = temp;
}

// 冒泡排序
void BubbleSort(int A[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = false;              // 表示本趟冒泡是否发生交换的标志
        for (int j = n - 1; j > i; j--) // 一趟冒泡过程
        {
            comp_count++;
            if (A[j - 1] > A[j]) // 若为逆序
            {
                swap(A[j - 1], A[j]); // 交换
                flag = true;
            }
        }
        if (flag == false)
        {
            return; // 本趟遍历后没有发生交换，说明表已经有序
        }
    }
}

int main()
{
    srand(time(NULL));

    int data[100];
    for (int i = 0; i < 100; i++)
    {
        data[i] = rand() % 1000 + 1;
    }

    cout << "随机序列：" << endl;
    show(data, 100);

    BubbleSort(data, 100);

    cout << "排序后序列：" << endl;
    show(data, 100);

    cout << "总共比较次数：" << comp_count << endl;
    cout << "总共交换次数：" << swap_count << endl;
    cout << "交换元素的次数：" << swap_count * 3 << endl;
    return 0;
}
