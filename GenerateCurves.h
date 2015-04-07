#ifndef __GENERATECURVES_H__
#define __GENERATECURVES_H__

using namespace std;

#include <vector>
#include <cmath>


#include "Vec.h"


class XYData
{
   public:
      XYData () {}
      
      void add(Vec v) {list.push_back(v);}
      
      Vec max()
      {
         Vec temp;
         float max = 0;
         int index;
         
         for(int i = 0; i < list.size(); i++)
         {
            temp = list[i];
            
            if(max < temp.y)
            {
               max = temp.y;
               index = i;
            }    
         }
         
         return list[index];
      }
      
      void localize(float x, float y)
      {
         for(int i = 0; i < list.size(); i++)
         {
            list[i].x -= x;
            list[i].y -= y;
         }
      }
      
      Vec fetch(int index)
      {
         return list[index];
      }
      
      virtual void generate(float xini, float xend, float inc) = 0;

   protected:
      /* data */
      
      std::vector<Vec> list;
};


class QuadraticCurve : public XYData
{
   public:
      QuadraticCurve (float A, float B, float C)
         : a(A), b(B), c(C) {}
         
      void generate(float xini, float xend, float inc)
      {
         Vec temp;
         
         for(int i = 0; xini <= xend; xini+= inc)
         {
            temp.x = xini;
            temp.y = (a*pow(xini, 2)) + (xini*b) + c;
            i++;
            add(temp);
         }
      }
      

   private:
      /* data */
      
      float a, b, c;
};

class CubicCurve : public XYData
{
   public:
      CubicCurve (float A, float B, float C, float D)
         : a(A), b(B), c(C), d(D) {}
         
      void generate(float xini, float xend, float inc)
      {
         Vec temp;
         for(int i = 0; xini <= xend; xini+= inc)
         {
            temp.x = xini;
            temp.y = (a*pow(xini, 3)) + (pow(xini, 2)*b) + (c * xini) + d;
            i++;
            
            add(temp);
         }
      }

   private:
      /* data */
      
      float a, b, c,d;
};


#endif /* __GENERATECURVES_H__ */

