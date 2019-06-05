SRCS = $(wildcard *.c *.cpp ../lib/*.c ../lib/*.cpp src/*.c src/*.cpp)
SRCS += $(wildcard src/http/*.c src/http/*.cpp)
SRCS += $(wildcard src/listen/*.c src/listen/*.cpp)
SRCS += $(wildcard test/*.c test/*.cpp test/testcase/*.c test/testcase/*.cpp)
OBJS = $(SRCS:.c = .o)
CC = g++
INCLUDES = -Iinclude \
			-Itest \
			-I.
LIBS = -lcurl -lpthread
CCFLAGS = -g -Wall -O0
OUTPUT = nacos-cli.out

all : $(OUTPUT)

$(OUTPUT) : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS) $(CCFLAGS)
%.o : %.c
	$(CC) -c $< $(CCFLAGS)
%.o : %.cpp
	$(CC) -c $< $(CCFLAGS)
testcase : all
SRCS = $(SRCS:testcase/*.c)

clean:
	rm -rf *.out *.o

.PHONY:clean