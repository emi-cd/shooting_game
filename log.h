/* log.h */
#ifndef _LOG_H_
#define _LOG_H_

#include<stdio.h>
#include<stdlib.h>
#include<gameio.h>
#include<ncurses.h>

extern FILE* logp;
void initlog(void);
int closelog(void);
void initlogw(void);
void logscore(int score);

#endif
