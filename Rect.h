#ifndef __Rect_H__
#define __Rect_H__

#include <iostream>
#include "Vec.h"


#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class Rect
{
   public:
      Rect (float, float, float, float, float, float, float);
      
      bool contains(const Vec& v);
      
      void Draw();
      
      void update(float, float);

      float ulX, ulY, w, h;
      float R, G, B; 
}; ///:~

#endif /* __Rect_H__ */

