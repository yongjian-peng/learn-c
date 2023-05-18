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
	$(CC) $(CFLAGS) -g -c $< -o $@
%.o: %.cpp
	$(CC) $(CFLAGS) -g -c $< -o $@
%.out: %.o
	$(CC) -g -o $@ $<

clean:
	$(RM) *.o *.out