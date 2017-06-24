/* scenario.c */
#include<scenario.h>
#include<bidlist.h>
#include<stdio.h>
#include<string.h>

static bidlist* scenario;
static int mark;

void initscenario(void){
  scenario = newbidlist();
  mark = 0;
} 

void addevent(event* ev){
  bidlistadd(scenario, ev);
}

void resetmark(void){
  bidlistreset(scenario); 
  mark = 0;
}

int getcurrentmark(void){
  return mark;
}

void setmark(int pos){
  int cnt = bidlistcount(scenario);
  if(pos<cnt){
    mark = pos;
    bidlistsetmark(scenario, bidlistget(scenario, mark)); 
  }else{
    mark = cnt;
    bidlistsetmark(scenario, scenario->tail); 
  }
}

event* getnextevent(void){
  event* ret = NULL;

  if(!strcmp(((event*)(scenario->mark->data))->name,"dummy")){
    setmark(1);
  }

  bidnode* node = bidlistnext(scenario);
  bidnode* prev = node ->prev;
  if(node != NULL){
    if(prev != NULL)
      ((event*)(prev->data))->time += 150;
    ret = (event*)(node->data);
  }
  return ret;
}
