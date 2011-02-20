#ifndef _VRPONG_H_
#define _VRPONG_H_

#include "highgui.h"
#include <iostream>

namespace  {
  const char* const title      = "VRPONG";
  const int winWidth     = 800;
  const int winHeight    = 800;
  const int colTolerance = 0x20;

  int vidWidth;
  int vidHeight;
}

struct Color {
  int r, g, b;

  Color() {}
  Color(int x, int y, int z) : r(x), g(y), b(z) {}
};

// delicious copypasta from 
// <http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html>
template<class T> class Image {
private:
  IplImage* imgp;
public:
  Image(IplImage* img=0) {imgp=img;}
  ~Image(){imgp=0;}
  void operator=(IplImage* img) {imgp=img;}
  inline T* operator[](const int rowIndx) {
    return ((T *)(imgp->imageData + rowIndx*imgp->widthStep));}
};

typedef struct {
  unsigned char b,g,r;
} RgbPixel;

#endif /* _VRPONG_H_ */
