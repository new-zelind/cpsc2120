CC=g++
CFLAGS=-Wall -g -std=c++11
LFLAGS=-lm
TARGET1=input
TARGET2=exe
FILE=input.txt

run:
	  rm -f $(TARGET1) $(TARGET2) input.txt
	  $(CC) $(CFLAGS) input.cpp -o $(TARGET1)
	  ./$(TARGET1) $(NUM)
	  $(CC) $(CFLAGS) main.cpp lab6.cpp lab6.hpp $(TARGET2)
	  ./$(TARGET2)
