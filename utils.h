#ifndef _UTILS_H_
#define _UTILS_H_
#include <time.h>
#include <stdlib.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include<stdio.h>
#include"node.h"
size_t split(char* src,char* spstr,char**out);
void split_free(char **t,size_t count);
char *strtime(time_t tmp,char*format);
#define GREENLOG(FORMAT,...)  printf("[%s]",strtime(0,"%Y/%m/%d %H:%M:%S"));printf("\033[32m"FORMAT"\033[0m\n",##__VA_ARGS__)
#define REDLOG(FORMAT,...)  printf("[%s]",strtime(0,"%Y/%m/%d %H:%M:%S"));printf("\033[31m"FORMAT"\033[0m\n",##__VA_ARGS__)
char *creatDataF(char *src,size_t len);
size_t split2NodeF(char* src,char* little,struct Node *head);
char* serachstr(char *big,char *left,char *right,char *result);
size_t mid2NodeF(char* big,char*left,char*right,struct Node* head,size_t c);
size_t countStr(char*little,char*big);
char* strRplaceF(char*old,char*new,char*src,size_t c_rplace);
//void strRplaceFree(char** r);
char* strSubF(char*src,size_t i,size_t len);
void strFree(char**r);
bool startWith(char*src,char*little);
void utochinese(char* input,char*out);
void unicodetoutf8(char*input,char*out);
char* strJqF(char*src,char*left,char*right);
char* findKeyValueF(char*key,char*src);
#endif