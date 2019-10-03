#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char * argv[])
{
    char buffer[]="TEST\n"; //test word

    char buf[100];

    int fd_fifo; //descriptor

    //delete file with name KDV
    unlink("/tmp/fifo0001");

    //create fifo
    if (mkfifo("/tmp/fifo0001", O_RDWR | 0600) == -1)
    {
        fprintf(stderr, "Can not create fifo\n");
        exit(0);

    }

    //try to open for read/write
    if ((fd_fifo = open("/tmp/fifo0001", O_RDWR)) == -1)
        {
            fprintf(stderr,"Can not open fifo for write\n");
            exit(0);
        }

    //write to fifo
    write(fd_fifo,buffer,strlen(buffer));

    /*
    close(fd_fifo);

    if ((fd_fifo=open("/home/elena/A2/lesson6/fifo0001", O_RDONLY)) == -1)
    {
        fprintf(stderr,"can not open for read\n");
        exit(0);
    }
*/
    //try to read from fifo
    if (read(fd_fifo,&buf,sizeof(buf)) == -1)
            fprintf(stderr,"Can not read from fifo\n");
    else
        printf("Read from fifo: %s\n",buf);

    return 0;

}
