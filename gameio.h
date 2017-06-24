/* gameio.h */

#ifndef _GAME_IO_H_
#define _GAME_IO_H_

/* store terminal environment 
   This have to be called before
   other functions in this file!! */
void gameioinit(void);

/* read one character from keyboard */ 
int gameioread(void);

/* recover terminal environment
   This have to be called before 
   the end of your program!! */
void gameiopost(void);

/* clear terminal */
void gameioclear(void);

/* refresh terminal */
void gameiorefresh(void);

/* put character ch at x,y  */
void gameioput(int x, int y, char ch);

/* sleep t microseconds */
void gameiousleep(int t);

void colorinit(void);

#endif

