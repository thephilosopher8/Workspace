#ifndef __GrRect_H__
#define __GrRect_H__
#include <vector>
#include "Vec.h"
#include "Rect.h"
#include "glut_window.h"
#include <iostream>


#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class GrRect
{
   public:
      
      enum eType{NONE, MOVE, RESIZE};
   
   
      GrRect (float, float, float, float, float, float, float);
      
      bool inMenu(const Vec& v);
      
      bool inResizer(const Vec& v);
      
      bool contains(const Vec& v);
      
      virtual void Draw();
      
      void update(float, float, eType);
      
      virtual void handle(float, float, eType);
      
      void focus(bool f) {Focus = f;}
      bool hasFocus() {return Focus;}

      float ulX, ulY, w, h;
      float R, G, B;
      
      virtual ~GrRect();
      
   protected:
       std::vector<Vec> points;
       
       bool Focus;
       
       Rect* topMargin;
       Rect* BottomRight;
};

#endif /* __GrRect_H__ */

