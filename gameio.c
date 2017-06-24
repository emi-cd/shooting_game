/* gameio.c */

#include<stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <ncurses.h>

static WINDOW *win;

static void signal_handler(int unused)
{
  printf("handler\n");
  endwin();
  exit(EXIT_SUCCESS);
}

static void set_signalhandlers(void)
{
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);
    signal(SIGILL, signal_handler);
    signal(SIGTERM,signal_handler);
    signal(SIGQUIT,signal_handler);
}


void gameioinit(void){
  set_signalhandlers();
  win = initscr();
  nodelay(win,TRUE);
  cbreak();
  noecho();
}

int gameioread(){
  int ret = getch();
  if (ret <=0){
    return 0;
  }else{
    return ret;
  }
}

void gameiopost(void){
  nocbreak();
  echo();
  endwin();
}

void gameioclear(){
  clear();
}

void gameiorefresh(void){
  refresh();
}

void gameioput(int x, int y, char ch){
  mvaddch(y,x,ch);
}


void gameiousleep(int t){
  usleep(t);
}
