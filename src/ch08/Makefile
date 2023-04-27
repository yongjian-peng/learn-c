.PHONY: clean
	#note: "PHONY" must be up case
CC = gcc
RM = rm
EXE = all

OBJS = 8-1.out

CFLAGS = "-std=c99"
$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.out: %.o
	$(CC) -o $@ $<

clean:
	$(RM) *.o *.out