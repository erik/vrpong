#ifndef _BALL_H_
#define _BALL_H_

#include "paddle.hpp"

struct Ball {
  int r;
  int x, y;
  float xspeed, yspeed;

  void CheckCollision(Paddle p, bool isP1=false) {
    // TODO: handle scoring
    
    if(y < 0 + r) {
      yspeed = -yspeed;
      y = 0 + r;
      Move();
    } else if (y > vidHeight - r) {
      yspeed = -yspeed;
      y = vidHeight - r;
      Move();
    }

    if(x <= 0 + r) {
      // p2 scored
      x = vidWidth / 2;
      y = vidHeight / 2;
    } else if (x >= vidWidth - 10) {
      //p1 scored
      x = vidWidth / 2;
      y = vidHeight / 2;
    } else {
      if(x <= vidWidth / 2 || isP1) {
        //player 1
        if(y >= p.y && y <= p.y + p.height &&
           x <= p.x + p.width + r / 2 && x > p.x + p.width / 2) {
        xspeed = -xspeed;
        yspeed = -yspeed;
        Move();
      }
    } else if(!isP1){
      //player 2
      if(y >= p.y && y <= p.y + p.height &&
         x >= p.x - r / 2) {
        xspeed = -xspeed;
        yspeed = -yspeed;
        Move();
      }
    }
  }
}

  void Move() {
    x += xspeed;
    y += yspeed;
  }

};


#endif /* _BALL_H_ */
