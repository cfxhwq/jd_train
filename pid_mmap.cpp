#include <iostream>
#include <sstream>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

#define BUFSIZE 1024

struct Message{
	int id = 0;
	char* str;
	//string* str;
};

int main(void){
	static const char* shm_name = "/mySHM";
	pid_t pid = fork();
	if(pid < 0){
		cerr<< "create pid error" <<endl;
	}
	else if(pid == 0){
		//sub pid
		//read shm
		sleep(1);
		int shmfd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
		assert(shmfd != -1);
		cout<< "sub pid shmfd:\t" << shmfd <<endl;
		int ret = ftruncate(shmfd, BUFSIZE);
		assert(ret != -1);
		
		Message* shm_mem = (Message*)mmap(NULL, sizeof(Message), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
		assert(shm_mem != MAP_FAILED);
		cout<< "sub pid shm ptr:\t" << shm_mem <<endl; 
		
		ret = close(shmfd);
		if(ret < 0){
			perror("sub close fd error");
		}
		sleep(2);
		cout<< "------------sub pid------------" <<endl;
		cout<< "sub pid:\t" << shm_mem->id <<endl;
		cout<< "sub pid:\t" << shm_mem->str <<endl;
		
		ret = munmap((void*)shm_mem, sizeof(Message));	
		if(ret < 0){
			perror("sub munmap error");
		}
		
		cout<< "sub pid ending" <<endl;
	}
	else{
		//father pid 
		//write shm
		
		int shmfd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
		assert(shmfd != -1);
		cout<< "father pid shmfd:\t" << shmfd <<endl;
		
		int ret = ftruncate(shmfd, BUFSIZE);
		assert(ret != -1);
		
		Message* shm_mem = (Message*)mmap(NULL, sizeof(Message), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
		assert(shm_mem != MAP_FAILED);
		cout<< "father pid shm ptr:\t" << shm_mem <<endl;

		sleep(2);
		
		ret = close(shmfd);
		if(ret < 0){
			perror("father close fd error");
		}

		shm_mem->id =123;
		shm_mem->str = "hello world!\0";

		cout<< "father pid:\t" << shm_mem->id <<endl;
		cout<< "father pid:\t" << shm_mem->str <<endl;
		
		sleep(3);
		ret = munmap((void*)shm_mem, sizeof(Message));	
		if(ret < 0){
			perror("father munmap error");
		}
		ret = shm_unlink(shm_name);
		if(ret < 0){
			perror("father unlink error");
		}
		wait(NULL);
		cout<< "father pid ending" << endl;		
	}
}
