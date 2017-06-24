/* scenario.h */
#ifndef _SCENARIO_H_
#define _SCENARIO_H_

#include<bidlist.h>
#include<event.h>

void initscenario(void);
void addevent(event* ev);
void resetmark(void);
int getcurrentmark(void);
void setmark(int pos);
event* getnextevent(void); 

#endif
