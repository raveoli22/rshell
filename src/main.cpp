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

    size_t place = input.find("#");
    if (place != 1 && place != 0){
        input.substr(0,place);
    }

    //cout << "not in loop";

    size_t check = 0;
    size_t pos = 0;
    while (check < input.size()){ // search string for the first connector ;{
       //cout << "in loop 1";
        check = input.find(";",check+1,1);
        if (check != string::npos && pos != check){
            input.replace(check,1," ; "); //if found replace with spaces
            pos = check+1;
        }

    }

    check = 0;
    pos = 0;
    while (pos < input.size()){
       // cout << "in loop 2";
        check = input.find("&&",check+2,2); //search string for second connector &&
        if (check != string::npos && pos!= check){
            input.replace(check,2," && "); //if found replace spaces
        }
        else {
            check = input.size();
        }

        pos = check+2;
    }

    check = 0;
    pos = 0;
    while (pos < input.size()){
       // cout << "in loop 3";
        check = input.find("||",check+2,2);
        if (check != string::npos && pos!=check){ //search string for third connector ||
            input.replace(check,2," || "); //if found replace with spaces
        }
        else {
            check = input.size();
        }
        pos = check+2;
    }
}

int main(){
    char hostname[200];
    char username[200];
    string endmark = "end";
    vector <char*> commands;

    vector <char*> wordlist;
    string single;
    string userinput;
    bool first = true;
    bool previous = true;
    bool test = true;
    bool run = true;

    gethostname(hostname, 200);
    getlogin_r(username,200);

    while (1){
        std::cout<< username <<"@"<<hostname<<"$"; //displaying the username and computer name on terminal
        getline(std::cin,userinput);

        fixline(userinput);
       //cout << userinput;

        char *token = std::strtok(const_cast<char*>(userinput.c_str()), " ");
        while (token != NULL){
            commands.push_back(token);
            token = std::strtok(NULL, " ");
        }



       // for (int i = 0; i < commands.size(); i++){
        //    cout << commands.at(i) << endl;
       // }


        for (unsigned int i = 0; i < commands.size(); i++){ //iterates through the commands

            single = commands.at(i);

            if (single == "exit"){ //exits out of the shell if exit is found
                exit(0);
            }

            else if (single == ";" &&  !wordlist.empty()){ //will execute the command before it
                if (first){ //if its the first command
                    test = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                test = system(wordlist);
                wordlist.clear();

            }

            else if (single == "&&" && !wordlist.empty()){ //will execute if the first command is successfully executed
                if(first){
                    test = system(wordlist);
                    first = false;
                    wordlist.clear();
                    if (!test){
                        perror("first command did not execute");
                        wordlist.clear();
                        break;
                    }
                }

                else if (test){
                    previous = system(wordlist);
                    wordlist.clear();
                }
                else if (!test){
                    perror("first command did not execute");
                }

            }

            else if (single == "||" && !wordlist.empty()){ //will execute if the first command did not execute

                if (first){
                    test = system(wordlist);
                    first = false;
                    wordlist.clear();
                }
                else if (test){
                    perror("first command ran so second cannot");
                }

                else if(!test){
                    test = system(wordlist);
                    wordlist.clear();
                }
            }

            else if (commands.size() == 1){ //if theres only 1 command typed in with no connectors
                wordlist.push_back(commands.at(i));
                test = system(wordlist);
                wordlist.clear();
            }


            else {
                wordlist.push_back(commands.at(i)); //pushes the commands from commands vector one at a time to execute
                if (i == commands.size()-1){
                    test = system(wordlist);
                    wordlist.clear();
                }
            }
        }







        commands.clear();
    }

}


