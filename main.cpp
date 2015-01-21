#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>

int main(){
    char hostname[200];
    char username[200];
    std::string userinput;
    int result;

    bool end = false;
    gethostname(hostname, 200);
    getlogin_r(username,200);

    while (!end){
        std::cout<< username <<"@"<<hostname<<"$";
        getline(std::cin,userinput);
    }
}


