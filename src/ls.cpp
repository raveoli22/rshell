#include <sys/types.h>
#include <stack>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <sys/stat.h>
#include <linux/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <vector>
#include <iostream>


using namespace std;
string perm(mode_t info);

void print(vector<string> filename,vector<bool> flagbool){
	struct stat filestuff; 
	
	/*if (flagbool.at(0)){
		for (size_t i = 0; i < filename.size(); i++){
			cout << filename.at(i) << " ";
		}
		cout << endl;
	}*/
	if (flagbool.at(1)){ // -l flag was called
		for (size_t j = 0; j < filename.size(); j++){
			if (stat(filename.at(j).c_str(),&filestuff) != 0){
				perror("ERROR HAPPENED");
				exit(1);
			}
			
			cout << perm(filestuff.st_mode) << "\t";
			cout << filestuff.st_nlink << "\t";
			struct group fileowner = *getgrgid(filestuff.st_gid);
			cout << fileowner.gr_name << "\t";
			cout << filestuff.st_size << "\t";
			string time = ctime(&filestuff.st_mtime);
			cout << time.substr(4,12) << "\t";
			cout << filename.at(j) << "\t";	
			cout << endl;
			 
		}
	}
	else {
		for (size_t n = 0; n < filename.size(); n++){
			cout << filename.at(n) << " ";
		}
		cout << endl;
	}
} 
string perm(mode_t info){
	string str = "----------";
	if (S_ISBLK(info)) {
		str[0] = 'b';
	}
	else if (S_ISDIR(info)) {
		str[0] = 'd';
	}
	else if (S_ISFIFO(info)) {
		str[0] = 'p';
	}
	else if (S_ISSOCK(info)) { 
		str[0] = 's';
	}
	else if (S_ISLNK(info)) {
		str[0] = 'l';
	}
	else if (S_ISCHR(info)) {
		str[0] = 'c';
	}
	
	if (info & S_IRUSR) {
		str[1] = 'r';
	}
	if (info & S_IWUSR) {
		str[2] = 'w';
	}
	if (info & S_IXUSR) {
		str[3] = 'x';
	}
	if (info & S_IRGRP) {
		str[4] = 'r';
	}
	if (info & S_IWGRP) {
		str[5] = 'w';
	}
	if (info & S_IXGRP) {
		str[6] = 'x';
	}
	if (info & S_IROTH) { 
		str[7] = 'r';
	}
	if (info & S_IWOTH) {
		str[8] = 'w';
	}
	if (info & S_IXOTH) {
		str[9] = 'x';
	}
	
	return str; 
}
	
	
	
int main(int argc, char** argv){ 
	
	
	if (argc < 1){
		perror("AN ERROR HAS OCCURRED");
	}
	
	string flagstring;
	vector <bool> flagbool(3,false);
	vector <string> pathname;
	vector <string> filename; 
	char* flags;
	int size = argc; 
		
	
	
	for (int i = 1; i < size; i++){
		flagstring = argv[i];
		if (flagstring[0] == '-'){
			flags = argv[i];
			for (int j = 1; flags[j] != '\0'; j++){
				if (flags[j] == 'a'){
					flagbool.at(0) = true;
				}
				else if (flags[j] == 'l'){
					flagbool.at(1) = true;
				}
				else if (flags[j] == 'R'){
					flagbool.at(2) = true; 
				}
				else {
					perror("ERROR HAPPENED");
					exit(1);
				}
			}
		}
		else {
			pathname.push_back(argv[i]);	
		}
	}
	if (pathname.empty()){
		 
		pathname.push_back(".");
	}
	
	for (size_t i = 0; i < pathname.size(); i++){
		DIR *dirp = opendir(pathname.at(i).c_str());
		dirent *direntp;
		while ((direntp = readdir(dirp))){
			if (!flagbool.at(0)){
				if (direntp -> d_name[0] != '.'){	
					filename.push_back(direntp -> d_name);
				}
				
			}
			else if (flagbool.at(0)){
				filename.push_back(direntp -> d_name);
			}
			
		}
		closedir(dirp);
	}		
	
	
	
	for (size_t b = 0; b < pathname.size(); b++){
		if (pathname.size() > 1){
			cout << pathname.at(b) << ":" << endl;
			//open function
		}
		print(filename,flagbool);
	}
	
		// open function

/*
	for (size_t i = 0; i < flagbool.size(); i++){
		cout << flagbool.at(i) << endl;
	}
	for (size_t i = 0; i < filename.size(); i++){
		cout << filename.at(i) << endl; 
	}
*/
}
