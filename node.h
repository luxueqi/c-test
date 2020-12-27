#ifndef _NODE_H_
#define _NODE_H_
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
struct Node{
    void* data;
    //char* data;
    struct Node* next;
};
void addNode(void* data,struct Node *head);
size_t countNode(struct Node *head);
void freeNode(struct Node *head,bool freeDataFlag);
void scNode(struct Node *head);
struct Node* findNode(size_t i,struct Node* head);
bool delNode(size_t i,bool freeDataFlag,struct Node** head);
struct Node* creatNodeF(void* data);
size_t findContentNode(char* content,bool littlestrflag,struct Node*head);
#endif