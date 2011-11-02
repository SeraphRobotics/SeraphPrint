#include "Motor.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Motor::Motor(string name,const byte& address,
             const double countsPerU,
             const double ticksPerSecond,
             short kp, short kd, short ki, short il, byte ol, byte cl, short int el, byte sr, byte db) :
initialized(false),
commandedPosition(0.0),
isReversed(false),
NAME(name),
ADDRESS(address),
COUNTS_PER_U(countsPerU),
TICKS_PER_SECOND(ticksPerSecond),
KP(kp),
KD(kd),
KI(ki),
IL(il),
OL(ol),
CL(cl),
EL(el),
SR(sr),
DB(db),
MIN_COMMANDED_POSITION(-2147483648.0/countsPerU),
MAX_COMMANDED_POSITION(2147483647.0/countsPerU),
MIN_COMMANDED_VELOCITY(0.0),
MAX_COMMANDED_VELOCITY(2500000.0/countsPerU),
MIN_COMMANDED_ACCELERATION(0.0),
MAX_COMMANDED_ACCELERATION(125000000000.0/countsPerU)
{}
/**
Motor::Motor(string name, const byte &address,
             double countsPerU,
             double ticksPerSecond,
             double newVelocity, double newAcceleration,
             short kp, short kd, short ki, short il, byte ol, byte cl, short el, byte sr, byte db):
initialized(false),
commandedPosition(0.0),
isReversed(false),
NAME(name),
ADDRESS(address),
COUNTS_PER_U(countsPerU),
TICKS_PER_SECOND(ticksPerSecond),
velocity(newVelocity),
acceleration(newAcceleration),
KP(kp),
KD(kd),
KI(ki),
IL(il),
OL(ol),
CL(cl),
EL(el),
SR(sr),
DB(db),
MIN_COMMANDED_POSITION(-2147483648.0/countsPerU),
MAX_COMMANDED_POSITION(2147483647.0/countsPerU),
MIN_COMMANDED_VELOCITY(0.0),
MAX_COMMANDED_VELOCITY(2500000.0/countsPerU),
MIN_COMMANDED_ACCELERATION(0.0),
MAX_COMMANDED_ACCELERATION(125000000000.0/countsPerU)
{}*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Motor::Motor():
        initialized(false)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Motor::updateData()
{
    NmcNoOp(ADDRESS);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Motor::setReversed(bool isReversed)
{
    this->isReversed = isReversed;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Motor::getPosition()
{
    updateData();
    return (isReversed ? -1 : 1) * ServoGetPos(ADDRESS) / COUNTS_PER_U; //Translate count to U.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Motor::getCommandedPosition()
{
    return commandedPosition;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::moveAbsolute(double position, double velocity, double acceleration)
{
    //if reversed then switches position
    if(isReversed)
    {
        position *= -1;
    }

    //Checks command againsts given constraints
    Util::assertTrue
            (
                    position >= MIN_COMMANDED_POSITION
                    && position <= MAX_COMMANDED_POSITION
                    && velocity >= MIN_COMMANDED_VELOCITY
                    && velocity <= MAX_COMMANDED_VELOCITY
                    && acceleration >= MIN_COMMANDED_ACCELERATION
                    && acceleration <= MAX_COMMANDED_ACCELERATION,
                    "Tried to issue a movement command with arguments that are out of bounds.",
                    __LINE__,__FILE__
                    );

    //sets the commanded position to the given position
    commandedPosition = position;

    return ServoLoadTraj
            (
                    ADDRESS,
                    LOAD_POS | LOAD_VEL | LOAD_ACC | ENABLE_SERVO | START_NOW,
                    (int)(position * COUNTS_PER_U), //Translate U to count.
                    (int)(velocity * COUNTS_PER_U / TICKS_PER_SECOND * 65536), //Translate U/second to count/tick * 2^16.
                    (int)(acceleration * COUNTS_PER_U / (TICKS_PER_SECOND * TICKS_PER_SECOND) * 65536), //Translate U/(second^2) to count/(ticks^2) * 2^16.
                    0 //pwm (no effect if not in pwm mode)
                    ) == 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::moveRelative(double positionDelta, double velocity, double acceleration)
{
    return moveAbsolute(getPosition()+positionDelta, velocity, acceleration);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::stop()
{
    return cleanUp();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::setGroup(byte groupAddress, bool isLeader)
{
    return NmcSetGroupAddr(ADDRESS, groupAddress, isLeader) == 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::resetPosition()
{
    ServoResetPos(ADDRESS);
    commandedPosition = 0.0;
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::moving()
{
    updateData(); //updates the motor info
    byte auxByte = ServoGetAux(ADDRESS);
    bool pathMoving = (auxByte & PATH_MODE) != 0;
    byte statbyte = NmcGetStat(ADDRESS);
    bool nonPathMoving = !(statbyte & MOVE_DONE);
    return pathMoving || nonPathMoving;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Motor::waitMove()
{
    while(moving())
    {
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Motor::initialize()
{

    if(!initialized)
    {
        stringstream ss;
        if(NmcGetModType(ADDRESS) != SERVOMODTYPE)
        {
            ss << "Motor with address " << ADDRESS << " is not a PIC-SERVO motor.";
            return ss.str();
        }
        if(ServoSetGain(ADDRESS,KP,KD,KI,IL,OL,CL,EL,SR,DB) != 1)
        {
            ss << "Failed to set gains for motor with address " << ADDRESS << ".";
            return ss.str();
        }

        ServoStopMotor(ADDRESS, AMP_ENABLE | STOP_ABRUPT | ADV_FEATURE);
        NmcDefineStatus(ADDRESS, SEND_POS | SEND_NPOINTS | SEND_PERROR | SEND_AUX);

        if(!resetPosition())
        {
            ss << "Could not reset position for motor with address " << ADDRESS << ".";
            return ss.str();
        }
        initialized = true;
    }
    return "";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Motor::cleanUp()
{
    bool result;
    if(initialized)
    {
        result = ServoStopMotor(ADDRESS, STOP_ABRUPT | MOTOR_OFF) == 1 && NmcHardReset(ADDRESS) == 1;
        if(result)
        {
            initialized = false;
        }
    }
    else
    {
        result = true;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte Motor::getAddress(void)
{
    return ADDRESS;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Motor::getCountsPerU(void)
{
    return (isReversed ? -1 : 1) * COUNTS_PER_U;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Motor::~Motor()
{
    if (initialized)
        cleanUp();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double Motor::getMinPosition()
{
    return MIN_COMMANDED_POSITION;
}
double Motor::getMaxPosition()
{
    return MAX_COMMANDED_POSITION;
}

void Motor::setVelocity(double newVelocity)
{
    velocity = newVelocity;
}

void Motor::setAcceleration(double newAcceleration)
{
    acceleration = newAcceleration;
}

double Motor::getVelocity()
{
    return velocity;
}

double Motor::getAcceleration()
{
    return acceleration;
}
