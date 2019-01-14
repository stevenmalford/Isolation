#
# File: Makefile
# Author: Joshua T. Guerin
# Description: Makefile for the isola tournament class.
#

# Compiler
CC=g++
# Compiler flags
CFLAGS=-c -Wall -std=c++11

# Binary name
TARGET=tournament


all: $(TARGET)

# Add additional agents to both lines here
$(TARGET): main.o isola.o random_agent.o ordered_agent.o alford_steven.o
	$(CC) objects/main.o objects/isola.o objects/random_agent.o objects/ordered_agent.o objects/alford_steven.o -o $(TARGET)

# Main's dependencies include agent files (included in the main)
main.o: main.cpp isola.h agents/random_agent.h agents/ordered_agent.h agents/alford_steven.h
	$(CC) $(CFLAGS) main.cpp -o objects/main.o

random_agent.o: agents/random_agent.cpp agents/random_agent.h
	$(CC) $(CFLAGS) agents/random_agent.cpp -o objects/random_agent.o

ordered_agent.o: agents/ordered_agent.cpp agents/ordered_agent.h
	$(CC) $(CFLAGS) agents/ordered_agent.cpp -o objects/ordered_agent.o
	
alford_steven.o: agents/alford_steven.cpp agents/alford_steven.h
	$(CC) $(CFLAGS) agents/alford_steven.cpp -o objects/alford_steven.o

#Add compilation instructions for any additional agents here

isola.o: isola.cpp isola.h
	$(CC) $(CFLAGS)	isola.cpp -o objects/isola.o

clean:
	rm agents/*~ objects/*.o *~ $(TARGET)
