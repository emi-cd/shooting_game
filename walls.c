/* walls.c */

#include <string.h>
#include <walls.h>
#include <screen.h>

#define WALLLOOP 42
#define UNITS 11
#define UNITLINES  7

static int count = 0;
extern int last;


int un=1;

static char walldata[UNITS*UNITLINES][WIDTH+1] ={
  "OOOOO                             OOOOOO",
  "OOOOOO       O          O        OOOOOOO",
  "OOOOOO      OOO        OOO       OOOOOOO",
  "OOOOOO     OOOO       OOOOO      OOOOOOO",
  "OOOOOO      OOO       OOOO      OOOOOOOO",
  "OOOOOOO      OO        O       OOOOOOOOO",
  "OOOOOOOO                      OOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOOOOOO                  OOOOOOOOOOOO",
  "OOOOOOOOO                  OOOOOOOOOOOOO",
  "OOOOOOO                   OOOOOOOOOOOOOO",
  "OOOO                     OOOOOOOOOOOOOOO",
  "OOO                     OOOOOOOOOOOOOOOO",
  "OOO                   OOOOOOOOOOOOOOOOOO",
  "OO                   OOOOOOOOOOOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  "OO                    OOOOOOOOOOOOOOOOOO",
  "OOO                   OOOOOOOOOOOOOOOOOO",
  "OOO                    OOOOOOOOOOOOOOOOO",
  "OOOO                     OOOOOOOOOOOOOOO",
  "OOOOOOO                    OOOOOOOOOOOOO",
  "OOOOOOOOO                    OOOOOOOOOOO",
  "OOOOOOOOOOO                   OOOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOOOOOOOOOO                 OOOOOOOOO",
  "OOOOOOOOOOOOOOOO                OOOOOOOO",
  "OOOOOOOOOOOOOOOOOO               OOOOOOO",
  "OOOOOOOOOOOOOOOOOOOO              OOOOOO",
  "OOOOOOOOOOOOOOOOOOOOO               OOOO",
  "OOOOOOOOOOOOOOOOOOOOOO               OOO",
  "OOOOOOOOOOOOOOOOOOOOOOO               OO",
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOOOOOOOOOOOOOOOOO                 OO",
  "OOOOOOOOOOOOOOOOOOOO                 OOO",
  "OOOOOOOOOOOOOOOOOOO                 OOOO",
  "OOOOOOOOOOOOOOOOO                  OOOOO",
  "OOOOOOOOOOOOOO                    OOOOOO",
  "OOOOOOOOOOOO                    OOOOOOOO",
  "OOOOOOOOO                      OOOOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOOO            OOOOO        OOOOOOOO",   
  "OOOOOO          OOOOOOOOOO        OOOOOO",
  "OOOOOO         OOOOOOOOOOOO        OOOOO",
  "OOOOOO         OOOOOOOOOOOO          OOO",   
  "OOOOOOO        OOOOOOOOOOO          OOOO",   
  "OOOOOOO         OOOOOOOOO         OOOOOO",   
  "OOOOOOOO          OOOOO          OOOOOOO",   
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOO                            OOOOOO",   
  "OOOOO       OO            OO       OOOOO",   
  "OOOO       OOO     OO     OOO       OOOO",   
  "OOOO        O     OOOO     O        OOOO",   
  "OOOOO              OO              OOOOO",   
  "OOOOO                              OOOOO",   
  "OOOOO                              OOOOO",   
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOO                              OOOOO",   
  "OOOOO                              OOOOO",   
  "OOOOO      O                O      OOOOO",   
  "OOOOO      O    OO    OO    O      OOOOO",   
  "OOOOO       O   O      O   O       OOOOO",   
  "OOOOOO                            OOOOOO",   
  "OOOOOOO                          OOOOOOO",   
  /*   ,    |    ,    |    ,    |    ,    */
  "*         *         *         *    *    ",
  "    *                   *              *",
  "       *         *         *            ",
  "              *                   *    *",
  "  *                *                 *  ",
  "     *      *          *     *          ",
  "                  GOAL                  ",
  /*   ,    |    ,    |    ,    |    ,    */
  "                                        ",
  "                                        ",
  "                                        ",
  "               GAME OVER                ",
  "                                        ",
  "                                        ",
  "                                        ",
  /*   ,    |    ,    |    ,    |    ,    */
  "OOOOOOOO                       OOOOOOOOO",
  "OOOOOO          OOOOO           OOOOOOOO",
  "OOOOO                            OOOOOOO",
  "OOOOO                            OOOOOOO",
  "OOOOO                            OOOOOOO",
  "OOOOO                            OOOOOOO",
  "OOOOO                            OOOOOOO",
  /*   ,    |    ,    |    ,    |    ,    */
};

static char collisioncheckdata[UNITS*UNITLINES][WIDTH];

static int wallorder[WALLLOOP] ={
  0,1,2,3,4, 10,5,6,7,6, 7,0,1,2,3, 4,5,6,7,6,
  7,0,1,2,1, 2,7,6,7,6, 10,7,0,3,4, 3,4,5,5,5,
  0,5,
};


void initwalls(void){
  int i,j;
  for(i=0;i<UNITS*UNITLINES;i++){
    for(j=0;j<WIDTH;j++){
      if(walldata[i][j] ==' '){ 
        collisioncheckdata[i][j] = NONOBJ;//non object
      }else{
        collisioncheckdata[i][j] = WALL;//wall
      }
    }
  }
}

void scrollwall(void){
  count++;
}

void putwalls(int lines){
  int unit,lline;
  int i,j;
  static int h=0;
  h++;
  if(h>=1500){
    h = 0;
    un = 1;
  }
  for (i=lines;i>0;i--){
    unit = ((count+i) / UNITLINES) % WALLLOOP; 
    lline = ((count+i) % UNITLINES); 
    putlife(wallorder[unit]);
    for(j=0;j<WIDTH;j++){
      putdata(j,lines-i,walldata[wallorder[unit]*UNITLINES+lline][j],
              collisioncheckdata[wallorder[unit]*UNITLINES+lline][j]);
    }
  }
  for(j=0;j<WIDTH;j++){
    putdata(j,0,'+',BORDER);
    putdata(j,lines-1,'+',BORDER);
  }            
  for(j=0;j<lines;j++){
    putdata(0,j,'+',BORDER);
    putdata(WIDTH-1,j,'+',BORDER);
  }            
}

void putlast(int h,int lines,int num){
  int lline,row;
  int i,j;
  if(h==1){
    for (i=lines;i>0;i--){ 
      lline = ((last+i) % (UNITLINES-1)); 
      for(j=0;j<WIDTH;j++){
	putdata(j,lines-i,walldata[num*UNITLINES+lline][j],'G');
	if(i==25){
	  putdata(j,lines-i,walldata[num*UNITLINES+UNITLINES-1][j],'G');
	}
      }
    }
  }
  else if(h==2){
    for(j=0;j<WIDTH;j++){ 
      row = ((last+j) % (SCREENWIDTH-1));
      for (i=lines;i>0;i--){
	lline = (i % (UNITLINES-1));
	putdata(j,lines-i,walldata[num*UNITLINES+lline][row],'G');
      } 
    }
  }
  
  for(j=0;j<WIDTH;j++){
    putdata(j,0,'+',BORDER);
    putdata(j,lines-1,'+',BORDER);
  }            
  for(j=0;j<lines;j++){
    putdata(0,j,'+',BORDER);
    putdata(WIDTH-1,j,'+',BORDER);
  }            
}

void putlife(int order){
  if(order==10&&un==1){
    walldata[10*UNITLINES+3][18]='L';
    collisioncheckdata[10*UNITLINES+3][18]=LIFE;
  }
}

void deleatlife(void){
  walldata[10*UNITLINES+3][18]=' ';
  collisioncheckdata[10*UNITLINES+3][18]=NONOBJ;
  un = 0;
}

