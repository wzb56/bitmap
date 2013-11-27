EXEC = test 
OBJS = test.o bitmap.o 
SRC  = test.c bitmap.c bitmap.h  

CC = gcc  
CFLAGS += -O2 -Wall -g 
LDFLAGS +=   

all:$(EXEC)  

$(EXEC):$(OBJS)  
	$(CC) $(LDFLAGS) -o $@ $(OBJS)  

bitmap.o: bitmap.c bitmap.h
test.o: test.c bitmap.h

%.o:%.c  
	$(CC) $(CFLAGS) -c $< -o $@  

clean:  
	@rm -vf $(EXEC) *.o *~  
