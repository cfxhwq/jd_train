#include <sys/shm.h>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
using namespace std;

struct Message{
	int id = 0;
	string* str;
};

int main(void){
	int state;
	int key = 12345;
	pid_t pid = fork();
	Message* msg;
	if(pid < 0){
		cerr<< "create pid error" <<endl;
	}
	else if(pid == 0){
		//sub pid
		//read shm
		sleep(5);
		cout<< "------------sub pid------------" <<endl;
		int shm_key = shmget((key_t)key, 0, 0666 | IPC_CREAT);
		void* shm_p = shmat(shm_key, (void*)0, 0);
		msg = (Message*)shm_p;
		cout<< "shm_p:\t" << shm_p <<endl;
		cout<< "msg ptr:\t" << msg <<endl;
		cout<< "int ptr:\t" << &msg->id <<endl;
		cout<< "string ptr:\t" << msg->str <<endl;
		cout<< "sub pid:\t" << msg->id <<endl;
		cout<< "sub pid:\t" << *(msg->str) <<endl;
		cout<< "sub pid ending" <<endl;
		assert(shmdt(shm_p) != -1);
		assert(shmctl(shm_key, IPC_RMID, 0) != -1);
	}
	else{
		//father pid 
		//write shm
		state = shmget((key_t)key, sizeof(Message), 0666 | IPC_CREAT);  	
		if(state < 0){
			perror("shmget error");
			exit(-1);
		}	
		cout<< "shm id:\t" << state <<endl;
		void* shm_p = (void*)0;
		shm_p = shmat(state, (void*)0, 0);
		if(shm_p == (void*)-1){
			exit(-1);
		}
		msg = (Message*)shm_p;
		cout<< "shm ptr:\t" << shm_p <<endl;
		cout<< "ptr:\t" << msg <<endl;
		cout<< "msg ptr:\t" << msg <<endl;
		cout<< "instance" <<endl;
		msg->str = new string("Hello World!");
		msg->id = 123;
		cout<< "msg ptr:\t" << msg <<endl;
		cout<< "int ptr:\t" << &msg->id <<endl;
		cout<< "string ptr:\t" << msg->str <<endl;
		cout<< "father pid:\t" << msg->id <<endl;
		cout<< "father pid:\t" << *(msg->str) <<endl;
		sleep(7);
		assert(shmdt(shm_p) != -1);
		wait(NULL);
	}
}
