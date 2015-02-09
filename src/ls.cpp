#include <sys/types.h>
#include <iomanip>
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
void print(vector<string>filenames,vector<bool>flags,string dir);
void Rfunc(vector<string>filename,vector<bool> flagbool,string pathname);
bool sortfunc(string a, string b){ 
	return tolower(a[0]) < tolower(b[0]);
}

void print(vector<string> filename,vector<bool> flagbool,string dir){
	struct stat filestuff; 
	
	/*if (flagbool.at(0)){
		for (size_t i = 0; i < filename.size(); i++){
			cout << filename.at(i) << " ";
		}
		cout << endl;
	}*/
	if (flagbool.at(1)){ // -l flag was called
		int Total = 0; 
		string completepath;
		string completepath2;
		for (size_t k = 0; k < filename.size(); k++){
			
			completepath = dir + "/" + filename.at(k); 
			//have to trace the path back to original directory 
			if (stat(completepath.c_str(),&filestuff) != 0){
				perror("ERROR HAPPENED 11");
				exit(1); 
			}
			Total = Total + filestuff.st_blocks;
		}
		cout << "total: " << Total/2 << endl;
		for (size_t j = 0; j < filename.size(); j++){
			completepath2 = dir + "/" + filename.at(j);
			//trace back to original directory
			if (stat(completepath2.c_str(),&filestuff) != 0){
				perror("ERROR HAPPENED");
				exit(1);
			}
			
			cout << perm(filestuff.st_mode) << left << setw(5);
			cout << filestuff.st_nlink << left << setw(5);
			struct group fileowner = *getgrgid(filestuff.st_gid);
			cout << fileowner.gr_name << left << setw(5);
			cout << filestuff.st_size << left << setw(5);
			string time = ctime(&filestuff.st_mtime);
			time = time.substr(4,12); //gets time
			//only gets month and time, cuts off day and seconds
			cout << time << left << setw(5);
			cout << "  "; //making the computer line up
			cout << filename.at(j) << left << setw(5);    
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
string perm(mode_t fileinfo){
	string str = "----------";
	if (S_ISBLK(fileinfo)) {
		str[0] = 'b';
	}
	else if (S_ISDIR(fileinfo)) {
		str[0] = 'd';
	}
	else if (S_ISFIFO(fileinfo)) {
		str[0] = 'p';
	}
	else if (S_ISSOCK(fileinfo)) { 
		str[0] = 's';
	}
	else if (S_ISLNK(fileinfo)) {
		str[0] = 'l';
	}
	else if (S_ISCHR(fileinfo)) {
		str[0] = 'c';
	}
	
	if (fileinfo & S_IRUSR) {
		str[1] = 'r';
	}
	if (fileinfo & S_IWUSR) {
		str[2] = 'w';
	}
	if (fileinfo & S_IXUSR) {
		str[3] = 'x';
	}
	if (fileinfo & S_IRGRP) {
		str[4] = 'r';
	}
	if (fileinfo & S_IWGRP) {
		str[5] = 'w';
	}
	if (fileinfo & S_IXGRP) {
		str[6] = 'x';
	}
	if (fileinfo & S_IROTH) { 
		str[7] = 'r';
	}
	if (fileinfo & S_IWOTH) {
		str[8] = 'w';
	}
	if (fileinfo & S_IXOTH) {
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
				} //testing for the -a flag
				else if (flags[j] == 'l'){
					flagbool.at(1) = true;
				} //testing for the -l flag
				else if (flags[j] == 'R'){
					flagbool.at(2) = true; 
				} //testing for the -R flag
				else {
					cout << "ERROR OCCURRED";
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
			if (!flagbool.at(0)){ // tests for the -a flag 
				if (direntp -> d_name[0] != '.'){//if -a flagged
                                        //then do not push files beginning with .	
					filename.push_back(direntp -> d_name);
				}
				
			}
			else if (flagbool.at(0)){
				filename.push_back(direntp -> d_name);
			}
			
		}
		closedir(dirp);
		if (pathname.size() > 1){
			cout << pathname.at(i) << ":" << endl;
			sort(filename.begin(),filename.end(),sortfunc);
			print(filename,flagbool,pathname.at(i));
			filename.clear(); 
		} // if there is more then 1 directory passed in
		else if (flagbool.at(2)){
			//string realpath;
			sort(filename.begin(),filename.end(),sortfunc); 
			cout << pathname.at(i) << ": " << endl;
			print (filename,flagbool,pathname.at(i));
			Rfunc(filename,flagbool,pathname.at(i));}
		else { 
			sort(filename.begin(),filename.end(),sortfunc);
			print(filename,flagbool,pathname.at(i));
			filename.clear();
		} //if there is only 1 directory listed
		
	}		
}
void Rfunc(vector<string> filename, vector<bool> flagbool, string pathname){
	struct stat files;
	vector <string> newfilename;
	string path;
	sort(filename.begin(),filename.end(),sortfunc);

	for (size_t k = 0; k < filename.size(); k++){
		path =  pathname + "/" + filename.at(k); 
		//have to trace the path back to original directory 
		if (stat(path.c_str(),&files) != 0){
			perror("ERROR HAPPENED 11");
			exit(1); 
		}		
		if (S_ISDIR(files.st_mode) && filename.at(k) != "." && filename.at(k) != ".." ){
		//tests to see whether if the file is a directory or not 
			DIR *dirp = opendir(path.c_str());
			if (dirp == NULL){
				perror("ERROR!!!!! with open directory");
				exit(1);
			}
			dirent *direntp;
			while ((direntp = readdir(dirp))){
				if (direntp < 0){
					perror("Error with pointer");
					exit(1);
				}
				if (!flagbool.at(0) && direntp -> d_name[0] != '.'){
					newfilename.push_back(direntp -> d_name);
					//if it is a directory, then push onto new vector
				}
				else if (flagbool.at(0)){
					newfilename.push_back(direntp -> d_name);
					//if -a flag is there or not along with -R
				}
			}
			
			closedir(dirp); //closes 
			Rfunc(newfilename,flagbool,path); //recursive calling back
			sort(newfilename.begin(),newfilename.end(),sortfunc);
	 		cout << "./" <<  filename.at(k) << ": " << endl;
			print (newfilename,flagbool,path); 
			
			//print all sub-directories 
			newfilename.clear();
			
							
		}
		
 
	}
		
}
