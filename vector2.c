/* vector2.c */
#include<vector2.h>

vector2 makevector2(double x, double y){
  vector2 ret;
  ret.x = x;
  ret.y = y;
  return ret;
}

vector2 vec2plus(vector2 a, vector2 b){
  vector2 ret;
  ret.x = a.x+b.x;
  ret.y = a.y+b.y;
  return ret;
}

void vec2add(vector2* a, vector2* b){
  a->x = a->x+b->x;
  a->y = a->y+b->y;
}

vector2 vec2minus(vector2 a, vector2 b){
  vector2 ret;
  ret.x = a.x-b.x;
  ret.y = a.y-b.y;
  return ret;
}

void vec2subtract(vector2* a, vector2* b){
  a->x = a->x-b->x;
  a->y = a->y-b->y;
}

double vec2dot(vector2 a, vector2 b){
  return a.x*b.x+a.y*b.y;
}

