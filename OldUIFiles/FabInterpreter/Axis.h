#ifndef AXIS_H
#define AXIS_H

#include "Motor.h"

namespace PROJECT_NAMESPACE
{
    /**
      This class represents each axis motor, and contains the Motor object for this specific axis,
      and the name of the axis.
     */

    class Axis
    {
    public:
        string name;
        Motor* motor;

        Axis(void);
        Axis(string,Motor*);
    };
}

#endif //ndef AXIS_H
