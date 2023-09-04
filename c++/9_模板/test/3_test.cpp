/* 编写一个排序模板，可以对不同的数据类型，进行排序。 */
#include <iostream>

using namespace std;

template <typename T>

// 插入排序
void sortArray(T arr[], int size)
{
    int i, j;
    T temp;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            temp = arr[i];
            for (j = i - 1; j >= 0 && arr[j] > temp; --j)
            {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = temp;
        }
    }
}

// 冒泡排序
// void sortArray(T arr[], int size)
// {
//     for (int i = 0; i < size - 1; ++i)
//     {
//         for (int j = 0; j < size - i - 1; ++j)
//         {
//             if (arr[j] > arr[j + 1])
//             {
//                 T temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
// }

int main()
{
    int intArr[] = {5, 2, 8, 1, 3};
    int intSize = sizeof(intArr) / sizeof(intArr[0]);
    sortArray<int>(intArr, intSize);

    for (int i = 0; i < intSize; ++i)
    {
        cout << intArr[i] << " ";
    }
    cout << endl;

    char charArr[] = {'d', 'e', 'a', 'b', 'c'};
    int charSize = sizeof(charArr) / sizeof(charArr[0]);
    sortArray<char>(charArr, charSize);

    for (int i = 0; i < charSize; ++i)
    {
        cout << charArr[i] << " ";
    }
    cout << endl;

    return 0;
}
