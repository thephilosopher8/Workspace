#ifndef __GrPlotQuadratic_H__
#define __GrPlotQuadratic_H__

#include "GrRect.h"
#include "GenerateCurves.h"



class GrPlotQuadratic : public GrRect
{
   public:
      GrPlotQuadratic(float, float, float, float, float, float, float);
      
      void Draw();
      virtual ~GrPlotQuadratic () {}

   private:
      /* data */
      
      QuadraticCurve curve;
};

#endif /* __GrPlotQuadratic_H__ */

