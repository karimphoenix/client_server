#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
    string answer; //answer from server
    char ans[]="";

    char buf[100];

    int fd_fifoCO; //descriptor of client out fifo
    int fd_fifoCI; //descriptor of client input fifo

    char key[]="";
    printf("Enter your command for server:");
    scanf("%s",&key);

    //try to open server_in
    if ((fd_fifoCO=open("/tmp/server_in", O_WRONLY)) == -1)
    {
        fprintf(stderr,"Can not open server_in for write key\n");
        exit(0);
    }
    //write to fifo
    write(fd_fifoCO,key,strlen(key));

    //close write stream in server_in
	close(fd_fifoCO);

	//try to open server_out for read answer server
    if ((fd_fifoCI=open("/tmp/server_out", O_RDONLY)) == -1)
    {
        fprintf(stderr, "Can not open server_out for read answer\n");
        exit(0);
    }

    //try to read from server_out
    if (read(fd_fifoCI,&ans,sizeof(buf)) == -1)
        fprintf(stderr,"Can not read from server_out\n");
    else
    {

        while (read(fd_fifoCI, ans, sizeof(buf)))
            {
                answer.append(ans, read(fd_fifoCI, ans, sizeof(buf)));
            }
        cout << "Server answer: " << answer<< endl;
    }

    close(fd_fifoCI);

    return 0;

}
