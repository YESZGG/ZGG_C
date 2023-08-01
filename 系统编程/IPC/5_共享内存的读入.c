#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/* 一直读的话会发生数据践踏 */
int main()
{
    // 1. 获取共享内存区
    key_t key = ftok(".", 100);// 确保了两个进程可以获取到同一个共享内存区域的标识。

    // 2、根据key值， 得到物理共享内存的ID号，如果该物理内存不存在，则创建  ---open
    int shm_id = shmget(key, 1024, 0666);
    if (shm_id == -1)
    {
        perror("shmget");
        exit(1);
    }

    printf("共享内存 key=%#x    shm_id:%d.\n", key, shm_id);

    // 3、将物理内存映射到用户的虚拟内存空间中的某一块区域
    char *shm_ptr = (char *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (char *)(-1))
    {
        perror("shmat");
        exit(1);
    }

    // 4. 读取共享内存区的数据
    printf("Data read from shared memory: %s\n", shm_ptr);

    // 5. 分离共享内存区(并不是删除，相当于解除映射)
    if (shmdt(shm_ptr) == -1)
    {
        perror("shmdt");
        exit(1);
    }

    // 6. 删除共享内存区
    if (shmctl(shm_id, IPC_RMID, 0) == -1)
    {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
