#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <string>
#include <iostream>


using namespace std;

string StrFromFile (const string& NameFile, string key);

int main(int argc, char * argv[])
{
    char buf[100];

    string quest;

    string answer;

    string key;

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
    if (read(fd_fifoSI,buf,sizeof(buf)) == -1)
            fprintf(stderr,"Can not read from fifo\n");
    else
        do
        {
            quest="";
            //it will be our question for server
            while (read(fd_fifoSI, buf, sizeof(buf)))
            {
                quest.append(buf, read(fd_fifoSI, buf, sizeof(buf)));
            }
		int i=0;
                //cout << "Client command:" << endl << quest << endl;

		//try to normal key
		key="";
            while (i<quest.length() && quest[i]!=' ' ){ key+=quest[i]; ++i;}
		cout << "Client command: " << key << endl;

        if (key!="stop"){
                //answer from server
		answer=StrFromFile("database.txt", key);

		//write our answer to server_out chanel
                write(fd_fifoSO, answer.c_str(), answer.size());
                cout << "Answer: " << answer << endl;

                sleep(2);
        }
        }
        while (quest!="stop");


	close(fd_fifoSI);
	close(fd_fifoSO);

    //delete our fifo
    unlink("/tmp/server_in");
    unlink("/tmp/server_out");

    return 0;

}

string StrFromFile (const string& NameFile, string key) {
  ifstream file(NameFile.c_str());

  string str;
  string tstr;
  int i;
  while(getline(file, str)) {
    tstr="";
    i=0;
    while (i<str.length() && str[i]!=' ' ){ tstr+=str[i]; ++i;}
    if (tstr == key) break;
  }
	cout << "Find in file "<< str << endl;
  return str;
}
