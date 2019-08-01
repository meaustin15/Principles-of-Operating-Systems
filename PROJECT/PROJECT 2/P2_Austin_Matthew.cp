// Matthew Austin Project 2
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>

using namespace std;

#define NUMBER_OF_THREADS 4

void * Sum(void* index);

long start_numbers[4] = {1, 250001, 500001, 750001};
long numbers[4] = {250000, 500000, 750000, 1000000};


int thread_numbers[4] = {0, 1, 2, 3};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

long result = 0;

int main(){
    
    pthread_t threadid[NUMBER_OF_THREADS];
    int thread_count; 
    
    for(thread_count = 0; thread_count < 4 ; thread_count++){
        if (pthread_create(&threadid[thread_count], NULL, Sum, (void *)&thread_numbers[thread_count]) == -1 ) {
            perror("thread fail");
            exit(-1);
        }
    }

    for(int x = 0; x < 4; x++){
        pthread_join(threadid[x],NULL);
    }
    
    cout << "The Sum Is: " << result << endl;
    
    pthread_mutex_destroy(&mutex);
  
    exit(0);
}

void* Sum(void* index){
    
    pthread_mutex_lock(&mutex);
    int temp_index;
    temp_index = *((int*)index);
    
    for(long i = start_numbers[temp_index]; i <= numbers[temp_index]; i++){
        result += i;
    }
    
    pthread_mutex_unlock(&mutex);
}


