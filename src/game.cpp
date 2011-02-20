#include "game.hpp"

Game::Game() :
  playerOne(0, 0, 25, 75),
  playerTwo(0, 0, 25, 75) 
{
  cvNamedWindow(title, 0);
  captureDevice = cvCreateCameraCapture(-1);

  NextFrame();
  vidWidth = currentFrame->width;
  vidHeight = currentFrame->height;

  if(!captureDevice) {
    std::cerr << "Error, device creation failed!" << std::endl
              << "Aborting..." << std::endl;
    exit(EXIT_FAILURE);
  }
  currentFrame = NULL;

  playerOne.x = 50;
  playerOne.y = playerTwo.y = vidHeight / 2;
  playerTwo.x = vidWidth - playerTwo.width - 50;

  b.x = vidWidth / 2;
  b.y = vidHeight / 2;
  b.r = 10;
  b.xspeed = 5;
  b.yspeed = 8;

}

Game::~Game() {
  cvReleaseCapture(&captureDevice);
  cvDestroyWindow(title);
}

void Game::Loop() {
  bool running(true);

  Calibrate();

  while(running) {

    NextFrame();

    if(!currentFrame) 
      break;

    FindPaddles();

    b.Move();
    b.CheckCollision(playerOne, true);
    b.CheckCollision(playerTwo);
    // draw the ball
    cvCircle(currentFrame, cvPoint(b.x, b.y), b.r, cvScalar(0xFF,0xFF,0xFF), 10);

    Draw();   
    
    // Wait for escape key to exit
    char c = cvWaitKey(33);
    if(c == 27) {
      running = false;
    }
  }
  
}


void Game::Calibrate() {

  Color colSum(10, 10, 10);
  int x = vidWidth / 2;
  int y = vidHeight / 2;
  int size = 30;

  CvFont font;
  double hScale = 1.0;
  double vScale = 1.0;
  int    lineWidth = 2;
  cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, hScale,vScale,0,lineWidth);  

  while(true) {
    NextFrame();

    cvPutText (currentFrame, "Place marker inside box to calibrate", cvPoint(25, 25),
               &font, cvScalar(255,255,255));
    cvPutText (currentFrame, "and press enter", cvPoint(25, 50),
               &font, cvScalar(255,255,255));

    cvRectangle(currentFrame, cvPoint(x - size / 2, y - size / 2),
                cvPoint(x - size / 2 + size, y - size / 2 + size),
                cvScalar(255, 255, 255), 1);

    Draw();

    char c = cvWaitKey(33);
    if(c == 27) {
      break;
    } else if(c == 'q') {
      size++;
    } else if(c == 'e') {
      size--;
    } else if(c == '\n') {      

      // finding the average of the selected square
      CvRect old_roi = cvGetImageROI(currentFrame);
      cvSetImageROI(currentFrame, cvRect(x, y, size, size));
      CvScalar c = cvAvg(currentFrame);
      cvSetImageROI(currentFrame,old_roi);

      colSum.r = c.val[0];
      colSum.g = c.val[1];
      colSum.b = c.val[2];

      playerMarker = colSum;

      cvRectangle(currentFrame, cvPoint(x - size / 2, y - size / 2),
                  cvPoint(x - size / 2 + size, y - size / 2 + size), 
                  cvScalar(colSum.r, colSum.g, colSum.b), size);
      Draw();
      cvWaitKey(100000);

      break;      
    } 
  }
}


void Game::NextFrame() {
  currentFrame = cvQueryFrame(captureDevice);
  cvFlip(currentFrame, 0, 1);
}

void Game::Draw() {
  cvShowImage(title, currentFrame);
}

void Game::FindPaddles() {
  Image<RgbPixel> image(currentFrame);
  
  int count = 0;
  int ySum = 0;

  int pr = playerMarker.r;
  int pg = playerMarker.g;
  int pb = playerMarker.b;

  // player 1
  for (int y = 0; y < currentFrame->height; y++) {
    for (int x = 0; x < currentFrame->width / 2; x++) {

      int r = image[y][x].r;
      int g = image[y][x].g;
      int b = image[y][x].b;

      if (abs(r - pr) < colTolerance  && abs(g - pg) < colTolerance &&
          abs(b - pb) < colTolerance) {          
          image[y][x].r = pr;
          image[y][x].g = 0;
          image[y][x].b = 0;
          ySum  += y;
          count++;       
        }
    }
  }
  
  // make sure there are some valid points
  if(count > 50 ) {
    int yAvg = ySum / count;
    playerOne.y = yAvg;
  }

  count = 0;
  ySum = 0;
  // player 2
  for (int y = 0; y < currentFrame->height; y++) {
    for (int x = currentFrame->width / 2; x < currentFrame->width; x++) {

      int r = image[y][x].r;
      int g = image[y][x].g;
      int b = image[y][x].b;

      if (abs(r - pr) < colTolerance  && abs(g - pg) < colTolerance &&
          abs(b - pb) < colTolerance) {          
          image[y][x].r = pr;
          image[y][x].g = 0;
          image[y][x].b = 0;
          ySum  += y;
          count++;       
        }
    }
  }
  
  if(count > 50) {
    int yAvg = ySum / count;
    playerTwo.y = yAvg;
  }

  Color c = playerOne.color;
  int w = playerOne.width;
  int h = playerOne.height;

  cvRectangle(currentFrame, cvPoint(playerOne.x , playerOne.y),
              cvPoint(playerOne.x + w, playerOne.y + h),
              cvScalar(c.r, c.b, c.g), 10);

  c = playerTwo.color;
  
  cvRectangle(currentFrame, cvPoint(playerTwo.x , playerTwo.y),
              cvPoint(vidWidth - 50, playerTwo.y + h),
              cvScalar(c.r, c.b, c.g), 10);

}
