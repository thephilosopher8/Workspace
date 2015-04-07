#ifndef _RECTSTASH_H
#define _RECTSTACH_H

#include <cassert>
#include <vector>
#include <iostream>


#include "GrRect.h"
#include "GrPlotQuadratic.h"
#include "glut_window.h"

//iterator for the vector that holds the Rects
#define ITR std::vector<GrRect*>::iterator

//stash that holds Rect objects
class RectStash
{
   private:
  
	std::vector<GrRect*> vec;
	
	float lastX, lastY;
	
	GrRect::eType type;
  
  public:
	// Functions!
	
	RectStash() : lastX(0), lastY(0), type(GrRect::NONE) {}
	
	void cleanup();
  
	int add(GrRect*);

	GrRect* fetch(int);
	
	void Draw();
	
	int count();
	
	ITR contains(float, float);
	
	void update(float, float);
	
	void handle(const GlutWindow::Event& e, float, float);
	
	~RectStash();
}; ///:~

#endif
