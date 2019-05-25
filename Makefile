SRCS = $(wildcard *.c *.cpp ../lib/*.c ../lib/*.cpp src/*.c src/*.cpp testcase/*.c testcase/*.cpp)
OBJS = $(SRCS:.c = .o)
CC = g++
INCLUDES = -Iinclude \
			-I.
LIBS = -lcurl
CCFLAGS = -g -Wall -O0
OUTPUT = nacos-cli.out

all : $(OUTPUT)

$(OUTPUT) : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)
%.o : %.c
	$(CC) -c $< $(CCFLAGS)
%.o : %.cpp
	$(CC) -c $< $(CCFLAGS)
testcase : all
SRCS = $(SRCS:testcase/*.c)

clean:
	rm -rf *.out *.o

.PHONY:clean