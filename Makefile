OBJS = $(wildcard *.c)
RMFILE = $(OBJS:%.c=%.o)
FLAGS = -lpthread -lsqlite3 -o
GCC=gcc 
main:$(OBJS)
	$(GCC) -g $(OBJS)  $(FLAGS) $@ 

.PHONY:clean

clean:
	$(RM)  main a.out $(RMFILE)
