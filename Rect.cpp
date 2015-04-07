#include "Rect.h"

Rect::Rect(float x, float y, float W, float H, float r, float g, float b) 
     : ulX(x), ulY(y), w(W), h(H), R(r), G(g), B(b)
{
}

bool Rect::contains(const Vec& v)
{
	bool c = false;
   
   //check if the point v is within the Rect
   if(v.x >= ulX && v.x <= (ulX + w))
   {  
   	if(v.y <= ulY && v.y >= (ulY - h))
      {
      	c = true;
      }
  	}
   return c;
}

void Rect::Draw()
{
   //draw the Rect
   glBegin( GL_POLYGON );
   glColor3f (R, G, B);
   glVertex2f (ulX,(ulY - h));
   glVertex2f ((ulX + w), (ulY - h));
   glVertex2f ((ulX + w), ulY);
   glVertex2f (ulX, ulY);  
   glEnd();
}

void Rect::update(float x, float y)
{
   //move the position of Rect by x,y 
   ulX += x;
   ulY += y;
}
