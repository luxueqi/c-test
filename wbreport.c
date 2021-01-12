#include "http.h"
#include  "utils.h"
#include <string.h>
#define BUFRESULT 10240
#define BUFDATA   256
#define LINEDATA   1024
#define COOKIE     512
int main()
{
    FILE* file=fopen("/Users/xx/Desktop/wei/ck.txt","r");

    if (file==NULL)
    {
        REDLOG("打开文件失败");
        return 0;
    }

    int index=0,start=1;

    char result[BUFRESULT],data[BUFDATA],line[LINEDATA],cookie[COOKIE];

    Http http={

    };

    while (!feof(file))
    {
        index++;

        if (index<start)
        {
            continue;
        }
        
        memset(line,0,LINEDATA);

        //memset(cookie,0,COOKIE);

        fgets(line,LINEDATA,file);

        line[strlen(line)-1]='\0';

        char* ck=strstr(line,"SUB=");

        if (ck==NULL)
        {
            continue;
        }

        

        return 0;
        

    }
    


    
}