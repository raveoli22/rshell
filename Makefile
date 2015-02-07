#variables

COMPILER = g++
CFLAGS = -Wall -Werror -ansi -pedantic
VPATH = src
FILEPATH = ./src/main.cpp
FILEPATH2 = ./src/ls.cpp
OUTPATH = ./bin/rshell
OUTPATH2 = ./bin/ls
objects = main.o

#Targets
all:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
rshell:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH)
ls: 
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
clean:
		rm -rf ./bin
