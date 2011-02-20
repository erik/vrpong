#ifndef _PADDLE_H_
#define _PADDLE_H_

#include "vrpong.hpp"

struct Paddle {
  Color color;

  int x, y;
  int width, height;

  Paddle(int x1, int y1, int w, int h, Color c = Color(0xFF, 0xFF, 0xFF)) :
    color(c.r, c.g, c.b), x(x1), y(y1), width(w), height(h) {}

};

#endif /* _PADDLE_H_ */
