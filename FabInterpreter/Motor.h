#ifndef MOTOR_H
#define MOTOR_H

#include "Util.h"
//PIC-SERVO path header files
#include "path.h"
#include "picservo.h"


/**
  The Motor class contains the functions necessary to start and stop the motor.
 */
namespace PROJECT_NAMESPACE
{

class Motor
{
    //CONSTANTS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    string NAME;
    byte ADDRESS; //The number of the motor port that this motor is plugged in.
    double COUNTS_PER_U; //Number of counts for 1 U of motion.
    double TICKS_PER_SECOND; //Number of ticks that a motor makes per second.
    double MIN_COMMANDED_POSITION; //The minimum position that the motor can go to
    double MAX_COMMANDED_POSITION; //The maxiumum position that the motor can go to
    double MIN_COMMANDED_VELOCITY; //The minumum velocity the motor can travel at
    double MAX_COMMANDED_VELOCITY; //The maximum velocity the motor can travel at
    double MIN_COMMANDED_ACCELERATION; //The minimum acceleration of the motor
    double MAX_COMMANDED_ACCELERATION; //The maxiumum acceleration of the motor
    double velocity, acceleration; //The velocity and acceleration of the motor
    short KP, KD, KI, IL, EL; //Damping contraints (look up procedure for critically damping motors for more details, also JKerr has documentation)
    byte OL, CL, SR, DB; //See JKerr's Document for more details on his motor bytes
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
    double commandedPosition; //desired position of the motor
    bool initialized; //true is motor is initialized and ready for us, false otherwise
    bool isReversed; //true if motor direction is to be reversed from default values on controller board

    //Tell hardware to send updated data for this motor to the DLL.
    void updateData(void);

public:
    Motor(void);

    //Creates a motor with all of the given values (described above)
    Motor(string name,const byte& address,
          const double countsPerU,
          const double ticksPerSecond,
          short kp, short kd, short ki, short il, byte ol, byte cl, short int el, byte sr, byte db);
    /*
    Motor(string name,const byte& address,
          const double countsPerU,
          const double ticksPerSecond,
          double newVelocity, double newAcceleration,
          short kp, short kd, short ki, short il, byte ol, byte cl, short int el, byte sr, byte db);
*/
    //Returns: The current position of the motor.  The unit of position is U.
    double getPosition(void);

    /**
      Gets the minimum position for input
      @return the smallest position the motor can be moved to
     */
    double getMinPosition();

    /**
      Gets the maximum position for input
      @return the largest position the motor can be moved to
     */
    double getMaxPosition();

    /**
      @return The most recent position that the motor was commanded to move to by moveAbsolute,
      moveRelative, and resetPosition functions. The unit of position is U.
     */
    double getCommandedPosition(void);

    /**
      Move to a position at a specified velocity and acceleration.
      The unit of position is U, the unit of velocity is U/second, and the unit of acceleration is U/(second^2).
      Requires MIN_COMMANDED_POSITION <= position <= MAX_COMMANDED_POSITION,
      MIN_COMMANDED_VELOCITY <= velocity <= MAX_COMMANDED_VELOCITY,
      MIN_COMMANDED_ACCELERATION <= acceleration <= MAX_COMMANDED_ACCELERATION
      @return true iff command was issued successfully.
     */
    bool moveAbsolute(double position, double velocity, double acceleration);

    /**
      Move relative to the current position at a specified velocity and acceleration.
      @return true iff command was issued successfully
     */
    bool moveRelative(double positionDelta, double velocity, double acceleration);

    /**
      Checks to see if the motor whose address is contained by ADDRESS is moving
      @return true iff motor is currently moving.
     */
    bool moving(void);

    /**
      This function returns as soon as possible after the motor has finished moving.
     */
    void waitMove(void);

    /**
      Stops the motor
      @return true iff the motor command to stop was sent in successfully
     */
    bool stop(void);

    /**
      Set whether this motor is reversed.
      If a motor is reversed, movement commands will cause the motor to move in the opposite direction.
      @param A bool that reverses the direction of the motor if true
     */
    void setReversed(bool);

    /**
      Sets the address of the motor on the controller board, see JKerr documentation for more details
      @param groupAddress The group address
      @param isLeader A boolean that indicates whether this motor is the leader of the motors under groupAddress
      @return true iff the command was sent successfully
     */
    bool setGroup(byte groupAddress, bool isLeader);

    /**
      The motors commanded position is set to 0
      @return true iff the command was sent to the motor successfully
     */
    bool resetPosition(void);

    /**
      Initialize the motor.
      @return "" if successful or an error message if failed
     */
    string initialize(void);

    /**
      gets the motor address from the controller board
      @return the address of the motor
     */
    byte getAddress(void);

    /**
      @return the ratio of counts of motor movement per real unit of measurement
     */
    double getCountsPerU(void);

    /**
      Perform cleanup when done using motor.
      @return True iff the command was sent to the motor successfully
     */
    bool cleanUp(void);

    /**
      Sets the velocity to given number
      @param The new velocity
     */
    void setVelocity(double);

    /**
      Sets the acceleration to given number
      @param The new acceleration
     */
    void setAcceleration(double);

    /**
      @return The velocity of the given motor
     */
    double getVelocity();

    /**
      @return The acceleration of the given motor
     */
    double getAcceleration();

    /**
      The destructor
     */
    ~Motor(void);

};

}

#endif //ndef MOTOR_H
