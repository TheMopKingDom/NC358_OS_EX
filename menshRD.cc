#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SHM_NAME "fuckingworld"

int main(int arg_count, const char **args){

  int shopen = shm_open(SHM_NAME, O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
  if(shopen<0){
    printf("open Error\nNo math shm_name\n");
    exit(0);
  }
  int ftrunc_res = ftruncate(shopen,64);
  int *sh_mm = mmap(0, 64, PROT_READ, MAP_SHARED, shopen, 0);

  printf("try read memsh . . .\n");
		for(int i=0;sh_mm[i]!=-1;i++)
			printf("num %d : %d \n",i,sh_mm[i] );
    printf("read ok end\n");
  close(shopen);
  shm_unlink(SHM_NAME);
  return 0;
}