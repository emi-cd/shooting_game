/* object.h */
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include<vector2.h>

typedef struct object{
  vector2 size;
  char* shape;
} object;

object* newobject(int w, int h, char* shape);
void deleteobject(object* obj); 
void putobject(object* obj, int id, int x, int y);
#endif
