#ifndef POINT_H
#define POINT_H

#include "Util.h"

namespace PROJECT_NAMESPACE
{
    /**
      A Point object represents a point in 3-dimensional Euclidean space.
     */
    class Point
    {
    public:
        double x,y,z;

        //Creates the point (0,0,0).
        Point();

        //Creates the point (x,y,z).
        Point(const double& x, const double& y, const double& z);

        /**
          Returns the Euclidean distance between a and b.
          @param a The first point
          @param b The second point
          @return The distance between these two points
         */
        static double calcDist(const Point& a, const Point& b);
    };
}

#endif //ndef POINT_H
