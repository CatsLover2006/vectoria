extern float closestX;
extern float closestY;

float dist(float x1, float y1, float x2, float y2);

bool linePoint(float x1, float y1, float x2, float y2, float px, float py);

bool pointCircle(float px, float py, float cx, float cy, float r);

bool lineCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r);