#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

using namespace std;

int main(){

   int result = fork();

   if( result == -1){
     exit(-1);
   }
   else if(result == 0){
       //this is the child process
       for(int i = 0; i < 10; i++){
           cout << "Child sleeps " << i << " " << result << endl;
           sleep(1);
       }
       exit(0);
       
     
   }
 //  else{
       //this is the parent process
       for(int i = 0; i < 10; i++){
           cout << "Parent sleeps " << i << endl;
           sleep(1);
       }
       cout << "Parent terminated" << endl;
//int status = -999;
       //int child_process_id = wait(&status);
       //cout << "Child process " << child_process_id << "terminated with exit code: " << status << endl;
   //}
}




--------------------------------------
    
          printf( "[parent] pid %d\n", getpid() );
    
    if ( fork() == 0 ){
    for ( int i = 0; i < 10; i++ ){
                
                printf( "[child] pid %d from pid %d\n", getpid(), getppid() );
               // cout << "Child sleeps " << i << endl;
                sleep(1);
                //exit(0);
            }
        
    
    
        
        //for ( int i = 0; i < 3; i++ )
         //   wait( NULL );
    
    }