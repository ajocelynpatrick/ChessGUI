CC = g++
CFLAGS = -std=c++11 -g

OBJS = main.o Board.o

chess: $(OBJS)
	$(CC) $(CFLAGS) -o chess $(OBJS)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
Board.o: Board.hpp Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp
.PHONY: clean
clean:
	rm -rf $(OBJS) chess