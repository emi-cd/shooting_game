/* gamemain2.c */
#include<math.h>
#include<scenario.h>
#include<screen.h>
#include<gameio.h>
#include<walls.h>
#include<stdio.h>
#include<enemy.h>
#include<enemy40.h>
#include<string.h>
#include<movingobjectmanager.h>
#include<log.h>
#include<put.h>
#ifdef DEBUG
#endif

#define OBJNUM 6
#define MOBJNUM 8
#define EVNUM 11
#define GOAL 10000
#define SPEED 16
#define BULLET 60;

object* objp[OBJNUM];
movingobject* mobjp[MOBJNUM];
event* ev[EVNUM];
vector2 mypos;
int isfire;
int isfire2;
int score;
int life = 2;
int last=0;
int counter=0;
int time=0,bullet=BULLET;
int speedlevel = SPEED; 

void onestepb(movingobject* mobj){
  vec2add(&(mobj->pos), &(mobj->vel));
}

void onestepi(movingobject* mobj){
  mobj->pos.x = mobj->pos.x + sin(M_PI/180.0*(mobj->cnt))/2;
  mobj->pos.y = mobj->pos.y + cos(M_PI/180.0*(mobj->cnt))/2 + 0.1; 
  mobj->cnt = (mobj->cnt + 3) % 720;
}

void dispb(movingobject* mobj){
  putobject(*(mobj->obj), mobj->id, mobj->pos.x, mobj->pos.y);
}

void dispm(movingobject* mobj){
  putobject(*(mobj->obj), 0, mobj->pos.x, mobj->pos.y);
}

int bomba(movingobject* mobj){
return 1;
}

void initobjects(void){
  objp[0] = newobject(1,1,"x");
  if(life==1)
    objp[1] = newobject(3,2," ^ =x=");
  else if(life==2)
    objp[1] = newobject(3,2," ^ =2=");
  else
    objp[1] = newobject(3,2," ^ =3=");
  objp[2] = newobject(1,1,"B");
  objp[3] = newobject(1,1,"D");
  objp[4] = newobject(2,1,"++");
}

void initmovingobjects(void){
  mobjp[0] = newenemy();
  mobjp[1] = newmovingobject(&objp[0], onestepb, dispb, bomba, "bullet");
  mobjp[2] = newmovingobject(&objp[1], NULL, dispm, NULL, "me");
  mobjp[3] = newenemy40();//連続して呼び出すことで違う敵が出現
  mobjp[4] = newenemy40();//
  mobjp[5] = newenemy40();
  mobjp[6] = newmovingobject(&objp[2], onestepi, dispb, bomba, "enemy");//弾
  mobjp[7] = newmovingobject(&objp[3], onestepi, dispb, bomba, "enemy");//スピードダウン
}

void makeshot(vector2 pos){
  movingobject* mobjp;
  mobjp = newmovingobject(&objp[4], onestepb, dispb, bomba, "enemy");
  addmo(mobjp,pos,makevector2(0,0.3));
}

void setevents(void){
  int i;
  ev[0] = newevent(10, makevector2(20,6),makevector2(0,0.2), mobjp[0],"plus0");
  ev[1] = newevent(25, makevector2(15,4),makevector2(0,0.1), mobjp[4],"plus1");
  ev[2] = newevent(40, makevector2(5,4),makevector2(0,0.1), mobjp[3],"plus2");
  ev[3] = newevent(55, makevector2(12,10),makevector2(0,0.1), mobjp[7],"item");
  ev[4] = newevent(70, makevector2(7,5),makevector2(0,0.2), mobjp[5],"plus3");
  ev[5] = newevent(85, makevector2(10,8),makevector2(0,0.1), mobjp[6],"item");
  ev[6] = newevent(100, makevector2(18,3),makevector2(0,0.3), mobjp[0],"plus4");
  ev[7] = newevent(115, makevector2(25,5),makevector2(0,0.1), mobjp[4],"plus5");
  ev[8] = newevent(130, makevector2(8,6),makevector2(0,0.2), mobjp[3],"plus6");
  ev[9] = newevent(145, makevector2(20,4),makevector2(0,0.2), mobjp[5],"plus7"); 
  ev[10] = newevent(1000000, 
                   makevector2(30,1),makevector2(0,1), mobjp[0],"dummy");
  for(i=0;i<EVNUM;i++){
    addevent(ev[i]);
  }
  resetmark();
}

void init(void){
  initscreen();
  initwalls();
  initmom();
  initobjects();
  initmovingobjects();
  initscenario();
  setevents();
}


void getstate(vector2* ret, int* isfire,int* isfire2){
  static vector2 pos = {SCREENWIDTH/2-1, SCREENHEIGHT-3}; 
  *isfire = 0;
  *isfire2 = 0;
  int in = gameioread();
  int pose = 0;
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
  case 's':
  case 'S':
    while(1){
      pose = gameioread();
      if(pose == 's'||pose=='S')
	break;
    }
    break;
  case ' ':
    *isfire = 1;
    break;
  case 'w':
  case 'W':
    *isfire2 = 1;
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
  int num=0,i=0,id;
  int j,k;
  vector2 tmpv;
  event* e = getnextevent();
  while(1){
    gameiousleep(30000);
    if(time%speedlevel == 0){
      scrollwall();
      if(counter%30==0){           //スピードレベルの調整30進むごとに1早くなる。
	speedlevel--;
	if(speedlevel<=0)
	  speedlevel = 1;
      }
      counter++;
      if((SPEED-speedlevel)<=0){    //スピードに合わせてスコアの増え方調整
	i=5;
      }else{
       	i=SPEED-speedlevel+4;
      }
      score=score+i; 
      while(e!= NULL && e->time*speedlevel < time){
        addmo(e->mobj, e->pos, e->vel);
        e = getnextevent();
      }
    }
    getstate(&mypos, &isfire,&isfire2);
    gameioput(SCREENWIDTH+3,3,'P');
    gameioput(SCREENWIDTH+4,3,'O');
    gameioput(SCREENWIDTH+5,3,'S');
    gameioput(SCREENWIDTH+7,3,'0'+(int)mypos.x/10);
    gameioput(SCREENWIDTH+8,3,'0'+(int)mypos.x%10);
    gameioput(SCREENWIDTH+10,3,'0'+(int)mypos.y/10);
    gameioput(SCREENWIDTH+11,3,'0'+(int)mypos.y%10);
    putwalls(SCREENHEIGHT);
    putscore(score);
    putspeedlevel(speedlevel);
    putmo();
    onestepmo();
    if(score>=GOAL){
      score=GOAL;
      break;
    }
    id=checkcollision(mypos, objp[1]);
    if(id == LIFE){
      life++;
      if(life>3){
	life = 3;
	score = score + 500;
      }
      deleatlife();
    }
    else if((id!=NONOBJ)&&num<(time/speedlevel)){
      if(id<MAXOBJCNT)
	movingitem(id);
      life--;
      if(life<=0){
	break;
      }
      num = time / speedlevel + 1;
    }
    if(isfire||isfire2){
      if(bullet>0){
      bullet--;
	tmpv = mypos;
	tmpv.y -=2;
	tmpv.x +=1;
	addmo(mobjp[1], tmpv, makevector2(0,-1));
	if(isfire2){
	  bullet -=7;
	  tmpv.x--;
	  addmo(mobjp[1], tmpv, makevector2(1.5,-1));
	  tmpv.x +=2;
	  addmo(mobjp[1], tmpv, makevector2(-1.5,-1));
	  tmpv.y +=4;
	  addmo(mobjp[1], tmpv, makevector2(1.5,1));
	  tmpv.x--;
	  addmo(mobjp[1], tmpv, makevector2(0,1));
	  tmpv.x--;
	  addmo(mobjp[1], tmpv, makevector2(-1.5,1));
	  tmpv.y -=1;
	  tmpv.x--;
	  addmo(mobjp[1], tmpv, makevector2(-1.5,0));
	  tmpv.x +=4;
	  addmo(mobjp[1], tmpv, makevector2(1.5,0));
	}
	  if(bullet<=0)
	    bullet=0;
      }
    }
    putbullet(bullet);
    initobjects();
    mobjp[2]->pos = mypos;
    dispm(mobjp[2]);
    show();
    time++;
  }
}


  
void goal(void){
  while(last<200){
    gameiousleep(30000);
    if(last%10==0){
      putlast(1,SCREENHEIGHT,8);//1=GOAL,8=LASTUNIT
      show();
    }
    last++;  
  }
}

void gameover(void){
  while(last<150){
    gameiousleep(20000);
    if(last%10==0){
      putlast(2,SCREENHEIGHT,9);//2=GAMEOVER
      show();
    }
    last++;    
  }
  }

int main(void){
  guide();
  gameioinit();
  gameioclear();
  init();
  score=0;
  gameloop();

  if(score>=GOAL){
    goal();
    if((6000-time)>=0)
      score += (6000-time)*2;
    score += bullet*2;
  }
  else
    gameover();
  logscore(score);
  printf("score %d\n",score);
  
  return 0;
}
