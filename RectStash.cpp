#include "RectStash.h"

void RectStash::cleanup()
{
   //clear the vector
	if(!vec.empty()) 
     vec.clear();
}
  
int RectStash::add(GrRect* element)
{
	vec.push_back(element);
	  return(vec.size() -1); // Index number
}

GrRect* RectStash::fetch(int index)
{
	// Check index boundaries:
	assert(0 <= index);
	assert(vec.size() >= index);
  
	// Produce pointer to desired element:
	return vec[index];
}
int RectStash::count()
{
	return vec.size(); // Number of elements in CStash
}

void RectStash::Draw()
{
   //draw boarder around selected Rect
   if(vec[0]->hasFocus())
   {
      // get coordinates from selected rect
      float x = vec[0]->ulX;
      float y = vec[0]->ulY;
      float w = vec[0]->w;
      float h = vec[0]->h;
         
      // Set drawing color to yellow
      glColor3d ( 1.0, 0.9, 0.3 );		

      // Draw a highlight around rect
      const double s=0.05;
      glBegin ( GL_LINES );
      glVertex2f (x, y);
      glVertex2f (x + w, y);
      glVertex2f (x + w, y);
      glVertex2f (x + w, y - h);
      glVertex2f (x + w, y - h);
      glVertex2f (x , y - h);
      glVertex2f (x , y - h);
      glVertex2f (x , y);
      glEnd();
   }
   
   // draw each rect in the vector
   for (ITR it = vec.begin(); it != vec.end(); it++)
   {
     (*it)->Draw();
   }
}

ITR RectStash::contains(float x, float y)
{
   Vec v(x, y);
   ITR it = vec.begin();
   vec[0]->focus(false);
   for (; it != vec.end(); it++)
   {
      //check if point x, y is in any Rect 
      if((*it)->contains(v))
      { 
         vec[0]->focus(false);
         GrRect* temp = *it;
         temp->focus(true);
         
         
         //if it is move the containing Rect to the front
         vec.erase(it);
         vec.insert(vec.begin(), temp);
         break;
      }
   } 
   
   return it;
}

void RectStash::update(float x, float y)
{
   //change the position of the top Rect
   //vec[0]->update(x, y);
}

void RectStash::handle(const GlutWindow::Event& e, float x, float y)
{
   Vec v(x, y);
   if(e.type == GlutWindow::MouseDown)
   { 
      ITR it = contains(x,y);
      
      if(it != vec.end())
      {  
         //if click is in the top bar, allow movement
         if(vec[0]->inMenu(v))
         {
            type = GrRect::MOVE;
         }
         
         else if(vec[0]->inResizer(v))
         {
            type = GrRect::RESIZE;
         }
         
         //if clicking in rect with focus, let Rect handle event
         else if(it == vec.begin())
         {
            (*it)->handle(x, y, type);
            type = GrRect::NONE;
         }
      }
      else
      {
         type = GrRect::NONE;
      }
   }
   
   //update selected Rect 
   if(e.type == GlutWindow::Motion && type != GrRect::NONE)
   {
      float diffX = x - lastX;
      float diffY = y - lastY;
      vec[0]->update(diffX, diffY, type);
   }
   
   lastX = x;
   lastY = y;
}

RectStash::~RectStash()
{
   //delete each Rect
   for (ITR it = vec.begin(); it != vec.end(); it++)
   {
      delete *it;
   }
}


