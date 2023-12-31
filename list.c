#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  //simplemente se crea una lista nueva y se le asigna memoria con malloc
  List *newList = (List*)malloc(sizeof(List));
     return newList;
}

void * firstList(List * list) {
  if(list->head == NULL || list == NULL){return NULL;}//se toman en cuenta los casos donde alguna variable necesaria sea NULL
  
  list->current = list->head;//se cambia el current por el head de la lista
    return list->current->data;
}

void * nextList(List * list) {
  if(list==NULL || list->current==NULL || list->current->next==NULL){return NULL;}
  //los casos donde algo es null incluido a donde queremos mover el current
  list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
  //primero se consideran los casos sin datos y luego resuelve igual que en nextlist y firstlist
  if(list==NULL || list->current==NULL || list->tail==NULL){return NULL;}

  list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
  if(list==NULL || list->current==NULL || list->current->prev==NULL){return NULL;}
  //casos donde no haya datos o este el current en un extremo

  list->current = list->current->prev; //se asigna los punteros correspondientes
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->head){
    //establezco el orden entre ambos nodos
    list->head->prev = newNode;
    newNode->next=list->head;
  }
  //si no hay tail, entonces el nuevo nodo sera tambien la cola
  if(list->tail==NULL){
    list->tail=newNode;
  }
  //luego reemplazp el head por el nuevo nodo
  //si no existe el head se hace solo esto
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *newNode = createNode(data);
  if(list->current->next){
    list->current->next->prev = newNode;//el anterior al siguiente del current es el nuevo
    newNode->next = list->current->next;//el siguiente del nuevo es el siguiente del current
  }
  newNode->prev = list->current;
  list->current->next = newNode;
  
  if(newNode->next==NULL){//caso donde el nuevo nodo sea la cola
    list->tail = newNode;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  Node *anterior=list->current->prev;
  Node *siguiente=list->current->next;
  //como se pasara el current al siguiente, debo guardar el dato del eliminado
  void *datoEliminado=list->current->data;
  
  if(anterior){//si hay un dato anterior se apunta al siguiente del eliminado
    anterior->next = list->current->next;
  }else{//si no hay un anterior y hay un siguiente se asigna el siguiente como head
    if(siguiente){
      list->head=siguiente;
    }
  }
  if(siguiente){//si hay siguiente se apunta al anterior del eliminado
    siguiente->prev = list->current->prev;
  }else{//si no hay siguiente pero hay anterior se asigna como cola al anterior
    if(anterior){
      list->tail = anterior;
    }
  }
  
  list->current = siguiente;
  
    return datoEliminado;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}