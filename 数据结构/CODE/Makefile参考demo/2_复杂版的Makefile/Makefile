TAR = bin/target	#目标文件
INC = -I ./include

#SRC = main/project.c src/fun1.c src/fun2.c
SRC = $(wildcard src/*.c)
MAIN = main/project.c

CC = gcc
#CC = arm-linux-gcc  #交叉编译工具

#.PHONY:$(TAR)  #无论是否更新 make每次都能执行 

$(TAR):$(MAIN) $(SRC) 
#	gcc $^ -o $@ $(INC)
	$(CC) $^ -o $@ $(INC)

run:
	./$(TAR)

.PHONY:clean

clean:
	$(RM) $(TAR)
