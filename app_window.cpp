
# include <iostream>
# include "app_window.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   addMenuEntry ( "Cubic 1", evOption0 );
   addMenuEntry ( "Cubic 2", evOption1 );
   selected = false;
   
   //add Rects to the scene
   stash.add(new GrRect(-0.75, 0.75, 0.5, 0.5, 1.0, 0.0, 0.0));
   stash.add(new GrRect(-0.50, 0.50, 0.5, 0.5, 0.0, 1.0, 0.0));
   stash.add(new GrRect(-0.25, 0.25, 0.5, 0.5, 0.0, 0.0, 1.0));
   stash.add(new GrRect( 0.00, 0.00, 0.5, 0.5, 0.5, 0.0, 0.5));
   
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
{
   bool rd=true;

   if ( e.type==Keyboard ) 
    switch ( e.key )
    { case ' ': // space bar
	   std::cout << "Space pressed.\n";
       redraw();
	   break;

	  case 27: // Esc was pressed
	   exit(1);
	}

   
   if (e.type == MouseDown || e.type == Motion)
    {
      float newX = (float)e.mx;
      float newY = (float)e.my;
      windowToScene(newX,newY);
      
      // allow the RectStash to handle the event
      stash.handle(e, newX, newY);
               
      _markx = newX;
      _marky = newY;
    }

   if ( e.type==Menu )
    { 
      if(e.menuev == 1)
      {       
         stash.add(new GrPlotQuadratic(0, 0, 0.5, 0.5, 1.0, 0.0, 0.0));
      }
      rd=false; // no need to redraw
    }


//   const float incx=0.02f;
//   const float incy=0.02f;
//   if ( e.type==SpecialKey )
//    switch ( e.key )
//    { case GLUT_KEY_LEFT:  _markx-=incx; break;
//      case GLUT_KEY_RIGHT: _markx+=incx; break;
//      case GLUT_KEY_UP:    _marky+=incy; break;
//      case GLUT_KEY_DOWN:  _marky-=incy; break;
//      default: rd=false; // no redraw
//	   }

   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();
   
   //Draw each Rect
   stash.Draw();

   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

