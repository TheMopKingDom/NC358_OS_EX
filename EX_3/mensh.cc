
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "fuckingworld"

static int coun_num(int num){
	if((num%2)==0)
		return num /2;
	else
		return 3*num+1;
}

int main()
{	
	shm_unlink(SHM_NAME);
	int shm_fd = shm_open(SHM_NAME,O_CREAT|O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	if(shm_fd==-1){
		printf("open Error\n");
		exit(0);
	}
	int ftrunc_res = ftruncate(shm_fd,64);
	if(ftrunc_res==-1){
		printf("Cate Error\n");
		exit(0);
	}
	int * sh_mm = mmap(0, 64, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (sh_mm==MAP_FAILED){
		printf("Mmap Error\n");
		exit(0);
	}

	//fork ps
	pid_t pid=fork();
	if(pid<0){
		printf("Fail in fork\n");
		exit(0);
	}
	else if (pid==0){
		printf("Child ps created\nEnter some int to start : ");
		int st;
		scanf("%d",&st);
		sh_mm[0]=st;
	for(int i =1;;i++){
		if(st>1){
			sh_mm[i]=coun_num(st);
			st=sh_mm[i];
		}
		else{
			sh_mm[i]=-1;
			break;
		}
	}

	}
	else{
		wait(NULL);
		printf("Child fin\nshow value for shmem\n");
		for(int i=0;sh_mm[i]!=-1;i++)
			printf("num %d : %d \n",i,sh_mm[i] );
	}
	close(shm_fd); 
	shm_unlink(SHM_NAME); //remove Shared-Memory Object
	//if you wnat to use with memshRD.cc 
	//set it line to comment.
	return 0;
}
