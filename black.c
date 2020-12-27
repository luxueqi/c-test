#include"utils.h"
#include"http.h"
#include <unistd.h>

int main(int argc,char *argv[])
{
    char refurl[50]={0},data[64]={0},linebuf[1200]={0},result[1024]={0},err[64]={0};
    int index=1,opt=0;
    char *string="u:i:",*url="https://weibo.com/aj/filter/block?ajwvr=6";
    while ((opt = getopt(argc, argv, string))!= -1)
    {  
        switch (opt)
        {
            case 'u':
            sprintf(refurl,"https://weibo.com/u/%s?is_hot=1",optarg);
            sprintf(data,"uid=%s&filter_type=1&status=1&interact=1&follow=1",optarg);
            break;
            case 'i':
            index=atoi(optarg);
            break;
        }
    } 
    char flag[]="y";
    GREENLOG("是否确认继续(y):%d:%s",index,data);
    scanf("%s",flag);
    if(strcmp(flag,"y")!=0)
    {
        return 0;
    }
    FILE *file=fopen("/Users/xx/Desktop/wei/ck.txt","r");
    if (file==NULL)
    {
        REDLOG("open file err");
        
        exit(EXIT_FAILURE);
    }
    int iline=0;
    while (1)
    {
        iline++;
        if (feof(file))
        {
            break;
        }
        memset(linebuf,0,1200);
        fgets(linebuf,1200,file);
        if (iline<index)
        {
            continue;
        }
        if (startWith(linebuf,"|"))
        {
            continue;
        }
        //去除换行
        linebuf[strlen(linebuf)-1]='\0';
        struct Node *head=creatNodeF(NULL);
        size_t c=split2NodeF(linebuf,"----",head);
        if (c!=4)
        {
            REDLOG("%d-该行数据格式不正确",iline);
            continue;
        }

        memset(result,'\0',1024);
        memset(err,0,64);
        Http h={
            .url=url,
            .data=data,
            .result=result,
            .err=err,
            .header=initHeader(true)
        };
        char *cktmp=(char*)findNode(3,head)->data;
        h.header= setUserAgent(h.header,"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:22.0) Gecko/20100101 Firefox/22.0");
        h.header=setReferer(h.header,refurl);
        h.header=setCookie(h.header,cktmp);
        freeNode(head,true);
        httputils(&h);
        if (h.err!=NULL)
        {
            REDLOG("post err:%s",h.err);
            continue;
        }
        if (strstr(h.result,"code\":\"100000\"")!=NULL)
        {
            GREENLOG("%d-ok",iline);
        }else
        {
            char *tr=strstr(h.result,"}");
            if(tr!=NULL)
            {
                *(tr+1)='\0';
            }
            size_t r_len=strlen(h.result);
            char res[r_len+1];
            memset(res,0,r_len+1);
            unicodetoutf8(h.result,res);
            REDLOG("%d-no-%s",iline,res);
        }
        
        
        sleep(4);
        
        
    }
    
    //sleep(100);
    fclose(file);
    GREENLOG("ok");

}