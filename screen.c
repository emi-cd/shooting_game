/* screen.c */

#include<stdlib.h>
#include<screen.h>
#include<vector2.h>
#include<object.h>

const unsigned char NONOBJ = 255;
const unsigned char WALL = 254;
const unsigned char BORDER = 253;
const unsigned char LIFE = 252;

unsigned char* dispbuffer; 
unsigned char* checkbuffer;

void initscreen(void){
  dispbuffer = (unsigned char*)malloc(sizeof(unsigned char)*
                             SCREENWIDTH*SCREENHEIGHT);
  checkbuffer = (unsigned char*)malloc(sizeof(unsigned char)*
                                       SCREENWIDTH*SCREENHEIGHT);
  
}

void putdata(int x, int y, unsigned char d, unsigned char c){
  if(0<=x&&x<SCREENWIDTH && 0<=y && y<SCREENHEIGHT){ 
    dispbuffer[SCREENWIDTH*y+x]=d;
    checkbuffer[SCREENWIDTH*y+x]=c;
  }
}

unsigned char checkcollision(vector2 pos, object* obj){
  int x,y;
  unsigned char id;
  for(y=0;y<obj->size.y;y++){
    for(x=0;x<obj->size.x;x++){
      if(obj->shape[(int)(obj->size.x)*y+x] !=' '){
        id = checkbuffer[SCREENWIDTH*((int)(pos.y)+y)+(int)(pos.x)+x];
        if(id !=NONOBJ){
          return id;
        }
      }
    }
  }
  return NONOBJ;
}
