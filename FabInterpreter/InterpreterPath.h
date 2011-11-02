#ifndef INTERPRETERPATH_H
#define INTERPRETERPATH_H

#include "Util.h"
#include "Point.h"
#include "Tool.h"

namespace PROJECT_NAMESPACE
{
     /**
        A Path object contains the material of the path and the list of points in that path
        This file is called InterpreterPath to avoid disambiguation between "path.h" in the JrKerr folder
      */
     class Path
     {          
          public:
               double length; //the length of the path
               MaterialCalibration* materialCalibration; //the material of the path
               vector<Point> points; //the list of points that make up the path
     		
               Path(MaterialCalibration*, vector<Point>&);
               
          private:
               /**
                 Calculates the length between the points given
                 @param points The vector of points
                 @return the total length between the given set of points
                */
               static double calcLength(const vector<Point>& points);
     };
}
     
#endif //ndef PATH_H
