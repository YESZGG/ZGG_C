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
	key_t key = ftok(".",10);// 确保了两个进程可以获取到同一个共享内存区域的标识。
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
	semctl(semid,0,SETVAL,1);//设置空间的起始值为1 //有空间
	semctl(semid,1,SETVAL,0);//设置数据的起始值为0 //无数据


	//空间结构体具体的含义是由结构体参数决定不是space
	struct sembuf space;
	space.sem_num = 0;//空间
	space.sem_op = -1;//P操作
	space.sem_flg = 0;//普通属性

	//数据结构体
	struct sembuf data;
	data.sem_num = 1;//数据
	data.sem_op = 1;//V操作
	data.sem_flg = 0;//普通属性

	//此时映射出来的shm_p 就是两个进程的共享内存
	while(1)
	{
		//空间：1  数据：0
		//开车进去之前，空间 -1 --P操作
		semop(semid, &space, 1);//请问空间能不能P操作？

		//能   -> 有车位  -> 函数返回
		//不能 -> 没车位  -> 函数阻塞


		//开车进去
		//从键盘上获取数据，存储到共享内存shm_p
		scanf("%s",shm_p);

		//开车进去之后，数据+1 --V操作
		semop(semid, &data, 1); //数据自动+1

		//退出条件，这里要注意 应该使用strncmp 指定字节数
		if(strncmp(shm_p,"exit",4) == 0)
			break;
	}

	//4、当不再使用时，解除映射关系
	shmdt(shm_p);
	//5、当没有进程再需要使用这块共享内存时，删除它
	shmctl(shmid,  IPC_RMID, NULL);

	semctl(semid,0,IPC_RMID);

	return 0;
}
