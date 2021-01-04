#include "http.h"
#include <string.h>
#include"utils.h"
size_t callback_get_heads(void *ptr, size_t size, size_t nmemb, void *userp)
{
   
   //不是一次性获取要用cat
    strcat(userp,ptr);
   
    return size*nmemb;
}

size_t callback_get_file(void *buffer, size_t size, size_t nmemb, FILE *file){
    size_t r_size = fwrite(buffer, size, nmemb, file);
    return r_size;
}

// Herders add_header(Herders h,char *val)
// {
    
//    return curl_slist_append(h,val);
  
// }

Herders setCookie(Herders h,char *ck)
{   
    return setHeader(h,"Cookie",ck);
}

Herders setReferer(Herders h,char *ref)
{   
    return setHeader(h,"Referer",ref);
}

Herders setUserAgent(Herders h,char *ua)
{   
    return setHeader(h,"User-Agent",ua);
}

Herders setAjax(Herders h,bool xml)
{   
    if (xml)
    {
       return setHeader(h,"X-Requested-With","XMLHttpRequest");
    }
    return h;
}

Herders setHeader(Herders h,char *key,char *val)
{
    size_t klen=strlen(key),vlen=strlen(val),tmplen=klen+vlen+3;
    char tmp[tmplen];
    //(char *)malloc(tmplen);
    memset(tmp,0,tmplen);
    sprintf(tmp,"%s: %s",key,val);
    return curl_slist_append(h,tmp);
}


Herders initHeader(bool ajx)
{
    Herders h=NULL;
    h=curl_slist_append(h,"Content-Type: application/x-www-form-urlencoded");
   // h=curl_slist_append(h,"Content-Type: application/x-www-form-urlencoded");
    return setAjax(h,ajx);
    
}


void fromCookieKeygetVal(char *result,char* key,char* val)
{
    char *p1=strstr(result,key);
    if(p1!=NULL)
    {
        char *p2=strstr(p1,";");
        //printf("%s\n",p1);
        if(p2!=NULL)
        {
            strncpy(val,p1,p2-p1);
        }
    }
   
}

void scHerder(Herders h)
{
    Herders tmp=h;
    while (tmp!=NULL)
    {
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    
}


// void freeheader(Herders hd)
// {
//   // printf("1-%p\n",*hd);
//      if(hd!=NULL)
//     {
//         curl_slist_free_all(hd);
//        // *hd=NULL;
//     }
// }


long httputils(Http *http)
{
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,http->url);
    http->timeout=http->timeout==0?8:http->timeout;
    curl_easy_setopt(curl,CURLOPT_TIMEOUT,http->timeout);
    curl_easy_setopt(curl,CURLOPT_HEADER,http->hdr);
    if(http->header!=NULL)
    {
      curl_easy_setopt(curl,CURLOPT_HTTPHEADER,http->header);
    }
  
    if(http->data!=NULL)
    { 
        curl_easy_setopt(curl,CURLOPT_POST,1);
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,http->data);
    }
    
    if (http->file!=NULL)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_file); //设置下载数据的回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, http->file);
    }else
    {

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_get_heads); //设置下载数据的回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, http->result);
    }
    long r_len=0;
    CURLcode res=curl_easy_perform(curl);
    curl_slist_free_all(http->header);  
    if (http->file!=NULL)
    {
        fseek(http->file,0L,SEEK_END);
        r_len=ftell(http->file);
       
    }else
    {
        r_len=strlen(http->result);
    } 
    curl_easy_cleanup(curl);
    http->err=NULL;
    if(res!=CURLE_OK)
    {
        http->err=curl_easy_strerror(res);
       
    }
   curl_global_cleanup();
   
   return r_len;
    
}