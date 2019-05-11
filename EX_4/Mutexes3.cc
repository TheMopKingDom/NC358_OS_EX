// thread0.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define N 3
#define MAXSize 10

void *min_thread(void *arg)
{               int *test = (int*)arg;
                int min=test[0];
     for (int i=0; i<MAXSize ; i++){
    if (test[i] < min){
          min = test[i];
    }
  }     
        //printf("Min number is : %d\n", min);
        static int successmin;
        successmin = min;
        pthread_exit((void *)&successmin);
}
void *max_thread(void *arg)
{               int *test = (int*)arg;
                int max=test[0];
     for (int i=0; i< MAXSize ; i++){
    if (test[i] > max){
          max = test[i];
    }
  }
        //printf("Max number is : %d\n", max);
        static int successmax;
        successmax = max;
        pthread_exit((void *)&successmax);
}
void *Avg_thread(void *arg){
        int *test = (int*)arg;
        int avg=0;
for (int i=0; i< MAXSize ; i++){
        avg += test[i];
}
        avg = avg/MAXSize ;
      //printf("Avg number is : %d\n", avg);
        static int successavg;
        successavg = avg;
        pthread_exit((void *)&successavg);
}
int main(int argc, char *argv[])
{
                srand(time(NULL));
                int random_number[MAXSize];
                void *min,*max,*avg;
                for(int i= 0;i<MAXSize;i++){
                       random_number[i] = rand() % 100 + 1;
                       printf("random_number %d : %d\n",(i+1),random_number[i] );
                }
        pthread_t my_thread[N];
        pthread_create(&my_thread[0], NULL, min_thread, (void*)&random_number);
        pthread_create(&my_thread[1], NULL, max_thread, (void*)&random_number);
        pthread_create(&my_thread[2], NULL, Avg_thread, (void*)&random_number);
        pthread_join(my_thread[0], &min);
        pthread_join(my_thread[1], &max);
        pthread_join(my_thread[2], &avg);
        printf("Min of main : %d\n",*(int *)min);
        printf("Max of main : %d\n",*(int *)max);
        printf("Avg of main : %d\n",*(int *)avg);
        return 0;
}
