#variables

COMPILER = g++
CFLAGS = -Wall -Werror -ansi -pedantic
VPATH = src
FILEPATH = ./src/main.cpp
FILEPATH2 = ./src/ls.cpp
FILEPATH3 = ./src/cp.cpp
FILEPATH4 = ./src/signals.cpp
OUTPATH = ./bin/rshell
OUTPATH2 = ./bin/ls
OUTPATH3 = ./bin/cp
OUTPATH4 = ./bin/signals
objects = main.o

#Targets
all:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH) 
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
		$(COMPILER) $(CFLAGS) $(FILEPATH3) -o $(OUTPATH3)
		$(COMPILER) $(CFLAGS) $(FILEPATH4) -o $(OUTPATH4)
rshell:
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH) -o $(OUTPATH)
ls: 
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH2) -o $(OUTPATH2)
cp: 
		mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH3) -o $(OUTPATH3)

signals:        mkdir -p ./bin
		$(COMPILER) $(CFLAGS) $(FILEPATH4) -o $(OUTPATH4)
 
clean:
		rm -rf ./bin
