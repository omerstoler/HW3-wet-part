# This is a makefile for AIRPORT project
# definitions
CC = g++
CFLAGS = -o3 -g -Wall -std=c++11 
LDFLAGS = -pthread -lpthread
CCLINK = $(CC)
LIBS =
OBJS = Board.o Cell.o Game.o Job.o main.o PCQueue.o Semaphore.o utils.o 
RM = rm -f
# Creating the exe.s
GameOfLife:  $(OBJS)
	$(CC) -o GameOfLife $(OBJS) $(LDFLAGS)
# Creating Object files

# Compile main.c to create main.o
Board.o: Board.cpp Board.hpp Cell.hpp Headers.hpp utils.hpp
Cell.o: Cell.cpp Cell.hpp Headers.hpp
Game.o: Game.cpp Game.hpp PCQueue.hpp Headers.hpp Semaphore.hpp Job.hpp \
 Board.hpp Cell.hpp utils.hpp JobThread.hpp Thread.hpp
Job.o: Job.cpp Job.hpp Board.hpp Cell.hpp Headers.hpp utils.hpp
#JobThread.o: JobThread.hpp Thread.hpp Headers.hpp Game.hpp PCQueue.hpp \
 #Semaphore.hpp Job.hpp Board.hpp Cell.hpp utils.hpp
main.o: main.cpp Game.hpp PCQueue.hpp Headers.hpp Semaphore.hpp Job.hpp \
 Board.hpp Cell.hpp utils.hpp
PCQueue.o: PCQueue.cpp PCQueue.hpp Headers.hpp Semaphore.hpp
Semaphore.o: Semaphore.cpp Semaphore.hpp Headers.hpp
#Thread.o: Thread.hpp Headers.hpp
utils.o: utils.cpp utils.hpp Headers.hpp

