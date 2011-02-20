#include "vrpong.hpp"
#include "game.hpp"

int main( int argc, char** argv ) {
  Game game;
  
  game.Loop();

  /*
  while(1) {
    frame = cvQueryFrame( capture );
    if( !frame ) break;
    
    cvFlip(frame, 0, 1);
    
    cvShowImage( "Example2", frame );
    char c = cvWaitKey(33);
    if( c == 27 ) break;
    
  }
  cvReleaseCapture( &capture );
  cvDestroyWindow( "Example2" );*/
}
