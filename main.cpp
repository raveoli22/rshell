#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdio.h>

int main(){
    char hostname[200];
    char username[200];
    std::vector <char*> commands;
    std::string userinput;


    bool end = false;
    gethostname(hostname, 200);
    getlogin_r(username,200);

    while (!end){
        std::cout<< username <<"@"<<hostname<<"$";
        getline(std::cin,userinput);
        char *token = std::strtok(const_cast<char*>(userinput.c_str()), ";&|");
        while (token != NULL){
            commands.push_back(token);
            token = std::strtok(NULL, ";&|");
        }
        for (int i = 0; i < commands.size(); i++){
            std::cout<<commands.at(i) << std::endl;
        }
        commands.clear();
    }
}


