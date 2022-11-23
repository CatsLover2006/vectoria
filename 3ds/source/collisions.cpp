#include <cmath>

float dist(float x1, float y1, float x2, float y2) {
	float dX = x1 - x2;
	float dY = y1 - y2;
	return sqrt(dX *dX + dY *dY);
}

bool linePoint(float x1, float y1, float x2, float y2, float px, float py) {
  float d1 = dist(px,py, x1,y1);
  float d2 = dist(px,py, x2,y2);
  float lineLen = dist(x1,y1, x2,y2);
  float buffer = 0.1; // Approximation
  return (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer);
}

bool pointCircle(float px, float py, float cx, float cy, float r) {
  float distX = px - cx;
  float distY = py - cy;
  return sqrt((distX*distX) + (distY*distY)) <= r;
}

bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r) {
  bool inside1 = pointCircle(x1,y1, cx,cy,r);
  bool inside2 = pointCircle(x2,y2, cx,cy,r);
  if (inside1 || inside2) return true;
  float distX = x1 - x2;
  float distY = y1 - y2;
  float len = sqrt( (distX*distX) + (distY*distY) );
  float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);
  float closestX = x1 + (dot * (x2-x1));
  float closestY = y1 + (dot * (y2-y1));
  bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
  if (!onSegment) return false;
  distX = closestX - cx;
  distY = closestY - cy;
  float distance = sqrt( (distX*distX) + (distY*distY) );
  return distance <= r;
}