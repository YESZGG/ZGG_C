#include<stdio.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#define SEM_NAME    "/semname1"

int main()
{
    //1、获取key值
    key_t key = ftok(".",10);
    //2、根据key值 获取共享内存的ID号
    int shmid = shmget(key,1024,IPC_CREAT|0666);
    //3、根据ID号 将共享内存映射至本进程虚拟内存空间的某个区域
    char*shm_p = shmat(shmid,NULL,0);
    if(shm_p == (void*)-1)
    {
        perror("shmat error");
        return -1;
    }
    
    //4、创建并打开一个有名信号量
    sem_t *nameSem = sem_open(SEM_NAME,O_CREAT,0777,0); 
    if(nameSem == SEM_FAILED )
    {
        printf("sem_open error\n");
        return -1;
    }
    
    //此时映射出来的shm_p 就是两个进程的共享内存
    while(1)
    {   
        //从键盘上获取数据，存储到共享内存shm_p
        scanf("%s",shm_p);
    
        //有名信号量的V操作  数据 +1
        sem_post(nameSem);
        
        //退出条件，这里要注意 应该使用strncmp 指定字节数
        if(strncmp(shm_p,"exit",4) == 0)
            break;
    }
    //4、当不再使用时，解除映射关系
    shmdt(shm_p);
    //5、当没有进程再需要使用这块共享内存时，删除它
    shmctl(shmid,  IPC_RMID, NULL);
    
    //6、关闭有名信号量。
    sem_close(nameSem);
    //7、删除有名信号量
    sem_unlink(SEM_NAME);
    
    return 0;
}