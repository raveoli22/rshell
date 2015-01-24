#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

bool system(std::vector<char*> com){
    int argc = com.size()+1;
    int status;
    char **argv = new char*[argc];
    for (int i = 0; i < argc-1; i++){
        argv[i] = com[i];
    }
    argv[argc-1] = '\0';
    int pid = fork();
    if (pid == -1) //there was an error in the fork process
    {
        perror("error with fork");
        exit(1);
    }

    else if (pid == 0) //you are in child process
    {
        std::cout << "You are in child process";
        if (-1 == execvp(argv[0],argv)){
            perror("There was an error in execvp().");}
            exit(1);

    }
    else if (pid > 0){  //parent function
        if (waitpid(pid,&status,0) == -1){
            perror("There was an error with wait().");
            exit(1);
        }
    }
    if (status == 0)
        return true;
    return false;

}

void fixline(string &input){

    unsigned int pos = 0;
    unsigned int count = 0;

    while (pos < input.size()){

     pos = input.find(";",pos+1,1); //searches string for ; in the command
     if (pos != string::npos&&count!=pos){
            input.replace(pos,1," ; "); //adds space between it
        }

    }

    pos = 0;
    count = 0;

    while (pos < input.size()){

        pos = input.find("&&",pos+2,2); //searches for && in the commands
        if (pos!= string::npos){
            input.replace(pos,2," && "); //adds space between the connectors
        }
    }


    pos = 0;
    count = 0;
    while (pos < input.size()){

        pos = input.find("||",pos+2,2); //  searches for || after first one is found
        if (pos!= string::npos){ //adds space between the connectors
            input.replace(pos,2," || ");
        }

     }
}

int main(){
    char hostname[200];
    char username[200];
    vector <char*> commands;
    commands.resize(30000);
    vector <char*> wordlist;
    commands.resize(30000);
    string single;
    string userinput;
    bool first = true;
    bool previous = false;

    gethostname(hostname, 200);
    getlogin_r(username,200);

    while (1){
        std::cout<< username <<"@"<<hostname<<"$"; //displaying the username and computer name on terminal
        getline(std::cin,userinput);

        fixline(userinput);

        char *token = std::strtok(const_cast<char*>(userinput.c_str()), " ");
        while (token != NULL){
            commands.push_back(token);
            token = std::strtok(NULL, " ");
        }
        for (unsigned int i = 0; i < commands.size(); i++){ //iterates through the commands

            single = commands.at(i);
            if (single == "exit"){ //exits out of the shell if exit is found
                exit(0);
            }
            else if (single == ";" &&  !wordlist.empty()){ //will execute the command before it
                if (first){ //if its the first command
                    previous = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                previous = system(wordlist);
                wordlist.clear();

            }
            else if (single == "&&" && !wordlist.empty()){ //will execute if the first command is successfully executed
                if(first){
                    previous = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                else if (previous){
                    previous = system(wordlist);
                    wordlist.clear();
                }
                else {
                    perror("first command did not execute");
                }

            }
            else if (single == "||" && !wordlist.empty()){ //will execute if the first command did not execute
                if(first){
                    previous = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                else if (!previous){
                    previous = system(wordlist);
                    wordlist.clear();
                }
                else {
                    perror("first command did execute so second cannot");
                }
            }

            else if (first && commands.size() == 1){ //if theres only 1 command typed in with no connectors
                wordlist.push_back(commands.at(i));
                previous = system(wordlist);
                wordlist.clear();
            }
            else {
                wordlist.push_back(commands.at(i)); //pushes the commands from commands vector one at a time to execute
            }
        }
        commands.clear();
    }
}


