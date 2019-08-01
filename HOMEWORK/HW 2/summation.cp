#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

int main(){
  long sum = 0;

   timeval start_time, end_time;

   double start_time_microseconds; //1 second = 1,000,000 microseconds
   double end_time_microseconds;

   gettimeofday(&start_time, NULL);

   start_time_microseconds = start_time.tv_sec * 1000000 + start_time.tv_usec;

   for(long i = 1; i <= 1000000; i++){
      sum = sum + i;
   }

   gettimeofday(&end_time, NULL);

   end_time_microseconds = end_time.tv_sec * 1000000 + end_time.tv_usec;

   double time_passed = end_time_microseconds - start_time_microseconds;

   cout << "Sum is " << sum << endl;
   cout << "Running time is " << time_passed << " microseconds" << endl;
}
