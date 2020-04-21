CC=g++
CFLAGS=-Wall -g -std=c++11
LFLAGS=-lm
TARGET1=greedy
TARGET2=refine
TARGET3=prune
FILE=candy.txt

greedy:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	$(CC) $(CFLAGS) greedy.cpp -o $(TARGET1)
	time ./$(TARGET1)

refine:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	$(CC) $(CFLAGS) refine.cpp -o $(TARGET2)
	time ./$(TARGET2)

prune:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	$(CC) $(CFLAGS) prune.cpp -o $(TARGET3)
	time ./$(TARGET3)

run:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
	$(CC) $(CFLAGS) greedy.cpp -o $(TARGET1)
	$(CC) $(CFLAGS) refine.cpp -o $(TARGET2)
	$(CC) $(CFLAGS) prune.cpp -o $(TARGET3)
	time ./$(TARGET1)
	time ./$(TARGET2)
	time ./$(TARGET3)

clean:
	rm -f $(TARGET1) $(TARGET2) $(TARGET3)
