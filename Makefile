SRCS = $(wildcard *.c *.cpp ../lib/*.c ../lib/*.cpp src/*.c src/*.cpp)
SRCS += $(wildcard src/http/*.c src/http/*.cpp)
SRCS += $(wildcard src/listen/*.c src/listen/*.cpp)
SRCS += $(wildcard src/config/*.c src/config/*.cpp)
SRCS += $(wildcard src/init/*.c src/init/*.cpp)
SRCS += $(wildcard src/md5/*.c src/md5/*.cpp)
SRCS += $(wildcard src/utils/*.c src/utils/*.cpp)
SRCS += $(wildcard src/naming/*.c src/naming/*.cpp)
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