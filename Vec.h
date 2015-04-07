#ifndef __Vec_H__
#define __Vec_H__

//stores a vector of x and y coordinates
class Vec
{
   public:
   
      static Vec null;
   
      Vec() : x(0.0f), y(0.0f) {}
      Vec(float X, float Y) : x(X), y(Y) {}
      
      void add(const Vec& v)
      {
         x += v.x;
         y += v.y;
      }
      
      float x, y;
}; ///:~


#endif /* __Vec_H__ */

