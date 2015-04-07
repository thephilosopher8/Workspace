#include "GrRect.h"

GrRect::GrRect(float x, float y, float W, float H, float r, float g, float b) 
     : ulX(x), ulY(y), w(W), h(H), R(r), G(g), B(b), Focus(false)
{
   topMargin = new Rect(x, y, W, H-0.4, 0.49, 0.79, 0.79);
   BottomRight = new Rect(x+w-0.05, y-h+0.05, 0.05, 0.05, 0.49, 0.79, 0.79);
}

bool GrRect::inMenu(const Vec& v)
{
   // return if click was in the top bar
  	return topMargin->contains(v);
}

bool GrRect::inResizer(const Vec& v)
{
   // return if click was in the top bar
  	return BottomRight->contains(v);
}

bool GrRect::contains(const Vec& v)
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

void GrRect::Draw()
{
   topMargin->Draw();
   BottomRight->Draw();
   
   //draw points in window
   glBegin(GL_POINTS);
      glColor3d ( 1.0, 1.0, 1.0 );
      for (unsigned int i = 0; i < points.size(); i++)
      {
         Vec temp(points[i].x + ulX, points[i].y + ulY);
         if(contains(temp))
            glVertex2f(temp.x, temp.y);
      }
   glEnd();
   
   
   //draw the Rect
   glBegin( GL_POLYGON );
   glColor3f (R, G, B);
   glVertex2f (ulX,(ulY - h));
   glVertex2f ((ulX + w), (ulY - h));
   glVertex2f ((ulX + w), ulY);
   glVertex2f (ulX, ulY);
   glEnd();
}

void GrRect::update(float x, float y, eType e)
{
   if(e == MOVE)
   {
      //move the position of Rect by x,y 
      ulX += x;
      ulY += y;
   
      topMargin->update(x,y);
      BottomRight->update(x,y);
   }
   
   else if(e == RESIZE)
   {
      BottomRight->update(x, y);
      h -= y;
      w += x;
      
      topMargin->w += x;
   }
}

void GrRect::handle(float x, float y, eType e)
{
   //add points to the window using local coordinates
   Vec v(x - ulX, y - ulY);
   points.push_back(v);
}

GrRect::~GrRect()
{
   delete topMargin;
   delete BottomRight;
}
