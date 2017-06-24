/* content.h */
#ifndef _CONTENT_H_
#define _CONTENT_H_

union content;

typedef struct general{
  void(*print)(union content*);
} general;

struct event;

typedef union content{
  struct general* wc;
  struct event* ev;
} content;

void printevent(content* con);

#endif
