/* screen.h */
#ifndef _SCREEN_H_
#define _SCREEN_H_

#include<vector2.h>
#include<object.h>

#define SCREENWIDTH 40
#define SCREENHEIGHT 40

extern unsigned char* dispbuffer;
extern unsigned char* checkbuffer;

extern const unsigned char NONOBJ;
extern const unsigned char WALL;
extern const unsigned char BORDER;
extern const unsigned char LIFE;

void initscreen(void);
void putdata(int x, int y, unsigned char d, unsigned char c);
unsigned char checkcollision(vector2 pos, object* obj);


#endif
