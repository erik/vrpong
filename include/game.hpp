#ifndef _GAME_H_
#define _GAME_H_

#include "vrpong.hpp"
#include "paddle.hpp"
#include "ball.hpp"

class Game {
  IplImage* currentFrame;
  CvCapture* captureDevice;
  Paddle playerOne; 
  Paddle playerTwo;
  Color playerMarker;
  Ball b;

public:
  Game();
  ~Game();

  void Loop();

private:
  void Calibrate();
  void NextFrame();
  void Draw();
  void FindPaddles();

};

#endif /* _GAME_H_ */
