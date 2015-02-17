#variables

COMPILER = g++
CFLAGS = -Wall -Werror -ansi -pedantic
VPATH = src
FILEPATH = ./src/main.cpp
FILEPATH2 = ./src/ls.cpp
FILEPATH3 = ./src/cp.cpp
OUTPATH = ./bin/rshell
OUTPATH2 = ./bin/ls
OUTPATH3 = ./bin/cp
objects = main.o

#Targets
all:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
		$(COMPILER) $(CFLAGS) $(FILEPATH3) -o $(OUTPATH3)
rshell:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH)
ls: 
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
cp: 
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH3) -o $(OUTPATH3) 
clean:
		rm -rf ./bin
