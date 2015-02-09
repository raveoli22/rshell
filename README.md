# rshell

#HW0 Description
This program is a copy of the original BASH terminal. It works like the original BASH, and it also allows users to run multiple commands on the same line by using connectors.
The ; connector will allow the user to execute multiple commands on the same line.
The && connector will only execute the following command if the first command is successfully executed.
The || connector will only execute the following command if the first command failed to execute.

#HW1 Description
This program is a copy of the original BASH terminal implementation of the ls command. It works just like the way it does in the original terminal. However, only the flags -a -l and -R are implemented in this version. This program will allow the user to use these flags to tell them about the files within each directory. The command bin/ls will print all the current files and directories within the current working directory. The -a flag will print out all files including hidden files. The -l flag will print out the permissions, time, and size of the files. The -R flag will print out recursively all of the directories, files, and all of those that are within each directory as well. 

#How to use
Run this program in a linux terminal, however, it is not guarantee to run correctly.

Steps to running program:
For HW0:
$git clone https://github.com/raveoli22/rshell.git

$cd rshell

$git checkout hw0

$make

$bin/rshell

For HW1: 
$git clone https://github.com/raveoli22/rshell.git

$cd rshell

$git checkout hw1

$make

$bin/ls


#Prerequisites

Requirements for the program:

- Linux

- g++

- vim

#Bugs/Limitations/Issues
For hw0:
-if the tab is entered before a command then the command will not work

Things not to do:

-many commands except ls and echo will give an error

For hw1:

-If you input a 1 character directory that is not within the current working directory,the program will not report an error but it will not do anything either. 



