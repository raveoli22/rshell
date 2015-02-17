#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "Timer.h"

using namespace std;

//static const char* INPUT = "/usr/share/dict/linux.words";
#define PRINTTIME(eTime) cout << "User time: " << eTime << endl; \
	t.elapsedWallclockTime(eTime); \
	cout << "Wallclock time: " << eTime << endl;\
	t.elapsedSystemTime (eTime); \
	cout << "System time: " << eTime << endl;


// use get() and put() to copy file
void cp1 (const char *input, const char* output)
{
	Timer t;
	double eTime;
	
	t.start();
	for (int i=0, j; i<1000000000; i++) j++;

	ifstream infile;
	infile.open(input);

	ofstream outfile;
	outfile.open(output);
	
	while (!infile.eof()) {
		char c = infile.get();
		outfile.put(c);
	}
	PRINTTIME(eTime);
}

// uses read and write syscalls to copy (one char at a time)
void cp2 (const char *input, const char *output)
{
	Timer t;
	double eTime;
	
	t.start();
	for (int i=0, j; i<1000000000; i++) j++;

	int input_fd, output_fd;
	ssize_t ret_in, ret_out; // return values of read(in) and read(out)
	char buf[4096];

	input_fd = open(input,O_RDONLY);
	if (input_fd == -1) {
		perror("open");
		return;
	}

	output_fd = open(output, O_RDWR | O_CREAT | O_EXCL);
	if (output_fd == -1) {
		perror("open");
		return;
	}
	
	// copy input to output
	while (ret_in = read (input_fd, &buf, sizeof(buf)), ret_in > 0) {
		ret_out = write (output_fd, &buf, ret_in); 
		if (ret_out != ret_in) {
			perror("Write");
			return;
		}
	}
	
	close (input_fd);
	close (output_fd);

	PRINTTIME(eTime);
}	


// uses read and write syscalls to copy (char buf array)
void cp3 (const char *input, const char *output)
{
	Timer t;
	double eTime;
	
	t.start();
	for (int i=0, j; i<1000000000; i++) j++;

	int input_fd, output_fd;
	ssize_t ret_in, ret_out; // return values of read(in) and read(out)
	char buf[BUFSIZ];

	input_fd = open(input,O_RDONLY);
	if (input_fd == -1) {
		perror("open");
		return;
	}

	output_fd = open(output, O_RDWR | O_CREAT | O_EXCL);
	if (output_fd == -1) {
		perror("open");
		return;
	}
	
	// copy input to output
	while (ret_in = read (input_fd, &buf, BUFSIZ), ret_in > 0) {
		ret_out = write (output_fd, &buf, ret_in); 
		if (ret_out != ret_in) {
			perror("Write");
			return;
		}
	}
	
	close (input_fd);
	close (output_fd);

	PRINTTIME(eTime);
}	

int main ()
{
	cout << "cp1\n";
	cp1("test.txt", "output1.txt");
	cout << endl;

	cout << "cp2\n";
	cp2("test.txt", "output2.txt");
	
	cout << "\ncp3\n";
	cp3("test.txt", "output3.txt");

	return 0;
}
