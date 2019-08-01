//Demonstrates what happens to threads after main thread terminates
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h> //measure the execution time of the computations

using namespace std;

//The number of thread to be generated
#define NUMBER_OF_THREADS 4

//The function that awill serve the role of a thread
void * Sum(void* index);

//used for adding the first 1,000,000 numbers
long numbers[4] = {250000, 500000, 750000, 1000000};
long start_numbers[4] = {1, 250001, 500001, 750001};

//used for adding the first 10,000 numbers
//long numbers[4] = {2500, 5000, 7500, 10000};
//long start_numbers[4] = {1, 2501, 5001, 7501};

int thread_numbers[4] = {0, 1, 2, 3};

int main(){
  pthread_t tid[NUMBER_OF_THREADS]; //The thread ID for each thread
  int tn; //The number of the thread being created

  long sum = 0; //the final sum

  timeval start_time, end_time; //start time struc and end time struct used to track the number of micro seconds passed during the computation

  double start_time_microseconds, end_time_microseconds;

  gettimeofday(&start_time, NULL);

  start_time_microseconds = start_time.tv_sec * 1000000 + start_time.tv_usec;

 //generate the thread
 for(tn = 0; tn < NUMBER_OF_THREADS; tn++){
    //create thread
    if (pthread_create(&tid[tn], NULL, Sum, (void *)&thread_numbers[tn]) == -1 ) {
        perror("thread fail");
        exit(-1);
    }
 }

 long value[4]; //values of the sum from each individual thread. 

 for(int i = 0; i < NUMBER_OF_THREADS; i++){
    if(pthread_join(tid[i],(void **) &value[i]) == 0){
        sum = sum + value[i]; //add four sums together
    }else{
      perror("Thread join failed");
      exit(-1);
    }
 }
 //get the end time in microseconds
 gettimeofday(&end_time, NULL);

 end_time_microseconds = end_time.tv_sec * 1000000 + end_time.tv_usec;

 //calculate the time passed
 double time_passed = end_time_microseconds - start_time_microseconds;

 cout << "Sum is: " << sum << endl;
 cout << "Running time is: " << time_passed << " microseconds" << endl;

 exit(0);
}


//Sum function
void* Sum(void* index){
  int temp_index;

  temp_index = *((int*)index);

  if(temp_index == 0){
     sleep(10);
  }
  long  sum_t = 0;

  for(long i = start_numbers[temp_index]; i <= numbers[temp_index]; i++){
      sum_t = sum_t + i;
  }
  
  cout << "Thread " << temp_index << " terminates" << endl;
  pthread_exit( (void*) sum_t);
}
