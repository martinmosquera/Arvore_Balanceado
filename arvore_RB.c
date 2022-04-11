#include <stdio.h>
#include <stdlib.h>

#define RED   1
#define BLACK 0

typedef struct arvoreRB {
  int info;
  int cor;
  int count;
  struct arvoreRB *esq;
  struct arvoreRB *dir;
  struct arvoreRB *pai;
} ArvoreRB;

typedef struct arvore{
    ArvoreRB* root;
    ArvoreRB* n;
}ArvRB;

ArvRB* create_arv(){
  ArvRB* a = (ArvRB*)malloc(sizeof(ArvRB));
  ArvoreRB* n = (ArvoreRB*)malloc(sizeof(ArvoreRB));
  n->esq = NULL;
  n->dir = NULL;
  n->pai = NULL;
  n->cor = 0;
  n->info = 0;
  a->n = n;
  a->root = a->n;
  return a;
}

ArvoreRB* create_nodo(int val){
  ArvoreRB* n = (ArvoreRB*)malloc(sizeof(ArvoreRB));
  n->esq = NULL;
  n->dir = NULL;
  n->pai = NULL;
  n->info = val;
  n->cor = 1;

return n;
}

int eh_no_vermelho(ArvoreRB * no){
  if(!no) return BLACK;
  return(no->cor == RED);
}

int buscar (ArvoreRB *a, int v) {
  if (a == NULL) { return 0; } /*Nao achou*/
  else if (v < a->info) {
    return buscar (a->esq, v);
  }
  else if (v > a->info) {
    return buscar (a->dir, v);
  }
  else { return 1; } /*Achou*/
}

void in_order(ArvRB* a,ArvoreRB* n){
  if(n != a->n){
    in_order(a,n->esq);
    printf("%d ", n->info);
    in_order(a, n->dir);
  }
}

void print(ArvoreRB * a,int spaces){
  int i;
  for(i=0;i<spaces;i++) printf(" ");
  if(!a){
    printf("//\n");
    return;
  }

  printf("%d\n", a->info);
  print(a->esq,spaces+2);
  print(a->dir,spaces+2);
}

void rota_esq(ArvRB *a, ArvoreRB *n) {
  ArvoreRB *aux = n->dir;
  n->dir = aux->esq;
  if(aux->esq != a->n) {
    aux->esq->pai = n;
  }
  aux->pai = n->pai;
  if(n->pai == a->n) {
    a->root = aux;
  }
  else if(n == n->pai->esq) {
    n->pai->esq = aux;
  }
  else {
    n->pai->dir = aux;
  }
  aux->esq = n;
  n->pai = aux;
}

void rota_dir(ArvRB *a, ArvoreRB *n) {
  ArvoreRB* aux =  n->esq;
  n->esq = aux->dir;
  if(aux->dir != a->n){
    aux->dir->pai = n;
  }
  aux->pai = n->pai;
  if(n->pai == a->n){
    a->root = aux;
  }else if(n == n->pai->dir){
    n->pai->dir = aux;
  }else{
    n->pai->esq = aux;
  }
  aux->dir = n;
  n->pai = aux;
}

void arruma_arriba(ArvRB* a, ArvoreRB *n) {
  while(n->pai->cor == 1){
    if(n->pai == n->pai->pai->esq){
      ArvoreRB* aux = n->pai->pai->dir;
      if(aux->cor == 1){
        n->pai->cor = 0;
        aux->cor = 0;
        n->pai->pai->cor = 1;
        n = n->pai->pai;
      }else{
        if(n == n->pai->dir){
          n == n->pai;
          rota_esq(a,n);
        }
        n->pai->cor = 0;
        n->pai->pai->cor = 1;
        rota_dir(a,n->pai->pai);
        }
      }else{
        ArvoreRB* aux = n->pai->pai->esq;
        if(aux->cor == 1){
          n->pai->cor = 0;
          aux->cor = 0;
          n->pai->pai->cor = 1;
          n = n->pai->pai;
        }else{
          if(n == n->pai->esq){
            n = n->pai;
            rota_dir(a,n);
          }
          n->pai->cor = 0;
          n->pai->pai->cor = 1;
          rota_esq(a,n->pai->pai);
      }
    }
  }
  a->root->cor = 0;
}

void insert(ArvRB* a, ArvoreRB* n) {
  ArvoreRB* aux = a->n;
  ArvoreRB* mov = a->root;

  while(mov != a->n){
    aux = mov;
    if(n->info < mov->info)
      mov = mov->esq;
    else
      mov = mov->dir;
  }
  n->pai = aux;

  if(aux == a->n)
    a->root = n;
  else if(n->info < aux->info)
    aux->esq = n;
  else
    aux->dir = n;
  n->dir = a->n;
  n->esq = a->n;

arruma_arriba(a, n);
}

void mudar_nodos(ArvRB* a,ArvoreRB* n1,ArvoreRB* n2){
  if(n1->pai == a->n)
    a->root = n2;
  else if(n1 == n1->pai->esq)
    n1->pai->esq = n2;
  else
    n1->pai->dir = n2;
  n2->pai = n1->pai;
}

ArvoreRB* min(ArvRB* a, ArvoreRB *n){
  while(n->esq != a->n)
    n = n->esq;
  return n;
}

void del_arruma_arriba(ArvRB* a,ArvoreRB* n){

}

int main(){
  ArvRB* arvore;
  arvore = create_arv();
  ArvoreRB *a,*b,*c,*d,*e,*f,*g;
  a = create_nodo(10);
  b = create_nodo(4);
  c = create_nodo(21);
  d = create_nodo(2);
  e = create_nodo(36);
  f = create_nodo(37);
  g = create_nodo(38);

  insert(arvore,a);
  insert(arvore,b);
  insert(arvore,c);
  insert(arvore,d);
  insert(arvore,e);
  insert(arvore,f);
  insert(arvore,g);

  in_order(arvore,arvore->root);
    return 0;
}
