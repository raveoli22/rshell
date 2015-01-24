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
    if (pid < 0) //there was an error in the fork process
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
    int pos = 0;
    pos = input.find("#"); //checks the input vector for "#" symbol
                          //deletes everything after it, disregard as comments
    if (pos != 0){
        input.erase(pos);
    }

    for (int x = 0; x < input.size(); x++){
        pos = input.find(";",x,1);
        if (pos != string::npos){
            input.replace(pos,1," ; ");
        }

    }

    for (int x = 0; x < input.size(); x++){
        pos = input.find("&&",x,2);
        if (pos != string::npos){
            input.replace(pos,2," && ");
        }
    }

    for (int x = 0; x < input.size(); x++){
        pos = input.find("||",x,2);
        if (pos != string::npos){
            input.replace(pos,2," || ");
        }
   }
   /* while (x < input.size()){  //looks for the first ;
     x = input.find(";",x+1,1); //searches string for ; after the first one is found
     if (x != string::npos && count != x){
            input.replace(x,1," ; "); //adds space between it
            count = x+1;
        }

    }

    int x = 0;
    int count = 0;
    while (x < input.size()){
        x = input.find("&&",x+2,2); //continues to search for && after first one is found
        if (x!= string::npos && count != x){
            input.replace(x,2," && "); //adds space between the connectors
            count = x+2;
        }
    }


    x = 0;
    count = 0;
    while (x < input.size()){ //searches for the first || that appears
        x = input.find("||",x+2,2); //continues to search for || after first one is found
        if (x!= string::npos && count != x){ //adds space between the connectors
            input.replace(x,2," || ");
            count = x + 2;
        }
     }*/
}

int main(){
    char hostname[200];
    char username[200];
    vector <char*> commands;
    vector <char*> wordlist;
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
        for (int i = 0; i < commands.size(); i++){

           cout << commands.at(i);
           /* single = commands.at(i);
            if (single == "exit"){
                exit(0);
            }
            else if (single == ";" &&  !wordlist.empty()){
                if (first){
                    previous = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                previous = system(wordlist);
                wordlist.clear();

            }
            else if (single == "&&" && !wordlist.empty()){
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
            else if (single == "||" && !wordlist.empty()){
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

            else if (first && commands.size() == 1){
                wordlist.push_back(commands.at(i));
                previous = system(wordlist);
                wordlist.clear();
            }
            else {
                wordlist.push_back(commands.at(i));
            }*/
        }
        commands.clear();
    }
}


