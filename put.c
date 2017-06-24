/*put.c */
#include<gameio.h>
#include<screen.h>
#include<ncurses.h>

void putscore(int score){
  int i=score/1000;
  gameioput(SCREENWIDTH+3,1,'S');//スコア1を表示
  gameioput(SCREENWIDTH+4,1,'C');
  gameioput(SCREENWIDTH+5,1,'O');
  gameioput(SCREENWIDTH+6,1,'R');
  gameioput(SCREENWIDTH+7,1,'E');
  gameioput(SCREENWIDTH+9,1,'0'+(int)i);
  i=score%1000;
  gameioput(SCREENWIDTH+10,1,'0'+(int)i/100);
  i=i%100;
  gameioput(SCREENWIDTH+11,1,'0'+(int)i/10);
  i=i%10;
  gameioput(SCREENWIDTH+12,1,'0'+(int)i);
}

void putspeedlevel(int speed){
  gameioput(SCREENWIDTH+3,5,'S');
  gameioput(SCREENWIDTH+4,5,'P');
  gameioput(SCREENWIDTH+5,5,'E');
  gameioput(SCREENWIDTH+6,5,'E');
  gameioput(SCREENWIDTH+7,5,'D');
  gameioput(SCREENWIDTH+9,5,'0'+(int)speed/10);
  gameioput(SCREENWIDTH+10,5,'0'+(int)speed%10);
}

void putbullet(int bullet){
  gameioput(SCREENWIDTH+3,7,'b');
  gameioput(SCREENWIDTH+4,7,'u');
  gameioput(SCREENWIDTH+5,7,'l');
  gameioput(SCREENWIDTH+6,7,'l');
  gameioput(SCREENWIDTH+7,7,'e');
  gameioput(SCREENWIDTH+8,7,'t');
  gameioput(SCREENWIDTH+10,7,'0'+(int)bullet/10);
  gameioput(SCREENWIDTH+11,7,'0'+(int)bullet%10);
}

void guide(void){
  int a;
  initscr();
  printw("GUIDE\n");
  printw("Speed up each 50 lines. GOAL is 10000!\n");
  printw("\nRULE\n");
  printw("Finalscore is \"basic score\" + \"bonus score\".\nEnemy:\tThere are 3 type of enemy. If you nock down enemy, you can get point.\n\tOne is 200point, the other is 300point.\n");
  printw("LIFE:\tAt first, your life is 2.\n");
  printw("\nITEM\n");
  printw("B \tFill bullet\n");
  printw("D \tSpeed down\n");
  printw("L \tLIFE\n");
  printw("\nHow to operate\nF or f\tright\nB or b\tleft\nP or p\tup\nN or n\tdown\n");
  printw("'space'\tshoot a bullet\nw or W \tshoot many bullets.\n");
  printw("\nPlease put 's'!\nGAME START!\n");
  while(1){
    a=getch();
    if('s'== a||'S'==a){
      endwin();
      return;
    }
  }
}
