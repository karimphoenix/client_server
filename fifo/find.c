#include <iostream>
#include <fstream.h>
#include <string.h>
#include <cstdlib.h>

using namespace std;

string StrFromFile(string NameFile, int key)
{
   string str;
   ifstream file(NameFile);
   while(!file.eof())
   {
    getline(file, str);
    int num=atoi(str);
    if (num=key) break;
   }
   file.close()

   return str;
}
