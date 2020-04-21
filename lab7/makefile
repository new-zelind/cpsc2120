#config variables
CC=g++
CFLAGS=-Wall -g -std=c++11
LFLAGS=-lm
TARGET=exe
INPUT=points.txt

CPP_SRCS :=\
	$(wildcard *.cpp)\
	$(wildcard src/*.cpp)\
	$(wildcard src/**/*.cpp)

HDRS :=\
	$(wildcard *.h)\
	$(wildcard src/*.h)\
	$(wildcard src/**/*.h)

OBJS := $(patsubst %.cpp, bin/%.o, $(wildcard *.cpp))
OBJS += $(filter %.o, $(patsubst src/%.cpp, bin/%.o, $(CPP_SRCS)))

all: build
	@echo "COMPLETE"

build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LFLAGS)

bin/%.o: %.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bin/%.o: src/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf bin
	
run: build
	  @echo "COMPILATION COMPLETE"
	  @echo "RUNNING ./$(TARGET)"
	./$(TARGET)

which:
	@echo "FOUND SOURCES: $(CPP_SRCS)"
	@echo "FOUND HEADERS: $(HDRS)"
	@echo "TARGET OBJS: $(OBJS)"
