/* log.c */
#include<log.h>

FILE* logp;

void initlog(void){
  logp = fopen("log.txt","r");
}
void initlogw(void){
  logp = fopen("log.txt","w");
}

int closelog(void){
  return fclose(logp);
}

void logscore(int score){
  int rank[6],i=0,j,k,a;
  char tmp[256];
  initlog();
  while(fgets(tmp,256,logp)){
    k = atoi(tmp);
    rank[i] = k;
    i++;
  }
  rank[5] = score;
  closelog();
  
  for(i=0;i<5;i++){
    for(j=i;j<6;j++){
      if(rank[i]<rank[j]){
	k = rank[i];
	rank[i] = rank[j];
	rank[j] = k;
      }
    }
  }
  
  initlogw();
  for(i=0;i<5;i++)
    fprintf(logp,"%d\n",rank[i]);
  closelog();

  gameioclear();
  printw("\nYOUR SCORE:%d\n",score);
  printw("\nRANKING\n");
  for(i=0;i<5;i++)
    printw("%d:%d\n",i+1,rank[i]);
  printw("\nPut return\n");

  while(1){
    a=getch();
    if('\n'== a){
      gameiopost();
      return;
    }
  }


}

