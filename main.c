#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int key;
    int value;
    struct node* next;
}node;

typedef node* bucket;

typedef struct hash_set{
    bucket* array;
    int max_size;
}hash_set;

typedef struct entry{
    int key;
    int value;
}entry;

node* AddToTail(node* L,entry* e){
    node* N=(node*)malloc(sizeof(node));
    N->key=e->key;
    N->value=e->value;
    N->next=NULL;
    if (L==NULL){return N;}
    else{
        node* ptr=L;
        while (ptr->next!=NULL){
            ptr=ptr->next;
        }
        ptr->next=N;
        return L;
    }
}

int hash_function(hash_set* H,entry* e){
    return (e->key)%(H->max_size);
}

hash_set* add(hash_set* H,entry* e){
    int hash_code=hash_function(H,e);
    //bucket list=(H->array)[hash_code];
    (H->array)[hash_code]=AddToTail((H->array)[hash_code],e);
    return H;
}

hash_set* CreateEmpty(){
    hash_set* H=(hash_set*)malloc(sizeof(hash_set));
    int n;
    printf("Give the hash set size : ");
    scanf("%d",&n);
    H->max_size=n;
    H->array=(bucket*)malloc(n*sizeof(bucket));
    for (int i=0;i<n;i++){
        ((H->array)[i])=NULL;
    }
    return H;
}

void show(hash_set* H){
    int n = H->max_size;
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (((H->array) + i)!=NULL) {
            printf("<");
            node* ptr=((H->array)[i]);
            while (ptr!=NULL){
                printf("(%d,%d)->",ptr->key,ptr->value);
                ptr=ptr->next;
            }
            printf("NULL>\n");
        } else {
            printf("<Empty>");
        }
    }
    printf("---------------------------------------------------------------------------\n");
}

int listsize(node* L){
    int s=0;
    node* ptr=L;
    while (ptr!=NULL){
        s++;
        ptr=ptr->next;
    }
    return s;
}

int size(hash_set* H){
    int s=0;
    for (int i=0;i<H->max_size;i++){
        s=s+listsize((H->array)[i]);
    }
    return s;
}

node* Search(node* L,int x){
    node* ptr=L;
    while (ptr!=NULL){
        if (ptr->value==x){return ptr;}
        else{
            ptr=ptr->next;
        }
        return NULL;
    }
}

node* findnode(hash_set* H,int x){
    node* ptr=NULL;
    bucket* arr=H->array;
    int i=0;int n=H->max_size;
    while ((ptr==NULL)&&(i<n)){
        ptr=Search(arr[i],x);
        if (ptr==NULL){i++;}
    }
    return ptr;
}

int findindex(hash_set* H,int x){
    node* ptr=NULL;
    bucket* arr=H->array;
    int i=0;int n=H->max_size;
    while ((ptr==NULL)&&(i<n)){
        ptr=Search(arr[i],x);
        if (ptr==NULL){i++;}
        else{return i;}
    }
    return -1;
}

node* before(node* L,node* p){
    if (L==p){
        return NULL;
    }
    else{
        node* tmp=L;
        while (tmp->next!=p){
            tmp=tmp->next;
        }
        return tmp;
    }
}

node* removenode(node* L,int x){
    node* ptr=L;
    while (ptr->value!=x){
        ptr=ptr->next;
    }
    node* bef=before(L,ptr);
    if (bef==NULL){
        L=L->next;
    }
    else{
        bef->next=ptr->next;
    }
    free(ptr);
    return L;
}

hash_set* removevalue(hash_set* H,int x){
    int i=findindex(H,x);
    bucket* arr=H->array;
    arr[i]=removenode(arr[i],x);
    return H;
}

void main(){
    hash_set* H=CreateEmpty();
    show(H);
    entry* e=(entry*)malloc(sizeof(entry));
    for (int i=0;i<10;i++){
        printf("Give key : ");
        scanf("%d",&(e->key));
        printf("Give value : ");
        scanf("%d",&(e->value));
        H=add(H,e);
        show(H);
    }
    printf("Size is : %d\n",size(H));
    H=removevalue(H,10);
    show(H);
}
