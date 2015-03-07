#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
using namespace std;

bool system(std::vector<char*> com,char* file,int whichone){
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
		perror("There was an error in execvp().");
	}

	exit(1);
	

    }
    else if (pid > 0){  //parent function
        if (waitpid(pid,&status,0) == -1){
            perror("There was an error with wait().");
            exit(1);
        }
    }
    delete []argv;
    if (status == 0)
        return true;
    return false;

}

void fixline(string &input){
	size_t place = input.find("#");
    	if (place != 1 && place != 0){
        	input = input.substr(0,place);
    	}
	
	size_t check = 0;
	size_t checkagain = 0; 
    	size_t pos = 0;
    	while (check < input.size()){ // search string for the first connector ;
       		
        	check = input.find(";",check+1,1);
        	if (check != string::npos && pos != check){
            		input.replace(check,1," ; "); //if found replace with spaces
			check = check + 2;
            		pos = check+1;
        	}

    	}	

    	check = 0;
    	pos = 0;
    	while (pos < input.size()){
        	check = input.find("&&",check+2,2); //search string for second connector &&
        	if (check != string::npos && pos!= check){
            		input.replace(check,2," && "); //if found replace spaces
			check = check+2;
        	}
        	else {
            		check = input.size();
        	}

        	pos = check+2;
    	}
	
	check = 0;
	pos = 0;
	while (pos < input.size()){
	        check = input.find("||",check+2,2);
		if (check != string::npos && pos!=check){ //search string for third connector ||
		    input.replace(check,2," || "); //if found replace with spaces
		    check = check + 2; 
		}
		else {
		    check = input.size();
		}
		pos = check+2;
	}

	check = 0; 
	pos = 0;
	checkagain = 0;
	while (pos < input.size()){
		check = input.find("|",check+1,1);
		checkagain = input.find("|",check+1,1);
		//cout << check << endl;
		//cout << checkagain << endl;
		if (checkagain == check+1){
			check = checkagain;
			pos = checkagain+1;
		}
		else { 
			if (check != string::npos && pos != check){
				input.replace(check,1," | ");
				check=check+2;
			}
			else {
				check = input.size();
			}
			pos = check+1;
		}
	}
	
	check = 0;
	pos = 0;
	while (pos < input.size()){
		check = input.find("<",check+1,1);
		if (check != string::npos && pos != check){
			input.replace(check,1," < ");
			check = check + 2; 
		}
		else {
			check = input.size();
		}
		pos = check +1; 
	}
	
	check = 0;
	pos = 0;
	while (pos < input.size()){
		check = input.find(">>",check+2,2);
		if (check != string::npos && pos != check){
			input.replace(check,2," >> ");
			check = check + 2;
		}
		else {
			check = input.size();
		}
		pos = check + 2;
	}
	
	check = 0; 
	pos = 0;
	checkagain = 0; 
	while (pos < input.size()){
		check = input.find(">",check+1,1);
		checkagain = input.find(">",check+1,1);
		if (checkagain == check + 1){
			check = checkagain;
			pos = checkagain + 1;
		}
		else{
			if (check != string::npos && pos != check){
				input.replace(check,1," > ");
				check = check + 2;
			}
			else {
				check = input.size();
			}
			pos = check + 1;
		} 
	}

	check = 0; 
	pos = 0;
	checkagain = 0; 
	while (pos < input.size()){
		check = input.find("cd",check+2,2);
		checkagain = input.find("cd",check+2,2);
		if (checkagain == check + 2){
			check = checkagain;
			pos = checkagain + 2;
		}
		else{
			if (check != string::npos && pos != check){
				input.replace(check,2," cd ");
				check = check + 2;
			}
			else {
				check = input.size();
			}
			pos = check + 2;
		} 
	}
	
	
}

void sighandle(int signal){
	if (signal == SIGINT){
		cout << "signal C caught" << endl;
		return;
	}
	if (signal == SIGTSTP){
		cout << "signal Z caught" << endl;
		//raise(SIGSTOP);
	}
}

int main(){
    char hostname[200];
    char username[200];
    vector <char*> commands;
    vector <char*> wordlist;
    int select = 0;
    string single;
    string userinput;
    char* filename = NULL;
    
   
    gethostname(hostname, 200);
    getlogin_r(username,200);

    if (SIG_ERR==signal(SIGINT,sighandle));
    //if (SIG_ERR==signal(SIGTSTP,sighandle));

    while (1){
        bool orflag = false;
	bool rediractivate = false;
	bool isfirstcommand = true;
	bool previouspassed = false;
	int connectorchk = 0; 
	int mustbreak = 0; 
	
	std::cout<< username <<"@"<<hostname<<"$"; //displaying the username and computer name on terminal
        getline(std::cin,userinput);

        fixline(userinput);
	cout << userinput << endl;


        char *token = std::strtok(const_cast<char*>(userinput.c_str()), " ");
        while (token != NULL){
            commands.push_back(token);
            token = std::strtok(NULL, " ");
        }
	
	bool first = true;
	bool test = true;
	select = 0;
	for (unsigned int i = 0; i < commands.size(); i++){ //iterates through the commands
		single = commands.at(i);
		if (single == ";" &&  !wordlist.empty()){ //will execute the command before it
			if (first){ //if its the first command
			test = system(wordlist,filename,select);
			first = false;
			wordlist.clear();
			} //will always execute the command before it
		test = system(wordlist,filename,select);
		wordlist.clear();

		}

		else if (single == "&&" && !wordlist.empty()){ //execute if first command is executed
			if(first){
				test = system(wordlist,filename,select); //if first command in line
				first = false;
				wordlist.clear();
				if (!test){ //if the previous failed
					perror("first command did not execute");
					wordlist.clear();
					break;
				}
			}
			else if (test){ //if the previous command passed
			test = system(wordlist,filename,select);
			wordlist.clear();
			}
			else if (!test){
				perror("first command did not execute");
			}
		}
		else if (single == "||" && !wordlist.empty()){ //execute if the firstcommand did not
			if (first) { //if its the first command in line
				test = system(wordlist,filename,select);
				if (test){
					orflag = true;
				}
				first = false;
				wordlist.clear();
			}
			else if (test){ //if the previous command passed
				perror("first command ran so second cannot");
				wordlist.clear();
				break;
			}
			else if(!test){ //if the previous command did not pass
				test = system(wordlist,filename,select);
				wordlist.clear();
			}
		}

		else if (single == "exit" && !orflag){
			exit(0); //exit rshell
		}
		else if (commands.size() == 1){ //if theres only 1 command typed in with no connectors
			wordlist.push_back(commands.at(i));
			test = system(wordlist,filename,select);
			wordlist.clear();
		}
		else if (single == "cd"){
			i++;
			if(chdir(commands.at(i)) == -1){
				perror("Error with chdir");
			}
		}
		else {
			wordlist.push_back(commands.at(i)); //pushes the commands
			if (i == commands.size()-1){
				if (!orflag){
					test = system(wordlist,filename,select);
					wordlist.clear();
				}
				else if(orflag){ //orflag used to see if an || connector is used
					perror("First command ran so second cannot");
					wordlist.clear();
					break;
				}
			}		
		}
		
	}
	commands.clear();		

	}
}



