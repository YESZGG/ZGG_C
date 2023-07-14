#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_random_number(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main()
{
    int min_value = 1;   // 最小值
    int max_value = 100; // 最大值

    // 设置随机数种子
    srand(time(NULL));

    // 生成随机数
    int random_number = generate_random_number(min_value, max_value);

    printf("Random number: %d\n", random_number);

    return 0;
}
