#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>



char StrFromFile(char NameFile, int key)
{
   char str[100];

   FILE *file;
   file=fopen(NameFile, "r");

   fscanf(file, "%s", str);

   while(atoi(str) != key)
   {
    fscanf(file, "%s", str);
   }

   fclose(file);

   return str;
}


int main(int argc, char * argv[])
{
    char buf[100];

    char answer[]="";

    int fd_fifoSI; //descriptor of server_in fifo
    int fd_fifoSO; //descriptor of server_out fifo

    //delete file with name of server_in
    unlink("/tmp/server_in");
    //delete file with name of server_out
    unlink("/tmp/server_out");
    //create server_in fifo
    if (mkfifo("/tmp/server_in", O_RDWR | 0600) == -1)
    {
        fprintf(stderr, "Can not create server_in fifo\n");
        exit(0);

    }

    //create server_out fifo
    if(mkfifo("/tmp/server_out", O_RDWR | 0600) == -1)
    {
        fprintf(stderr, "Can not create server_out fifo\n");
        exit(0);
    }

    //try to open server_in for read key
    if ((fd_fifoSI = open("/tmp/server_in", O_RDONLY)) == -1)
        {
            fprintf(stderr,"Can not open fifo for write\n");
            exit(0);
        }

    //try to open server_out for write from server
    if ((fd_fifoSO = open("/tmp/server_out", O_WRONLY)) == -1)
    {
        fprintf(stderr,"Can not open fifo for write\n");
        exit(0);
    }

    //try to read from server_in fifo
    if (read(fd_fifoSI,&buf,sizeof(buf)) == -1)
            fprintf(stderr,"Can not read from fifo\n");
    else
        while (buf!="stop")
            {
                printf("Client command: %s\n",buf);
                int key=atoi(buf);
                answer=StrFromFile("database", key);
                //write our answer to server_out chanel
                write(fd_fifoSO, answer, sizeof(buf));

                sleep(2);
                if (read(fd_fifoSI,&buf,sizeof(buf)) == -1)
                    fprintf(stderr,"Can not read from fifo\n");
            }


    //delete our fifo
    unlink("/tmp/server_in");
    unlink("/tmp/server_out");

    return 0;

}


/*#include <fstream>
#include <string>

int main() {
  std::istream file("file_name.ext");

  while(file) {
    std::string str;
    std::getline(file, str);
    // Обработка строки str
  }

  return 0;
}*/
