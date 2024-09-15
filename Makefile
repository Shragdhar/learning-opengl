objs: main.cpp glad.c
	g++ -c main.cpp glad.c

all: objs
	g++ -o main main.o glad.o -lGL -lglfw3
	rm main.o glad.o