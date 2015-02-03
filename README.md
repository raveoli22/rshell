# rshell
This program is a copy of the original BASH terminal. It works like the original BASH, and it also allows users to run multiple commands on the same line by using connectors.
The ; connector will allow the user to execute multiple commands on the same line.
The && connector will only execute the following command if the first command is successfully executed.
The || connector will only execute the following command if the first command failed to execute.

#How to use
Run this program in a linux terminal, however, it is not guarantee to run correctly.

Steps to running program:

$git clone https://github.com/raveoli22/rshell.git

$cd rshell

$git checkout hw0

$make

$bin/rshell

#Prerequisites

Requirements for the program:

- Linux

- g++

- vim

#Bugs/Limitations/Issues

-if the tab is entered before a command then the command will not work

Things not to do:

-many commands except ls and echo will give an error


