#include "msg.pb.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <string>
using namespace std;
using namespace lm;
int main(void){
	int fd[2];
	pipe(fd);
	int pid = fork();
	assert(pid >= 0);
	if(pid == 0){
		close(fd[0]);
		helloworld msg1;
		msg1.set_id(101);
		msg1.set_str("hello");
		string s;
		msg1.SerializeToString(&s);
		write(fd[1], s.c_str(), strlen(s.c_str()));
	}else{
		close(fd[1]);
		sleep(5);
		helloworld msg2;
		char tmp[1025];
		read(fd[0], tmp, 1024);
		string s(tmp); 
		msg2.ParseFromString(s);
		cout<< msg2.str() <<endl;
	
	}

}
