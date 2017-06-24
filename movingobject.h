/* movingobject.h */
#ifndef _MOVINGOBJECT_H_
#define _MOVINGOBJECT_H_
#include<object.h>

typedef struct movingobject{
  vector2 pos;
  vector2 vel;
  int flag;
  int cnt;
  int id;
  void (*onestep)(struct movingobject* obj);
  void (*display)(struct movingobject* obj);
  int (*bomb)(struct movingobject* obj);
  char* name; 
  object** obj;
  object* currentobj;
  int kind;
} movingobject;

movingobject* newmovingobject(object** shape, 
                              void(*onestep)(movingobject* obj),
                              void(*display)(movingobject* obj), 
                              int(*bomb)(movingobject* obj), 
                              char* name);
void deletemovingobject(movingobject* mobj);
void setinitposition(movingobject* mobj, vector2 pos);
void putmovingobject(movingobject* mobj); 

#endif
