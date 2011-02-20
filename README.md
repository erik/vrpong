#vrpong
vrpong is a basic implementation of pong. The point of it was not to
create an awesome game, but to experiment with the OpenCV library a
bit.

The game doesn't use object detection to find the player's markers,
instead, it just asks for a color at startup, and will treat any pixel
within a tolerance of that color as part of the marker. This seems to
work decently, but is definitely not the best way of doing this.

Code is under MIT license, more information in COPYING.
