/* gamemain.c */
#include<screen.h>
#include<gameio.h>
#include<walls.h>
#include<stdio.h>
#include<object.h>
#include<movingobject.h>
#ifdef DEBUG
#include<log.h>
#endif

#define OBJNUM 1
#define MOBJNUM 1

object* objp[OBJNUM];
movingobject* mobjp[MOBJNUM];
vector2 mypos;
int isfire;
int score;


void initobjects(void){
  objp[0] = newobject(3,2," ^ =x=");
}

void initmovingobjects(void){
  mobjp[0] = newmovingobject(&objp[0], NULL, NULL, NULL, "me");
}

void dispm(movingobject* mobj){
  putobject(*(mobj->obj), 0, mobj->pos.x, mobj->pos.y);
}

void init(void){
  initscreen();
  initwalls();
  initobjects();
  initmovingobjects();
}

void getstate(vector2* ret, int* isfire){
  static vector2 pos = {SCREENWIDTH/2-1, SCREENHEIGHT-3}; 
  *isfire = 0;
  int in = gameioread();
  switch(in){
  case 'f':
  case 'F':
    pos.x++;
    break;
  case 'b':
  case 'B':
    pos.x--;
    break;
  case 'p':
  case 'P':
    pos.y--;
    break;
  case 'n':
  case 'N':
    pos.y++;
    break;
  case ' ':
    *isfire = 1;
  } 
  *ret = pos;
}

void show(void){
  int x,y;
  for(y=0;y<SCREENHEIGHT;y++){
    for(x=0;x<SCREENWIDTH;x++){
      gameioput(x,y,dispbuffer[SCREENWIDTH*y+x]);
    }
  }
  gameiorefresh();
}

void gameloop(void){
  int speedlevel = 16; 
  int time=0;
  vector2 tmpv;
  while(1){
    gameiousleep(30000);
    if(time%speedlevel == 0){
      scrollwall();
      score++;
    }
    getstate(&mypos, &isfire);
    gameioput(SCREENWIDTH+3,1,'0'+(int)mypos.x/10);
    gameioput(SCREENWIDTH+4,1,'0'+(int)mypos.x%10);
    gameioput(SCREENWIDTH+6,1,'0'+(int)mypos.y/10);
    gameioput(SCREENWIDTH+7,1,'0'+(int)mypos.y%10);
    putwalls(SCREENHEIGHT);
    if(checkcollision(mypos, objp[0])!=NONOBJ){
      break;
    }
    mobjp[0]->pos = mypos;
    dispm(mobjp[0]);
    show();
    time++;
  }
}

int main(void){
  gameioinit();
  gameioclear();
  init();
  
  score=0;
  gameloop();

  gameiopost();
  printf("score %d\n",score);
  return 0;
}
