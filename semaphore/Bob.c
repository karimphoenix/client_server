#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define SEMAPHORE_NAME "/Alice_Bob"
int main()
{
	sem_t * semph;

	if ( (semph = sem_open(SEMAPHORE_NAME, 1)) == SEM_FAILED)
	{
		//error when ty to open semaphore
      		perror("sem_open");
      		return 1;
    	}

	//timer for wait for print
	int Timer;
	//for escape from loop
	int i;
	do		//Loop which print B
	{
		//wait semaphore
		sem_wait(semph);
		//random time for semaphore
		Timer = rand()%5;
		//system call sleep
		sleep(Timer);
		//up semaphore
		sem_post(semph);
		//print our message
		printf("B\n");
		usleep(500000);
		//random number, for close programm
		i = rand()%100;

	}while(i!=60);

	//close semaphore
	if (sem_close(semph) == -1)
	{
		//error when try to close semaphore
	      	perror("sem_close");
      		return 1;
    	}

	return 0;
}
