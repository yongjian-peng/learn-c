#CC = arm-linux-gcc
#DD = main.o f1.o f2.o f3.o
#DD = $(wildcard *.o)
SRCS = $(wildcard *.c)
DD = $(patsubst %.c,%.o,$(SRCS))
all: $(DD)
	$(CC) -o all $(DD)
	echo $(DD)
%.o: %.c
	$(CC) -o $@ -c $<
clean:
	$(RM) *.o all