#include<stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

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

	//4、获取信号量的key值
	key_t key1 = ftok(".",20);
	//5、根据key值申请信号量ID号
	int semid = semget(key1,2,IPC_CREAT|0666);
	//6、初始化信号量起始值
	semctl(semid,0,SETVAL,1);//设置空间的起始值为1
	semctl(semid,1,SETVAL,0);//设置数据的起始值为0

	//空间结构体
	struct sembuf space;
	space.sem_num = 0;
	space.sem_op = 1; //V操作
	space.sem_flg = 0;

	//数据结构体
	struct sembuf data;
	data.sem_num = 1;
	data.sem_op = -1;//P操作
	data.sem_flg = 0;

	//此时映射出来的shm_p 就是两个进程的共享内存
	while(1)
	{
		//空间：0  数据：1
		//把车开出来之前，请问数据能不能-1?
		semop(semid, &data, 1);

		//能  -> 里面有车  -> 函数返回
		//不能 -> 里面没车 -> 函数阻塞

		//从车库里面把车开出来
		//从共享内存中读取数据
		printf("recv:%s\n",shm_p);
		//sleep(1);

		//把车开出来之后，空间+1
		semop(semid, &space, 1);

		//空间：1  数据：0

		//退出条件，这里要注意 应该使用strncmp 指定字节数
		if(strncmp(shm_p,"exit",4) == 0)
			break;
	}

	return 0;
}
