/* walls.h */

#ifndef _GAME_WALLS_H_
#define _GAME_WALLS_H_

#define WIDTH 40



void initwalls(void);
void putwalls(int lines);
void scrollwall(void);
void putlast(int h,int lines,int num);
void putlife(int order);
void deleatlife(void);

#endif /* _GAME_WALLS_H_ */

