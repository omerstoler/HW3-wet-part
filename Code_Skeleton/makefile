# This is a makefile for AIRPORT project
# definitions
CC = g++
CFLAGS = -g -Wall -std=c++11 
LDFLAGS = -pthread -lpthread
CCLINK = $(CC)
LIBS =
OBJS = Board.o Cell.o Job.o main.o PCQueue.o Semaphore.o SerialGame.o utils.o
RM = rm -f
# Creating the exe.s
GameOfLife:  $(OBJS)
	$(CC) -o GameOfLife $(OBJS) $(LDFLAGS)
# Creating Object files

# Compile main.c to create main.o
Board.o: Board.cpp Board.hpp Cell.hpp Headers.hpp
Board.o: Board.hpp Cell.hpp Headers.hpp
Cell.o: Cell.cpp Cell.hpp Headers.hpp
Cell.o: Cell.hpp Headers.hpp
Job.o: Job.cpp Job.hpp Board.hpp Cell.hpp Headers.hpp
Job.o: Job.hpp Board.hpp Cell.hpp Headers.hpp
main.o: main.cpp SerialGame.hpp utils.hpp Headers.hpp PCQueue.hpp \
 Semaphore.hpp Job.hpp Board.hpp Cell.hpp
PCQueue.o: PCQueue.cpp
PCQueue.o: PCQueue.hpp Headers.hpp Semaphore.hpp
Semaphore.o: Semaphore.cpp Semaphore.hpp Headers.hpp
Semaphore.o: Semaphore.hpp Headers.hpp
SerialGame.o: SerialGame.cpp SerialGame.hpp utils.hpp Headers.hpp \
 PCQueue.hpp Semaphore.hpp Job.hpp Board.hpp Cell.hpp
SerialGame.o: SerialGame.hpp utils.hpp Headers.hpp PCQueue.hpp \
 Semaphore.hpp Job.hpp Board.hpp Cell.hpp
utils.o: utils.cpp utils.hpp Headers.hpp
utils.o: utils.hpp Headers.hpp

