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

-many of the special cases are bugs, for example, if you input special characters such as '//' or ';' or '=' or '&' or '.....' the program will go to a seg fault instead of creating an error message.

-segfaults will occur depending on what kind of special character you input.

-special characters can also cause program disfunctionalities other than segfaults.

-although special characters do not work, all flags work in every combination, and all of the different combinations of directories work. Everything works fine except for special character cases.

-the only time where bugs can be found is when you mix special characters into the commands.

#TESTING: 

For HW1, I have a made test executable named "tester" that can be found under the test folder so I can run my testcases, which are all listed in testscripts.txt, automatically without having to have the user input each 
testcase manually. The script that I got from my tester executable can be found in the file "NEWlstest.script". Each of the tests are separated by 2 lines of "+" symbols so each separate test can be easily seen. I have 
also included comments along with the test cases. The "NEWlstest.script" shows both the command being typed in and the results from that command. Please disregard the test script "ls.script" and use the "NEWlstest.script" instead. Thank you. 


