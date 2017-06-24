/* event.h */
#ifndef _EVENT_H_
#define _EVENT_H_

#include<vector2.h>
#include<movingobject.h>
#include<content.h>

typedef struct event{
  struct general gene;
  int time;
  vector2 pos;
  vector2 vel;
  movingobject* mobj;
  char* name;
} event;

event* newevent(int time, vector2 pos, vector2 vel, 
                movingobject* mobj, char* name);
#endif
