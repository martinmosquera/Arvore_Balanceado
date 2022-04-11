// um tipo de estrutura conector recebe o ponteiro de um tipo pero pode apontar
// para varios tipos

#include <stdio.h>
#include <stdlib.h>


typedef struct n2{
    int info;
    int count;
    struct conn* dir;
    struct conn* esq;
}Nodo2;

typedef struct n3{
    int info1;
    int info2;
    int count1;
    int count2;
    struct conn* dir;
    struct conn* cen;
    struct conn* esq;
}Nodo3;

typedef struct n4{
    int info1;
    int info2;
    int info3;
    int cor;
    int count1;
    int count2;
    int count3;
    struct conn* dir;
    struct conn* cen1;
    struct conn* cen2;
    struct conn* esq;
}Nodo4;

typedef struct conn{
    struct n2* nodo2;
    struct n3* nodo3;
    struct n4* nodo4;
    struct conn* pai;
}Conn;

typedef struct root{
    struct conn* root;
    int count;
    int max;
}Root;


Root* create_arv()
{
    Root* r = (Root*)malloc(sizeof(Root));
    if (r == NULL)
        return NULL;
    r->root = NULL;
    return r;
}

Conn* insert(Conn* a, int val){
    if(a == NULL){
        a = (Conn*)malloc(sizeof(Conn));
        if(a == NULL) return 0;
        Nodo2* nodo = (Nodo2*)malloc(sizeof(Nodo2));
        if(nodo == NULL) return 0;
        nodo->info = val;
        nodo->count = 1;
        a->nodo2 = nodo;
        a->nodo3 = NULL;
        a->nodo4 = NULL;
        a->pai = NULL;
        return a;
    }
    else if(a->nodo2 != NULL){
        if(a->nodo2->info == val){
            a->nodo2->count++;
            return a;
        }else if(val>a->nodo2->info){
            a->nodo3 = (Nodo3*)malloc(sizeof(Nodo3));
            if(a->nodo3 == NULL) return 0;
            a->nodo3->info1 = a->nodo2->info;
            a->nodo3->info2 = val;
            Nodo2* aux = a->nodo2;
            a->nodo2 = NULL;
            free(aux);
            a->nodo4 = NULL;
            return a;
        }else if(val<a->nodo2->info){
            a->nodo3 = (Nodo3*)malloc(sizeof(Nodo3));
            if(a->nodo3 == NULL) return 0;
            a->nodo3->info1 = val;
            a->nodo3->info2 = a->nodo2->info;
            Nodo2* aux = a->nodo2;
            a->nodo2 = NULL;
            free(aux);
            a->nodo4 = NULL;
            return a;
        }
    }else if(a->nodo3 != NULL){
        printf("Ainda nao implementei");
    }
}

void print_arv(Conn* c){
    if(c == NULL){ 
        printf(" <> ");
        return;
    }
    if(c->nodo2){
        print_arv(c->nodo2->esq);
        printf("%d ",c->nodo2->info);
        print_arv(c->nodo2->dir);
    }
    if(c->nodo3){
        print_arv(c->nodo3->esq);
        printf("%d ",c->nodo3->info1);
        printf("%d ",c->nodo3->info2);
        print_arv(c->nodo3->dir);
    }
}

int main(){
    Root* r = create_arv();
    r->root = insert(r->root,10);
    printf("%d",r->root->nodo2->info);
    r->root = insert(r->root,4);
    printf("%d",r->root->nodo3->info1);
    printf("%d",r->root->nodo3->info2);
}