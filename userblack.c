#include"utils.h"
#include"http.h"
#include <unistd.h>
#define URL_POST_BLACK "https://weibo.com/aj/filter/block?ajwvr=6"

#define URL_POST_REPORT "https://service.account.weibo.com/aj/reportspamobile?__rnd=1608914198635"
//#define URL_REFER_BLACK "https://weibo.com/u/%s?is_hot=1"

bool httpinfo(char*url,char*data,char*refer,char* ck,int i,char*name);
char cookie[1024]={0},preuid[12]={0};
int main(int argc,char *argv[])
{
    int opt=0;
    char *string="c:u:";
    while ((opt = getopt(argc, argv, string))!= -1)
    {  
        switch (opt)
        {
            case 'c':
            strcpy(cookie,optarg);
            break;
            case 'u':
            strcpy(preuid,optarg);
            break;
        }
    } 
    FILE *file=fopen("./black.txt","r");
    if (file==NULL)
    {
        REDLOG("open file err");
        exit(EXIT_FAILURE);
    }
    int i=0;
    while (1)
    {
        i++;
        if (feof(file))
        {
            break;
        }
        char linebuf[512]={0};
        fgets(linebuf,512,file);
        if (startWith(linebuf,"|"))
        {
            continue;
        }
        
        linebuf[strlen(linebuf)-1]='\0';
        struct Node *head =creatNodeF(NULL);
        size_t c=split2NodeF(linebuf,":",head);
        if (c!=2)
        {
            REDLOG("%d-该行数据格式不正确",i);
            continue;
        }
        char refer[50]={0},bdata[64]={0};
        char *uid=findNode(1,head)->data;
        char *name=findNode(0,head)->data;
        sprintf(refer,"https://weibo.com/u/%s?is_hot=1",uid);
        sprintf(bdata,"uid=%s&filter_type=1&status=1&interact=1&follow=1",uid);
        if (httpinfo(URL_POST_BLACK,bdata,refer,cookie,i,name))
        {
            usleep(800000);
            char report_refer[88]={0},redata[256]={0};
            sprintf(report_refer,"https://service.account.weibo.com/reportspamobile?rid=%s&type=3&from=40000",uid);
            char res[1024*500]={0},err[64]={0};
            Http h={
                .url=report_refer,
                .hdr=1,
                .result=res,
                .err=err
            };
            h.header=setCookie(h.header,cookie);
            httputils(&h);
            if (h.err==NULL)
            {
                char out[68]={0};
                //REDLOG("get report key err:%s",h.err);05f18b5e7747833e04b80059fbc1a9f569209903=27243bcc15458106315fe62eab
                fromCookieKeygetVal(h.result,"05f18b5e7747833e04b80059fbc1a9f569209903",out);
                if (strlen(out)!=0)
                {
                    sprintf(redata,"category=1&tag_id=108&url=&type=3&rid=%s&uid=%s&r_uid=%s&from=40000&getrid=%s&luicode=0&appGet=0&weiboGet=0&blackUser=1&_t=0",uid,preuid,uid,uid);
                    char ck[1024]={0};
                    sprintf(ck,"%s; %s",cookie,out);
                    httpinfo(URL_POST_REPORT,redata,report_refer,ck,i,name);
                    
                }else
                {
                    REDLOG("get report key err:no key");
                }
                
                
                //continue;
            }else
            {
                REDLOG("get report key err:%s",h.err);
            }
        }
        
        freeNode(head,true);
        sleep(4);
        printf("\n");
        //exit(0);
    }

    fclose(file);
    GREENLOG("ok!!!");
    
    

}


bool httpinfo(char*url,char*data,char*refer,char*ck,int i,char *name)
{
    char result[512]={0},err[64]={0};
    Http h2={
            .url=url,
            .data=data,
            .result=result,
            .err=err,
            .header=initHeader(true)
        };
        h2.header= setUserAgent(h2.header,"Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:22.0) Gecko/20100101 Firefox/22.0");
        h2.header=setReferer(h2.header,refer);
        h2.header=setCookie(h2.header,ck);
        httputils(&h2);
        if (h2.err!=NULL)
        {
            REDLOG("post err:%s",h2.err);
           // continue;
        }else
        {
           //split2NodeF()
            char *mo=strstr(url,"service")?"report":"black";
            if (strstr(h2.result,"code\":\"100000\"")!=NULL)
            {
                //return "ok";
               GREENLOG("%d-%s-%s-ok",i,name,mo);
               return true;
            }else
            {
                char *tr=strstr(h2.result,"}");
                if(tr!=NULL)
                {
                    *(tr+1)='\0';
                }
                 size_t r_len=strlen(h2.result);
                char res[r_len+1];
                memset(res,0,r_len+1);
                unicodetoutf8(h2.result,res);
               
                REDLOG("%d-%s-%s-no-%s",i,name,mo,res);
            }
        }
        return false;
        
}