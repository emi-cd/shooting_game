/* bidlist.c */
#include<bidlist.h>
#include<stdio.h>
#include<stdlib.h>

bidlist* newbidlist(void){
  bidlist* ret = (bidlist*)malloc(sizeof(bidlist));
  ret->head = NULL;
  ret->tail = NULL;
  ret->mark = NULL;
  ret->count =0;
  return ret;
}

int bidlistadd(bidlist* blist, void* data){
  bidnode* newnode = (bidnode*)malloc(sizeof(bidnode));
  newnode->data = data; 
  newnode->prev = blist->tail; 
  newnode->next = NULL;
  if(blist->tail != NULL){
    blist->tail->next = newnode;
  }    
  blist->tail = newnode;
  if(blist->head == NULL){
    blist->head = newnode;
  }
  blist->count++;
  return blist->count;
}

int bidlistremove(bidlist* blist, bidnode* node){
  bidnode* prev = node->prev;
  bidnode* next = node->next;
  if(blist->mark == node){
    blist->mark = node->next;
  }
  if(next!= NULL){
    next->prev = prev;
  }else{
    blist->tail = prev;
  }
  if(prev!= NULL){
    prev->next = next;
  }else{
    blist->head = next;
  }
  free(node);
  blist->count--;
  return blist->count;
}

int bidlistcount(bidlist* blist){
  return blist->count;
}

bidnode* bidlistget(bidlist* blist, int num){
  int i;
  bidnode* point = blist->head;
  for(i=0;i<num;i++){
    point = point->next;
  }
  return point;
}

void bidlistreset(bidlist* blist){
  blist->mark = blist-> head;
}

bidnode* bidlistnext(bidlist* blist){
  bidnode* ret = blist->mark;
  if(ret != NULL){
    blist->mark = blist->mark->next;
  }
  return ret;
}

bidnode* bidlistsetmark(bidlist* blist, bidnode* node){
  blist->mark = node;
  return node;
}
