/* object.c */
#include<string.h>
#include<stdlib.h>
#include<screen.h>
#include<object.h>

object* newobject(int w, int h, char* shape){
  int i;
  char* tmp;
  object* ret = (object*)malloc(sizeof(object));
  ret->size.x = w;
  ret->size.y = h;
  ret->shape = (char*)malloc(sizeof(char)*w*h);
  strncpy(ret->shape, shape, w*h);
  return ret;
}

void deleteobject(object* obj){
  free(obj->shape);
  free(obj);
}

void putobject(object* obj, int id, int x, int y){
  int i,j;
  int w = obj->size.x;
  int h = obj->size.y;
  for(i=0;i<h;i++){
    for(j=0;j<w;j++){
      if(obj->shape[i*w+j] != ' '){ 
        putdata(x+j, y+i, obj->shape[i*w+j],(unsigned char)id);
      }
    }
  }
}
