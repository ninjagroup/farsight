OBJS = $(wildcard *.c)
RMFILE = $(OBJS:%.c=%.o)
FLAGS = -lpthread -o
GCC=gcc 
main:$(OBJS)
	$(GCC) $(OBJS)  $(FLAGS) $@ 

.PHONY:clean

clean:
	$(RM) main a.out $(RMFILE)
