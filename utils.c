#include "utils.h"


char *strtime(time_t tmp,char*format)
{
    if(tmp==0)
    {
        tmp=time(NULL);
    }
    //printf("%ld\n",strlen(format));
    static char stime[100]={0};
    //char *p=stime;"%Y/%m/%d %H:%M:%S"
    strftime(stime,100,format,localtime(&tmp));
    return stime;
}

size_t split(char* src,char* spstr,char**out)
{
    size_t i=0;
    char* tmpp=src,*tt=NULL;
    size_t splen=strlen(spstr);
    while((tt=strstr(tmpp,spstr))!=NULL)
    {
        i++;
        int len=tt-tmpp;
        char* tc=(char*)calloc(len+1,sizeof(char));          
        strncpy(tc,tmpp,len);
        *out++=tc;
        tmpp=tt+splen;
    }
    if (tmpp!=NULL)
    {
        i++;
        *out=tmpp;
    }
    return i;

}

void split_free(char **t,size_t count)
{
    for (size_t ii = 0; ii < count-1; ii++)
    {
        char*tmp=*t++;
        free(tmp);
        tmp=NULL;
    }
    *t=NULL;
}





char *creatDataF(char *src,size_t len)
{
    char* tc=(char*)calloc(len+1,sizeof(char));          
    strncpy(tc,src,len);
    return tc;
}


size_t split2NodeF(char* src,char* little,struct Node *head)
{
    
    char* tmpp=src,*tt=NULL;
    size_t litlen=strlen(little);
    int i=0,len;
    while (++i)
    {
        tt=strstr(tmpp,little);
        len=tt==NULL?strlen(tmpp):tt-tmpp;
        char* tc=creatDataF(tmpp,len);
       
        if (i==1)
        {
            head->data=tc;
            
        } else
        {
           addNode(tc,head);
        }      
        if (tt==NULL)
        {
            break;
        }
        
        tmpp=tt+litlen;
    }
    
    
    return i;
    //return head;

}

char* serachstr(char *big,char *left,char *right,char *result)
{
   
    char* tmp=strstr(big,left);

    if (tmp!=NULL)
    {
        tmp+=strlen(left);
        char* tmp1=strstr(tmp,right);
        if (tmp1!=NULL)
        {
            
            strncpy(result,tmp,tmp1-tmp);
            return tmp1+strlen(right);
        }
        
        
    }

    return NULL;
    
}

size_t mid2NodeF(char* big,char*left,char*right,struct Node* head)
{
    size_t i=0;

    size_t l_len=strlen(left),r_len=strlen(right);

    char *tmp=NULL,*src=big,*rtmp=NULL,*data=NULL;
    while ((tmp=strstr(src,left))!=NULL)
    {
        tmp+=l_len;
        rtmp=strstr(tmp,right);
        if (rtmp==NULL)
        {
            break;
        }
        i++;
        data=creatDataF(tmp,rtmp-tmp);
        if (i==1)
        {
            head->data=data;
        }else
        {
            addNode(data,head);
        }
        src=rtmp+r_len;
        
    }

    return i;
    
    
}

size_t countStr(char*little,char*big)
{
    size_t i=0,l_len=strlen(little);
    char* tmp=NULL,*bigtmp=big;
    while ((tmp=strstr(bigtmp,little))!=NULL)
    {
        i++;
        bigtmp=tmp+l_len;
    }
    return i;
}

//yao释放
char* strRplaceF(char*old,char*new,char*src,size_t c_rplace)
{
    size_t count=countStr(old,src);
    c_rplace=(c_rplace>count||c_rplace==0)?count:c_rplace;
    size_t o_len=strlen(old),n_len=strlen(new),s_len=strlen(src),r_len=(n_len-o_len)*c_rplace+s_len+1;
    char*  result=(char*)malloc(r_len);
    memset(result,0,r_len);
    char *tmp=NULL,*srctmp=src;
    size_t tmpli_len=0,c_c=0;
    while ((tmp=strstr(srctmp,old))!=NULL)
    {
        tmpli_len=tmp-srctmp;
        strncat(result,srctmp,tmpli_len);
        strcat(result,new);
        c_c++;
        srctmp=tmp+o_len;
        if (c_rplace==c_c)
        {
            break;
        }
        
    }
    // if (tmpli_len==-1)
    // {
        strcat(result,srctmp);
   // }
    
    
    return result;  
    
}

// void strRplaceFree(char** r)
// {
//     if (*r!=NULL)
//     {
//         free(*r);
//         *r=NULL;
//     }

// }

char* strSubF(char*src,size_t i,size_t len)
{
    size_t srclen=strlen(src);
    len=len>srclen?srclen:len;
    return creatDataF(src+i,len);
}

void strFree(char**r)
{
    free(*r);
    *r=NULL;
}

bool startWith(char*src,char*little)
{
    char*tmp=strstr(src,little);
    return tmp-src==0;
}

// void strSubFree(char**r)
// {}

void utochinese(char* input,char*out)
{
  char tmp[11]={0};
  sprintf(tmp,"0x%s",input);
  unsigned long i=strtoul(tmp,NULL,16);
  //printf("%lu\n",i);
  if (i<2048||i>65535)
  {
      printf("%lu超出范围(2048-65535)\n",i);
      exit(EXIT_FAILURE);
  }
  
  char ss[]="0000000000000000";
  int index=15;
  char s[3][9]={
      "1110",
      "10",
      "10"
  };
  while (i)
  {
      ss[index--]=i%2?'1':'0';    
      i/=2;
  }
  strncat(s[0],ss,4);
  strncat(s[1],ss+4,6);
  strncat(s[2],ss+10,6);
  for (size_t j = 0; j < 3; j++)
  {
      out[j]=strtoul(s[j],NULL,2);
     // printf("%d\n",out[i]);
  }
}

void unicodetoutf8(char*input,char*out)
{
    
    char *tmp=NULL,*ser=input;
    while ((tmp=strstr(ser,"\\u"))!=NULL)
    {
        char ii[5]={0},oo[4]={0};
        strncpy(ii,tmp+2,4);
        utochinese(ii,oo);
        strncat(out,ser,tmp-ser);
        strncat(out,oo,3);
        ser=tmp+6;
    }
    strcat(out,ser);
    
}