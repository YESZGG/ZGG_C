TAR = bin/main	#目标文件
INC = -I ./include -I ./libjpeg
LIB = -L ./libjpeg -ljpeg -L ./lib -lfont -lm

#SRC = main/project.c src/fun1.c src/fun2.c
SRC = $(wildcard src/*.c)
MAIN = main/main.c

#CC = gcc
CC = arm-linux-gcc  #交叉编译工具

#.PHONY:$(TAR)  #无论是否更新 make每次都能执行 

$(TAR):$(MAIN) $(SRC) 
#	gcc $^ -o $@ $(INC)
	$(CC) $^ -o $@ $(INC) $(LIB)

run:
	./$(TAR)

.PHONY:clean

clean:
	$(RM) $(TAR)
