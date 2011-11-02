#ifndef BAY_H
#define BAY_H

#include "Motor.h"
#include "Point.h"
#include "MaterialCalibration.h"

namespace PROJECT_NAMESPACE
{
    /**
      This is a class that contains all the data fields for the bay motors,
      including the Motor object that has direct access to the motor commands, the MaterialCalibration
      object for the specific material in the syringe controlled by this bay, and its current location.
     */
    class Bay
    {
    public:
        string name; //The name of the bay
        Motor* motor; //The motor that corresponds to this port
        Point location; //The location of the motor
        MaterialCalibration* materialCalibration; //The material of the bay

        Bay(void);
        Bay(string,Point,Motor*);
    };
}

#endif //ndef BAY_H
