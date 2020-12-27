#ifndef _HTTP_H_
#define _HTTP_H_
#include <curl/curl.h>
#include<stdio.h>
#include<stdbool.h>
// #define HERADER_CONTENT_TYPE 0b00000001
// #define HERADER_UAER_AGENT 0b00000010
// #define HERADER_REFERER 0b00000100
// #define HERADER_X_REQUESTED_WITH 0b00001000
// #define HERADER_X_COOKIE 0b00010000
//char *http_headers[5]={"Content-Type","User-Agent","Referer","X-Requested-With","Cookie"};

typedef struct curl_slist* Herders;
typedef struct http
{
    char* url;
    char* result;
    FILE* file;
    char* data;
    Herders header;
    int hdr;
    int timeout;
    const char*err;
    
}Http;

//Herders add_header(Herders h,char *val);
Herders setHeader(Herders h,char *key,char *val);
Herders setCookie(Herders h,char *cktmp);
Herders setReferer(Herders h,char *ref);
Herders setUserAgent(Herders h,char *ua);
Herders setAjax(Herders h,bool xml);
Herders initHeader(bool ajx);
void scHerder(Herders h);
void fromCookieKeygetVal(char *result,char* key,char* val);
size_t callback_get_heads(void *, size_t , size_t , void *);
size_t callback_get_file(void *, size_t , size_t , FILE *);
//void freeheader(Herders hd);
long httputils(Http* http);

#endif