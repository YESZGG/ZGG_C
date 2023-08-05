#include "test_pool.h"

void *task1(void *arg)
{
	printf("\t江城子 . 程序员之歌\n\n");
	printf("   十年生死两茫茫，写程序，到天亮。\n");
	printf("\t千行代码，Bug何处藏。\n");
}

void *task2(void *arg)
{
	printf("   纵使上线又怎样，朝令改，夕断肠。\n\n");
	printf("   领导每天新想法，天天改，日日忙。\n");
}

void *task3(void *arg)
{
	printf("\t相顾无言，惟有泪千行。\n");
	printf("   每晚灯火阑珊处，夜难寐，加班狂。\n");
}

int main(int argc, char **argv)
{

	thread_pool *pool = malloc(sizeof(thread_pool));

	// 初始化线程池
	init_pool(pool, 2); // 在初始化的时候创建了num条线程

	// 添加了3个任务
	add_task(pool, task1, NULL);
	add_task(pool, task2, NULL);
	add_task(pool, task3, NULL);

	// 按照实际情况来增加线程或者删除线程
	add_thread(pool, 1);
	// remove_thread()

	// 销毁线程池
	destroy_pool(pool);

	return 0;
}