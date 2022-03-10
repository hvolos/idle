/*
* The following program uses pthreads. Each thread has as idle and active period.
* It gets as parameters number of iterations for idle and active period, duration
* of active period in microseconds and duration of idle period in nanoseconds.
* **
* Compiled with: gcc idleness_valication.c -o idle_test -lpthread
* Execute with: ./idle_test 10 250000 250000000 1 (250 ms active and idle period, 10 iterations, 1 thread)
*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <chrono>
#include <chrono>
#include <iostream>
#include <random>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <algorithm>


#include <time.h>
#include <errno.h>

long long int sum=0;
std::chrono::high_resolution_clock::time_point start2, end2, end,start;
std::chrono::duration<double> duration, elapsed_seconds;
long int sleep_time=0, act;
int outside_iterations=1000;



void *myThreadInfLoop1(void *vargp)
{
	
	struct timespec tim, tim2;
	tim.tv_sec = 0;
	tim.tv_nsec = sleep_time;
    long long int j=0;
	
	//start = std::chrono::high_resolution_clock::now();
	for (j=0; j<outside_iterations; j++)
	{
		
		
		start2 = std::chrono::high_resolution_clock::now();
		do
		{
			
			end2 = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end2-start2;
			
		}while(elapsed_seconds.count() < act*1e-6); 
		
		nanosleep(&tim , &tim2); 
		end = std::chrono::high_resolution_clock::now();
		sum = sum + (end-end2).count();	
		
		//std::cout << (end-end2).count() << "ms\n";
		
	}
	
	
	FILE* fp;
	fp = fopen("validation_idle.txt", "a+");
    fprintf(fp, "Sum Idle: %lld\n", sum);
	fclose(fp);
	
}
    


int main(int argc, char** argv)
{
	//vars
	int exec_time, num_thread, index; 
	float idle, act_time;

	//get arguments
	if (argc != 5)
	{
		printf("Wrong Number of Arguments\n");
		return 1;
    }   
	else
	{
		
		
		outside_iterations=atoll(argv[1]);	
		act=atof(argv[2]);
		sleep_time=atoi(argv[3]);
		num_thread = atoi(argv[4]);
    }
	
	//calculate active,idle time for each thread

	//create threads
	pthread_t threadId[num_thread]; // holder for num_threads threads

	// Create num_threads threads
	for(index = 0; index < num_thread; index++)
		pthread_create(&(threadId[index]), NULL, myThreadInfLoop1 , NULL);
	
	// wait for active and idle time
	for(index = 0; index < num_thread; index++)
		pthread_join(threadId[index],NULL);
	
	
	return 0;
	
}
