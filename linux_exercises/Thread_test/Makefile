src=$(wildcard *.c)                     # 
target=$(patsubst %.c, %, $(src))       # 

com_opt=-g -Wall -lpthread

ALL:$(target)

%:%.c
	gcc $< -o $@ ${com_opt}

clean:
	rm -rf $(target)

.PHONY:clean ALL

