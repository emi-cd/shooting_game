/* bidlist.h */
#ifndef _BIDLIST_H_
#define _BIDLIST_H_

typedef struct bidnode{
  struct bidnode* prev;
  struct bidnode* next;
  void* data; 
} bidnode;

typedef struct bidlist{
  bidnode* head;
  bidnode* tail;
  bidnode* mark;
  int count;
} bidlist;


bidlist* newbidlist(void);
int bidlistadd(bidlist* blist, void* data);
int bidlistremove(bidlist* blist, bidnode* node);
int bidlistcount(bidlist* blist);
bidnode* bidlistget(bidlist* blist, int num);
void bidlistreset(bidlist* blist);
bidnode* bidlistnext(bidlist* blist);
bidnode* bidlistsetmark(bidlist* blist, bidnode* node);

#endif
