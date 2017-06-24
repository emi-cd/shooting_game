/* enemy40.c */
#include<movingobject.h>
#include<enemy.h>
#include<movingobjectmanager.h>
#include<object.h>
#include<math.h>
#include<string.h>
#include<vector2.h>
#include<stdio.h>
#include<object.h>

static object* objp[4];
extern int score;
extern void makeshot(vector2 pos);


static void onesteppm(movingobject* mobj){
  vector2 tmpv;
  if(mobj->kind==1){
    mobj->pos.x = mobj->pos.x + sin(M_PI/180.0*(mobj->cnt))/2;
    mobj->pos.y = mobj->pos.y + mobj->vel.y; 
  }else if(mobj->kind==2){
    mobj->pos.x = mobj->pos.x + sin(M_PI/180.0*(mobj->cnt))/2;
    mobj->pos.y = mobj->pos.y + cos(M_PI/180.0*(mobj->cnt))/2; 
  }else{
    mobj->pos.x =  mobj->pos.x + (cos((mobj->cnt)*M_PI/180.0) + 
				  ((mobj->cnt)*M_PI/180.0)*sin((mobj->cnt)*M_PI/180.0))/40;
    mobj->pos.y =  mobj->pos.y + (cos((mobj->cnt)*M_PI/180.0) - 
				  ((mobj->cnt)*M_PI/180.0)*sin((mobj->cnt)*M_PI/180.0))/40;
    if(mobj->cnt == 360){
      tmpv = mobj->pos;
      tmpv.x +=2;
      tmpv.y +=4;
      makeshot(tmpv);     
    } 
  }
  mobj->cnt = (mobj->cnt + 10) % 720;
}

static void dispa(movingobject* mobj){
int l;
 if((mobj->cnt)/90%4){
   l = 3-mobj->flag;
   if(mobj->kind==2)
     l = 2; 
 }
 else
   l = 3;
 mobj->currentobj = (mobj->obj)[l];
 putobject(mobj->currentobj, mobj->id, mobj->pos.x, mobj->pos.y);
}

static int bomba(movingobject* mobj){
  if(!strcmp(mobj->name,"bullet"))
    return 1;
  else{
    mobj->flag--;
    if((mobj->flag)<=0||mobj->kind==2){
      score += 300;
      return 1;
    }else{
      score +=300;
      return 0;
    }
  }
}

movingobject* newenemy40(void){
  objp[0] = newobject(3,3," : :3: : ");
  objp[1] = newobject(3,3," : :2: : ");
  objp[2] = newobject(3,3," : ::: : ");
  objp[3] = newobject(1,3,":*:");
  return newmovingobject(&objp[0], onesteppm, dispa, bomba, "enemy");
}
