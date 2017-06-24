/* event.c */
#include<stdio.h>
#include<stdlib.h>
#include<event.h>
#include<content.h>

event* newevent(int time, vector2 pos, vector2 vel,
                movingobject* mobj, char* name){
  event* ret = (event*) malloc(sizeof(event));
  ret->gene.print = printevent;
  ret->time = time;
  ret->pos = pos;
  ret->vel = vel;
  ret->mobj = mobj;
  ret->name =  name;
  return ret;
}

void printevent(content* con){
  printf("%07d,",con->ev->time);
  printf("%f, %f, ",con->ev->pos.x, con->ev->pos.y);
  printf("%f, %f, ",con->ev->vel.x, con->ev->vel.y);
  printf("%s\n",con->ev->name);
}
