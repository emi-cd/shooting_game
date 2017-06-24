/* vector2.h */
#ifndef _VECTOR2_H_
#define _VECTOR2_H_
typedef struct vector2{
  double x;
  double y;
} vector2;

vector2 makevector2(double x, double y);
vector2 vec2plus(vector2 a, vector2 b);
void vec2add(vector2* a, vector2* b);
vector2 vec2minus(vector2 a, vector2 b);
void vec2subtract(vector2* a, vector2* b);
double vec2dot(vector2 a, vector2 b);

#endif

