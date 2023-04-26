.PHONY: clean
	#note: "PHONY" must be up case
CC = gcc
RM = rm
EXE = all

OBJS = 7-1.o

CFLAGS = "-std=c99"
$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

#7-1.o: 7-1.c
#	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%: %.o
	$(CC) -o $@ $<

clean:
	$(RM) *.o 7-1 7-2 7-3