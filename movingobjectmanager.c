/* movingobjectmanager.c */
#include<movingobjectmanager.h>
#include<screen.h>
#include<bidlist.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ncurses.h>
#ifdef DEBUG
#include<log.h>
#endif


extern int score;
static bidlist* objlist;
static bidnode* nodes[MAXOBJCNT];
static int count=0;
extern int bullet;
extern int speedlevel; 
extern int life;

void initmom(void){
  objlist = newbidlist();
}

void addmo(movingobject* mobj, vector2 pos, vector2 vel){
  movingobject* tmp;
  if(count<MAXOBJCNT){
    tmp = (movingobject*)malloc(sizeof(movingobject));
    *tmp = *mobj;
    tmp->pos = pos;
    tmp->vel = vel;
    bidlistadd(objlist,tmp);
    count++;
  }
} 

/* call just after putmo */
void removemo(int num){
  count--;
  deletemovingobject(nodes[num]->data);
  bidlistremove(objlist,nodes[num]);
}

/* put objects on dispbuffer and checkbuffer */
void putmo(void){ 
  movingobject* mobj;
  bidnode* node;
  int num=0;
  int id,i,j=0;
  int check[MAXOBJCNT+1] = {};
  bidlistreset(objlist);
  while((node = bidlistnext(objlist))){
    nodes[num] = node;
    mobj =(movingobject*)(node->data);
    mobj->id = num;
    id = checkcollision(mobj->pos, mobj->currentobj);
    if(id == BORDER){
      removemo(num);
    }else if(id<MAXOBJCNT){
      if(!strcmp(((movingobject*)(nodes[id]->data))->name,mobj->name)){
	putmovingobject(mobj);
	num++;
      }else{
	if(mobj->bomb(mobj)){
	  beep();
	  for(i=0;i<MAXOBJCNT;i++){
	    if(i == j){
	      check[i] = num;
	      j = i + 1;
	      break;
	    }
	    if(num==check[i])
	      break;
	  }
	}
	if(((movingobject*)(nodes[id]->data))
	   ->bomb((movingobject*)(nodes[id]->data))){
	  beep();
	  for(i=0;i<MAXOBJCNT;i++){
	    if(i == j){
	      check[i] = id;
	      j = i + 1;
	      break;
	    }
	    if(id==check[i])
	      break;
	  }
	}
      }
    }else{
      putmovingobject(mobj);
      num++;
    }
  }
  i=0;
  while(j>0){
    removemo(check[i]);
    j--;
    i++;
  }
}


void movingitem(int num){
  movingobject* mobj = nodes[num]->data;
  if(!strcmp(mobj->currentobj->shape,"B")){
    bullet +=15;  
    removemo(num);
    life++;
    if(bullet>=100)
      bullet = 99;
  }
  if(!strcmp(mobj->currentobj->shape,"D")){
    speedlevel +=2;
    removemo(num);
    life++;
    }
}


/* put objects on dispbuffer and checkbuffer */
void onestepmo(void){
  movingobject* mobj;
  bidnode* node;
  int num=0;
  bidlistreset(objlist);
  while((node = bidlistnext(objlist))){
    mobj = (node->data);
    mobj->onestep(mobj);
  }
}
