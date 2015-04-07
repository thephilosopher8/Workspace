#include "GrPlotQuadratic.h"

GrPlotQuadratic::GrPlotQuadratic(float x, float y, float W, float H, float r, float g, float b) : GrRect(x, y, W, H, r, g, b), curve(1, 1,1)
{
   float inc = W/20;
   float xStart = x;
   float xEnd = x + W;
   
   curve.generate(xStart, xEnd, inc);
   
  //curve.localize(x,y);
}

void GrPlotQuadratic::Draw()
{
   // Set drawing color to yellow
   glColor3d ( 1.0, 0.9, 0.3 );	
   
   //draw points in window
   glBegin(GL_POINTS);
      glColor3d ( 1.0, 1.0, 1.0 );
      for (unsigned int i = 0; i < 20; i++)
      {
            glVertex2f(curve.fetch(i).x, curve.fetch(i).y);
      }
   glEnd();

   // Draw a highlight around rect
   const double s=0.05;
   glBegin ( GL_LINES );
   glVertex2f (ulX, ulY - h/2);
   glVertex2f (ulX + w, ulY - h/2);
   
   glVertex2f (ulX + w/2, ulY);
   glVertex2f (ulX + w/2, ulY - h);

   glEnd();
   
   GrRect::Draw();
}

