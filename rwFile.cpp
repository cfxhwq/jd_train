#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
using namespace std;
int main(void){
	fstream file("hello.txt", ios::out);
	assert(file != NULL);
	if(file.is_open()){
		file << "hello world!" <<endl;
		file << "I'm a JDer.";
		file.close();
	}
	else{
		cout<< "unopen file" <<endl;
	}
	cout<< (file==NULL) <<endl;	
	file.open("hello.txt", ios::out | ios::in);
	cout<< file.bad() << file.fail() <<endl;
	int i = 0;
	if(file.is_open())
		while(!file.eof()){
			//cout<< "line " << ++i << ":\t";
			char *s;
			//char s[20];
			file.getline(s, 20);
			cout<< "line " << i << s <<endl;
		}
	file.close();
	cout<< (file == NULL) <<endl;
	cout<< file.bad() << file.fail() <<endl;
	cout<< "end" <<endl;
}

