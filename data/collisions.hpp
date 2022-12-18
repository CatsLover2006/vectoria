#include <cmath>

double closestX;
double closestY;

double dist(double x1, double y1, double x2, double y2) {
	double dX = x1 - x2;
	double dY = y1 - y2;
	return sqrt(dX*dX + dY*dY);
}

bool linePoint(double x1, double y1, double x2, double y2, double px, double py) {
  double d1 = dist(px,py, x1,y1);
  double d2 = dist(px,py, x2,y2);
  double lineLen = dist(x1,y1, x2,y2);
  double buffer = 0.1; // Approximation
  return (d1+d2 >= lineLen-buffer && d1+d2 <= lineLen+buffer);
}

bool pointCircle(double px, double py, double cx, double cy, double r) {
  double distX = px - cx;
  double distY = py - cy;
  return sqrt((distX*distX) + (distY*distY)) <= r;
}

bool lineCircle(double x1, double y1, double x2, double y2, double cx, double cy, double r) {
  double distX = x1 - x2;
  double distY = y1 - y2;
  double len = sqrt( (distX*distX) + (distY*distY) );
  double dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) ) / pow(len,2);
  closestX = x1 + (dot * (x2-x1));
  closestY = y1 + (dot * (y2-y1));
  bool onSegment = linePoint(x1,y1,x2,y2, closestX,closestY);
  if (!onSegment) {
  	if(pointCircle(x1,y1, cx,cy,r)) {
	  closestX = x1;
	  closestY = y1;
	  return true;
  	}
  	if (pointCircle(x2,y2, cx,cy,r)){
	  closestX = x2;
	  closestY = y2;
	  return true;
  	}
	return false;
  }
  distX = closestX - cx;
  distY = closestY - cy;
  double distance = sqrt( (distX*distX) + (distY*distY) );
  return distance <= r;
}