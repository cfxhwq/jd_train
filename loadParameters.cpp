#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char* argv[]){
	int opt;
	while((opt = getopt(argc, argv, "if:lr")) != -1){
		switch(opt){
			case 'i':
			case 'l':
			case 'r':
				cout<< (char)opt <<endl; 
				break;
			case 'f':
				cout<< (char)opt << "\t" << optarg <<endl;
				break;
			case '?':
				cout<< "unknow:\t" << (char)optopt <<endl;
				break;
		}
	
	}


}
