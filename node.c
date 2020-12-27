#include"node.h"

struct Node* creatNodeF(void* data)
{
    struct Node* node=(struct Node*) malloc(sizeof(struct Node));
    node->data=data;
    node->next=NULL;
    return node;
}

struct Node* findNode(size_t i,struct Node* head)
{
    size_t index=0;
    struct Node* tmp=head;

    while (tmp!=NULL)
    {
        if(index++==i)
        {
            return tmp;
        }
        tmp=tmp->next;       
    }
    return NULL;

}

void scNode(struct Node *head)
{
    struct Node* tmp=head;
    while (tmp!=NULL)
    {
        printf("%s\n",tmp->data);
        tmp=tmp->next;
    }
    
}

void freeNode(struct Node *head,bool freeDataFlag)
{
    struct Node *tmp=NULL;
    while (head!=NULL)
    {
        tmp=head; 
        head=head->next; 
        if (freeDataFlag)
        {
            free(tmp->data);
            tmp->data=NULL;
        }
        free(tmp);
        tmp=NULL;    
        
    }
    
}

size_t countNode(struct Node *head)
{
    size_t c=0;
    struct Node *tmp=head;
    while (tmp!=NULL)
    {
        c++;
        tmp=tmp->next;
    }
    return c;
}

void addNode(void* data,struct Node *head)
{
   
   struct Node* n=creatNodeF(data);
   struct Node* tmp=head;
    while (tmp!=NULL)
    {
      
        if (tmp->next==NULL)
        {  
            tmp->next=n;
            break;
        }
       
        tmp=tmp->next;
    }
  
   
}

bool delNode(size_t i,bool freeDataFlag,struct Node** head)
{
    size_t index=0;

    struct Node*cur=*head,*pre=NULL;

    while (cur!=NULL)
    {
        //index++;

        if (index++==i)
        {   
            if (i==0)
            {
                *head=(*head)->next;
            }else
            {
                pre->next=cur->next;
            }
           if (freeDataFlag)
           {
               free(cur->data);
               cur->data=NULL;
           }
           
           free(cur);
           cur=NULL;
           return true;
           //break;
        }  
        pre=cur;
        cur=cur->next;       
    }
    return false;
    
}

size_t findContentNode(char* content,bool littlestrflag,struct Node*head)
{
    struct Node* tmp=head;
    size_t i=-1;
    while (tmp!=NULL)
    {
        i++;
        if (littlestrflag)
        {
            if (strstr(tmp->data,content)!=NULL)
            {
                return i;
            }
            
        }else
        {
            if (strcmp((char*)tmp->data,content)==0)
            {
                return i;
            } 
        }
                
        tmp=tmp->next;
    }
    return -1;
}