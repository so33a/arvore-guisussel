#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"

ARVORE novaArvore() {
  ARVORE a = malloc(sizeof(struct arvore));  
  a->z = malloc(sizeof(struct node));
  a->raiz = a->z;
  a->raiz->left = a->raiz->right = a->z;
  a->z->left = a->z->right = a->z;
  return a;
}

void imprimePreOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    printf ("%d ", h->key);
    imprimePreOrdemR(a, h->left);
    imprimePreOrdemR(a, h->right);
  }
}

int contaNosR (ARVORE a, link h) {
  if(h == a->z) return 0;
  return 1 + contaNosR(a, h->left) + contaNosR(a, h->right);
}

int contaParesR (ARVORE a, link h) {
  if(h == a->z) 
    return 0;
  if (h->key %2 == 0) 
    return 1 + contaParesR(a, h->left) + contaParesR(a, h->right);
  else
    return  contaParesR(a, h->left) + contaParesR(a, h->right);
}

void imprimePreOrdem (ARVORE a) {
  imprimePreOrdemR(a, a->raiz);
}
void imprimePosOrdemR(ARVORE a, link h) {
  if (h != a->z) {
    imprimePosOrdemR(a, h->left);
    imprimePosOrdemR(a, h->right);
    printf ("%d ", h->key);
  }
}

void imprimePosOrdem (ARVORE a) {
  imprimePosOrdemR(a, a->raiz);
}


void imprimeEmOrdemR (ARVORE a, link h) {
   if (h != a->z) {
     imprimeEmOrdemR(a, h->left);
     printf("%d ", h->key);
     imprimeEmOrdemR(a, h->right);
   }
}

void imprimeEmOrdem (ARVORE a) {
   imprimeEmOrdemR(a, a->raiz); 
}

link buscaR (ARVORE a, link h, int key) {
  if(h == a->z) return NULL;
  if(h->key == key) return h;
  if( h->key < key) 
    return buscaR(a, h->right, key);
  return buscaR(a, h->left, key);
}


link busca (ARVORE a, int key){
  return buscaR(a, a->raiz, key);
}

link novoNo(int key, link l, link r) {
  link x = malloc(sizeof(struct node));
  x->key = key;
  x->left = l;
  x->right = r;
  return x;
}
link inserirR (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key) 
    h->right = inserirR(a, h->right, key);
  else 
    h->left = inserirR(a, h->left, key);
  return h;
}
link inserirT (ARVORE a, link h, int key) {
  if(h == a->z) 
    return novoNo(key, a->z, a->z); 
  if(h->key == key) return h;
  if(h->key < key)  {
    h->right = inserirT(a, h->right, key);
    h = rotL(a, h);
  }
  else {
    h->left = inserirT(a, h->left, key);
    h = rotR(a, h);
  }
  return h;
}

void inserirNaRaiz(ARVORE a, int key) {
  a->raiz = inserirT(a, a->raiz, key);
}

void inserir (ARVORE a, int key){
  a->raiz = inserirR(a, a->raiz, key);
}

void imprimeEmLargura (ARVORE a) {
  link aux;
  FILA f = novaFila();
  enfilar(f, a->raiz);
  while (f->primeiro != NULL) {
    aux = desenfilar(f);
    printf ("%d ", aux->key);
    if (aux->left != a->z)  {
      enfilar (f,aux->left);
    }
    if (aux->right != a->z) {
      enfilar (f,aux->right);
    }
  }
  destroiFila(f);
}

link rotL(ARVORE a, link h) {
  link x = h->right;
  h->right = x->left;
  x->left = h;
  return x; 
}
link rotR(ARVORE a, link h) {
  link x = h->left;
  h->left = x->right;
  x->right = h;
  return x;
}


void remover (ARVORE a, int key){
  if(a == NULL){
    return 0;
  }
  
  struct node* ant = NULL;
  struct node* atual = a;
  while (atual != NULL){
    if(key == atual -> node.key){
      if(atual == a){
        a = removerNo(atual);
      }else{
        if(ant->right == atual){
          ant->right = removerNo(atual)
        }else{
          ant->left = removerNo(atual) 
        }
        return 1;
      }
      ant = atual;
      if(key > atual -> node.key){
        atual = atual -> right;
      }else{
        atual = atual -> left;
      }
    }
  }


void removerNo (ARVORE a, link node){
  struct node *node1, *node2;
  if(node -> left == NULL){
    node2 = node->right;
    free(node);
    return node2;
  }
  
  node1 = node;
  node2 = node->left;
  while(node2->right != NULL){
    node1 = node2;
    node2 = node2 ->right;
  }
  
  if(node1 != node){
    node1->right = node2 -> left;
    node2 -> left = node -> left;
  }
  node2->right = node -> right;
  free(node);
  return node2;
}

void libera_no(struct *node){
  if(node == NULL){
    return;
  }
  libera_no(node->left);
  libera_no(node->right);
  free(node);
  node=NULL;
}  

void destroiArvore(ARVORE a){
  if(a == NULL){
    return;
  }
  libera_no(a);
    free(a);
}



