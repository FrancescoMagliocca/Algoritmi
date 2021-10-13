#include <stdio.h>
#include <stdlib.h>
#include "../include/lib3.h"

struct _node{
  void* key;
  void* value;
  struct _node *next;
};

struct _table{
  int capacity;
  int size;
  Node** list;
  hashFunction hash;
  hashCmp compare;
};

Hashmap* hashmap_create(int capacity, hashFunction hash, hashCmp compare){	 //capicty = Map_size
  Hashmap* hm=(Hashmap*)malloc(sizeof(Hashmap));//alloca lo spazio per la hashmap
  hm->capacity=capacity;
  hm->size=0;
  hm->list=(Node**)malloc(sizeof(Node*)*capacity);//lista grossa quanto la capacità
  hm->hash=hash;
  hm->compare=compare;
  return hm;
}

void hashmap_free(Hashmap* hm){
  Node *curr, *temp;
  int i;
  for(i=0; i<hashmap_capacity(hm);i++){
  	curr=hm->list[i];
	while(hm->list[i]!=NULL){
  	  temp=hm->list[i];
	  hm->list[i]=hm->list[i]->next;
	  free(temp);
	}
  }	
  free(hm->list);
  free(hm);
  
}

int hashmap_empty(Hashmap* hm){
  if(hm->size==0)
	return 1;
  else
	return 0;
}

int hashmap_size(Hashmap* hm){
  return hm->size;
}

int hashmap_capacity(Hashmap* hm){
  return hm->capacity;
}

void hashmap_flush(Hashmap* hm){ 
  Node* temp;
  int i;
  for(i=0; i<hashmap_capacity(hm);i++){
	while(hm->list[i]){	
	  temp=hm->list[i];
	  hm->list[i]=hm->list[i]->next;
	  free(temp);
	}
  hm->size=0;
  }
}

int hashmap_contain_key(Hashmap* hm, void* key){ //compara sulla stessa chiave
  int pos=hm->hash(key);
  Node* curr=hm->list[pos];
	
  while(curr!=NULL){
  if(hm->compare(curr->key,key)==0)// se la chiave esiste ritorna 1
	return 1;
    curr=curr->next;
  }
  return 0;
}

void hashmap_insert(Hashmap* hm, void* key, void* val){
  if(hashmap_contain_key(hm, key)==0){//se la chiave non c'è
 	int pos=hm->hash(key);///inserisce la chiave e val nel nuovo nodo
	Node* list=hm->list[pos];
	Node* newnode=(Node*)malloc(sizeof(Node));
	newnode->key=key;
	newnode->value=val;
	newnode->next=list;
	hm->list[pos]=newnode;
	hm->size++;
  }
		
}

void* hashmap_get_value(Hashmap* hm, void* key){
  if(hashmap_contain_key(hm, key)==1){//se hm contiene la chiave
 	int pos=hm->hash(key);
	Node* curr=hm->list[pos];
	while(curr){
  	  if(hm->compare(curr->key, key)==0)//vedo se sono nella stessa posizione
	  return curr->value;//restituico il valore
	  curr=curr->next;
	}
  return NULL;
  }
}

void hashmap_delete_key(Hashmap* hm, void* key){
  if(hashmap_contain_key(hm,key)>0){
    int pos=hm->hash(key);
	int flag=0;
	Node* list=hm->list[pos];
	Node* prev=NULL;

	while(list!=NULL && flag){
	  if(hm->compare(list->key, key)==0){
	    if(prev==NULL){
		  Node *temp=list;
		  hm->list[pos]=list->next;
		  free(list);
		}
	    else{
	      prev->next=list->next;
		  free(list);
	    }
	    hm->size--;
	    flag=1;
	  }
	  prev=list;
	  list=list->next;
	}
  }
}

void** hashmap_get_keys(Hashmap* hm){
  void** keys=malloc(sizeof(void*)*hm->size);
  Node* current;
  int j=0;
  for(int i=0; i<hm->capacity;i++){
 	current=hm->list[i];
	while(current!=NULL){
	  keys[j++]=current->key;
	  current=current->next;
	}
  }
  return keys;
}