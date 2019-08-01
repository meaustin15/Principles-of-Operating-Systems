//Matthew Austin
//used summation-thread.cp as template/reference

//Demonstrates what happens to threads after main thread terminates
#include <pthread.h> //POSIX thread library
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h> //measure the execution time of the computations

using namespace std;

//The number of thread to be generated
#define NUMBER_OF_THREADS 4

//The function that awill serve the role of a thread
void * Prime(void* index);

//used for adding the first 10,000,000 numbers
long numbers[4] = {2500000, 5000000, 7500000, 10000000}; //10 million divded between 4 threads
long start_numbers[4] = {1, 2500001, 5000001, 7500001}; //starting numbers; 10 million divded between 4 threads + 1

int thread_numbers[4] = {0, 1, 2, 3}; //create array that contains 4 threads

int main(){
    pthread_t tid[NUMBER_OF_THREADS]; //The thread ID for each thread
    int tn; //The number of the thread being created
    
    long primes = 0; //the final sum
    
    timeval start_time, end_time; //start time struc and end time struct used to track the number of micro seconds passed during the computation
    
    double start_time_microseconds, end_time_microseconds; // create start and end time
    
    gettimeofday(&start_time, NULL); //Get the start time
    
    start_time_microseconds = start_time.tv_sec * 1000000 + start_time.tv_usec; //initialize start time
    
    //generate the thread
    for(tn = 0; tn < NUMBER_OF_THREADS; tn++){
        //create thread
        if (pthread_create(&tid[tn], NULL, Prime, (void *)&thread_numbers[tn]) == -1 )
        {
            perror("thread fail");
            exit(-1);
        }
    }
    
    long value[4]; //values of the sum from each individual thread.
    
    for(int i = 0; i < NUMBER_OF_THREADS; i++){
        if(pthread_join(tid[i],(void **) &value[i]) == 0){
            primes = primes + value[i]; //add four sums together
        }else{
            perror("Thread join failed");
            exit(-1);
        }
    }
    //get the end time in microseconds
    gettimeofday(&end_time, NULL);
    
    //endtime
    end_time_microseconds = end_time.tv_sec * 1000000 + end_time.tv_usec;
    
    //calculate the time passed
    double time_passed = end_time_microseconds - start_time_microseconds;
    
    cout << "Number of primes [Not Inlcuding 1]: " << primes - 1 << endl; //displays number of primes not including 1
    cout << "Number of primes [Inlcuding 1]: " << primes << endl; //displays number of primes including 1
    cout << "Run time is: " << time_passed << " microseconds" << endl; //Shows run time
    
    exit(0); //exit
}


//Prime function
void* Prime(void* index){
    int temp_index; //create in temp_index
    
    temp_index = *((int*)index); //initialize temp index
    
    long  sum_t = 0; //variable that will hold the amount of primes
    bool prime; //boolean that will filter not prime numbers
    
    for(long i = start_numbers[temp_index]; i <= numbers[temp_index]; i++){
    
        prime = true;
        for(long filter = 2; filter * filter <= i; filter++){
            if(i % filter == 0){
                prime = false;
            }
        }
        
        // if the number is price add that to the total of prime numbers found
        if(prime){
            sum_t = sum_t + 1;
        }
    }
    cout << "Thread " << temp_index << " terminates" << endl; //Which Thread Terminates
    pthread_exit( (void*) sum_t); //Thread exits
}
