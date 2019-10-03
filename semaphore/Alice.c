#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SEMAPHORE_NAME "/Alice_Bob"


int main()
{
	sem_t * semph;
	
	sem_unlink(SEMAPHORE_NAME);

	if ( (semph = sem_open(SEMAPHORE_NAME, O_CREAT, 0600, 1)) == SEM_FAILED)
	{
		//error when ty to open semaphore
       		perror("sem_open"); 
       		return 1;
    	}

	//timer for wait for print
	int Timer;
	//for escape from loop
	int i;

	do	//loop which prints A
	{
		//reduce semaphore
		sem_wait(semph);
		//random time for semaphore
		Timer = rand()%5;
		//system call sleep
		sleep(Timer);
		//print our message
		printf("A\n");
		sem_post(semph);
		usleep(500000);
		//random number for close semaphore
		i = rand()%100;
	}while(i != 60);

	//close semaphore
	if (sem_close(semph) == -1)
	{
		//error when try to close semaphore
      		perror("sem_close");
      		return 1;
    	}
    	
 	sem_unlink(SEMAPHORE_NAME);

	return 0;
}
