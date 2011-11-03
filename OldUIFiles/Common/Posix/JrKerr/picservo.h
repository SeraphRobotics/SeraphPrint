//---------------------------------------------------------------------------
#ifndef picservoH
#define picservoH
//---------------------------------------------------------------------------
#endif
//--------------------- Servo Module specific stuff ---------------------------

typedef unsigned char byte;
typedef int BOOL;  //0=false, <>0 true

#define MAXSIOERROR 2

typedef	struct _GAINVECT {
    short int	kp;				//gain values
    short int	kd;
    short int	ki;
    short int	il;
    byte		ol;
    byte		cl;
    short int	el;
    byte		sr;
    byte		dc;
	byte		sm;
	} GAINVECT;

typedef struct _SERVOMOD {
    int		pos;     		//current position
    byte		ad;				//a/d value
    short int	vel;            //current velocity
    byte		aux;            //auxilliary status byte
    int		home;           //home position
    short int	perror;			//position error
    byte		npoints;		//number of points in path buffer

    //The following data is stored locally for reference
    int		cmdpos;			//last commanded position
    int		cmdvel;			//last commanded velocity
    int		cmdacc;			//last commanded acceleration
    byte		cmdpwm;			//last commanded PWM value
    GAINVECT    gain;
    int		stoppos;		//motor stop position (used by stop command)
    byte		stopctrl;		//stop control byte
    byte		movectrl;		//load_traj control byte
    byte		ioctrl;			//I/O control byte
    byte		homectrl;		//homing control byte
    byte		ph_adv;			//phase advance (for ss-drive modules)
    byte		ph_off;			//phase offset (for ss-drive modules)
    int		last_ppoint;	//last path point specified
    } SERVOMOD;


//Servo Module Command set:
#define	RESET_POS	  0x00	//Reset encoder counter to 0 (0 bytes)
#define	SET_ADDR	  0x01	//Set address and group address (2 bytes)
#define	DEF_STAT	  0x02	//Define status items to return (1 byte)
#define	READ_STAT	  0x03	//Read value of current status items
#define	LOAD_TRAJ  	  0x04	//Load trahectory date (1 - 14 bytes)
#define START_MOVE	  0x05	//Start pre-loaded trajectory (0 bytes)
#define SET_GAIN	  0x06  //Set servo gain and control parameters (13 or 14)
#define	STOP_MOTOR 	  0x07	//Stop motor (1 byte)
#define	IO_CTRL		  0x08	//Define bit directions and set output (1 byte)
#define SET_HOMING	  0x09  //Define homing mode (1 byte)
#define	SET_BAUD	  0x0A 	//Set the baud rate (1 byte)
#define CLEAR_BITS	  0x0B  //Save current pos. in home pos. register (0 bytes)
#define SAVE_AS_HOME  0x0C	//Store the input bytes and timer val (0 bytes)
#define ADD_PATHPOINT 0x0D  //Adds path points for path mode
#define	NOP			  0x0E	//No operation - returns prev. defined status (0 bytes)
#define HARD_RESET	  0x0F	//RESET - no status is returned

//Servo Module RESET_POS control byte bit definitions:
//(if no control byte is used, reset is absolute)
#define REL_HOME 	  0x01	//Reset position relative to current home position
#define SET_POS 	  0x02	//Set the position to a specific value (v10 & >)

//Servo Module STATUSITEMS bit definitions:
#define	SEND_POS	  0x01	//4 bytes data
#define	SEND_AD		  0x02	//1 byte
#define	SEND_VEL	  0x04	//2 bytes
#define SEND_AUX	  0x08	//1 byte
#define SEND_HOME	  0x10	//4 bytes
#define SEND_ID		  0x20	//2 bytes
#define SEND_PERROR	  0x40  //2 bytes
#define SEND_NPOINTS  0x80  //1 byte

//Servo Module LOAD_TRAJ control byte bit definitions:
#define	LOAD_POS	  0x01	//+4 bytes
#define LOAD_VEL	  0x02	//+4 bytes
#define	LOAD_ACC	  0x04	//+4 bytes
#define LOAD_PWM	  0x08	//+1 byte
#define ENABLE_SERVO  0x10  //1 = servo mode, 0 = PWM mode
#define VEL_MODE	  0x20	//1 = velocity mode, 0 = trap. position mode
#define REVERSE		  0x40  //1 = command neg. PWM or vel, 0 = positive
#define MOVE_REL	  0x40  //1 = move relative, 0 = move absolute
#define START_NOW	  0x80  //1 = start now, 0 = wait for START_MOVE command

//Servo Module STOP_MOTOR control byte bit definitions:
#define	AMP_ENABLE	  0x01	//1 = raise amp enable output, 0 = lower amp enable
#define MOTOR_OFF	  0x02	//set to turn motor off
#define STOP_ABRUPT   0x04	//set to stop motor immediately
#define STOP_SMOOTH	  0x08  //set to decellerate motor smoothly
#define STOP_HERE	  0x10	//set to stop at position (4 add'l data bytes required)
#define ADV_FEATURE   0x20  //enable features in ver. CMC

//Servo Module IO_CTRL control byte bit definitions:
#define SET_OUT1	  0x01	//1 = set limit 1 output, 0 = clear limit 1 output
#define SET_OUT2	  0x02	//1 = set limit 2 output, 0 = clear limit 2 output
#define IO1_IN		  0x04	//1 = limit 1 is an input, 0 = limit 1 is an output
#define IO2_IN		  0x08	//1 = limit 2 is an input, 0 = limit 2 is an output
#define LIMSTOP_OFF   0x04   //turn off motor on limit
#define LIMSTOP_ABRUPT 0x08  //stop abruptly on limit
#define THREE_PHASE	  0x10  //1 = 3-phase mode, 0 = single PWM channel
#define ANTIPHASE	  0x20  //1 = antiphase (0 = 50% duty cycle), 0 = PWM & dir
#define	FAST_PATH	  0x40  //0 = 30 or 60 Hz path execution, 1 = 60 or 120 Hz
#define STEP_MODE	  0x80  //0 = normal operation, 1 = Step & Direction enabled

//Servo Module SET_HOMING control byte bit definitions:
#define ON_LIMIT1	  0x01	//home on change in limit 1
#define ON_LIMIT2	  0x02	//home on change in limit 2
#define HOME_MOTOR_OFF  0x04  //turn motor off when homed
#define ON_INDEX	  0x08	//home on change in index
#define HOME_STOP_ABRUPT 0x10 //stop abruptly when homed
#define HOME_STOP_SMOOTH 0x20 //stop smoothly when homed
#define ON_POS_ERR	  0x40	//home on excessive position error
#define	ON_CUR_ERR	  0x80  //home on overcurrent error

//Servo Module ADD_PATHPOINT frequency definitions
#define P_30HZ		  30	//30 hz path resolution
#define P_60HZ		  60    //60 hs path resolution
#define P_120HZ		  120   //120 hs path resolution

//Servo Module HARD_RESET control byte bit definitions (v.10 and higher only):
#define	SAVE_DATA	  0x01	//save config. data in EPROM
#define RESTORE_ADDR  0x02  //restore addresses on power-up
#define EPU_AMP	      0x04  	//enable amplifier on power-up
#define EPU_SERVO     0x08  //enable servo
#define EPU_STEP	  0x10  //enable step & direction mode
#define EPU_LIMITS    0x20  //enable limit switch protection
#define EPU_3PH	      0x40  //enable 3-phase commutation
#define EPU_ANTIPHASE 0x80 //enable antiphase PWM

//Servo Module Status byte bit definitions:
#define MOVE_DONE	  0x01	//set when move done (trap. pos mode), when goal
							//vel. has been reached (vel mode) or when not servoing
#define CKSUM_ERROR	  0x02	//checksum error in received command
#define OVERCURRENT	  0x04	//set on overcurrent condition (sticky bit)
#define POWER_ON	  0x08	//set when motor power is on
#define POS_ERR		  0x10	//set on excess pos. error (sticky bit)
#define LIMIT1		  0x20	//value of limit 1 input
#define LIMIT2		  0x40	//value of limit 2 input
#define HOME_IN_PROG  0x80  //set while searching for home, cleared when home found

//Servo Module Auxilliary status byte bit definitions:
#define INDEX		  0x01	//value of the encoder index signal
#define POS_WRAP	  0x02	//set when 32 bit position counter wraps around
							//  (sticky bit)
#define SERVO_ON	  0x04	//set when position servo is operating
#define ACCEL_DONE	  0x08	//set when acceleration portion of a move is done
#define SLEW_DONE	  0x10  //set when slew portion of a move is done
#define SERVO_OVERRUN 0x20  //set if servo takes longer than the specified
							//servo period to execute
#define PATH_MODE	  0x40  //path mode is enabled (v.5)

//Servo module function prototypes:

//---------------------------------------------------------------------------//
//  Function Name:  ServoNewMod (Internal Library Function)                  //
//  Return Value:   Pointer to the new SERVOMOD structure.                   //
//  Parameters:     None                                                     //
//  Description:    Creates and initializes a new SERVOMOD structure.        //
//---------------------------------------------------------------------------//
extern "C" SERVOMOD * ServoNewMod();

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetStat (Internal Library Function)                 //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Processes and stores returned PIC-SERVO status data.     //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoGetStat(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetPos                                              //
//  Return Value:   Returns the current motor position.                      //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the current motor position (stored locally).     //
//---------------------------------------------------------------------------//
extern "C" int ServoGetPos(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetAD                                               //
//  Return Value:   Returns the current A/D value.                           //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the current A/D value (stored locally).          //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetAD(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetVel                                              //
//  Return Value:   Returns the current motor velocity.                      //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the current motor velocity (stored locally).     //
//---------------------------------------------------------------------------//
extern "C" short int ServoGetVel(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetAux                                              //
//  Return Value:   Returns the current auxiliary status byte.               //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the current auxiliary status byte (stored        //
//                  locally).                                                //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetAux(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetHome                                             //
//  Return Value:   Returns the current motor home position.                 //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the current motor home position (stored locally).//
//---------------------------------------------------------------------------//
extern "C" int ServoGetHome(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetPError                                           //
//  Return Value:   Returns the servo positioning error.                     //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the servo positioning error (stored locally).    //
//---------------------------------------------------------------------------//
extern "C" short int ServoGetPError(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetNPoints                                          //
//  Return Value:   Returns the number of path points remaining.             //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the number of path points remaining (stored      //
//                  locally).                                                //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetNPoints(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetCmdPos                                           //
//  Return Value:   Returns the most recently issued command position.       //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued command position.       //
//---------------------------------------------------------------------------//
extern "C" int ServoGetCmdPos(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetCmdVel                                           //
//  Return Value:   Returns the most recently issued command velocity.       //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued command velocity.       //
//---------------------------------------------------------------------------//
extern "C" int ServoGetCmdVel(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetCmdAcc                                           //
//  Return Value:   Returns the most recently issued command acceleration.   //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued command acceleration.   //
//---------------------------------------------------------------------------//
extern "C" int ServoGetCmdAcc(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetStopPos                                          //
//  Return Value:   Returns the most recently issued stop position.          //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued stop position (by a     //
//                  ServoStopHere() command).                                //
//---------------------------------------------------------------------------//
extern "C" int ServoGetStopPos(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetCmdPwm                                           //
//  Return Value:   Returns the most recently issued command PWM.            //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued command PWM.            //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetCmdPwm(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetMoveCtrl                                         //
//  Return Value:   Returns most recently issued move command control byte.  //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued move command control    //
//                  byte.                                                    //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetMoveCtrl(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetStopCtrl                                         //
//  Return Value:   Returns most recently issued stop command control byte.  //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued stop command control    //
//                  byte.                                                    //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetStopCtrl(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetHomeCtrl                                         //
//  Return Value:   Returns most recently issued home command control byte.  //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued home command control    //
//                  byte.                                                    //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetHomeCtrl(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetIoCtrl                                           //
//  Return Value:   Returns most recently issued I/O command control byte.   //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the most recently issued I/O command control     //
//                  byte.                                                    //
//---------------------------------------------------------------------------//
extern "C" byte ServoGetIoCtrl(byte addr);

extern "C" byte ServoGetPhAdv(byte addr);
extern "C" byte ServoGetPhOff(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetGain                                             //
//  Return Value:   None                                                     //
//  Parameters:     addr: module address (1-32)                              //
//                  kp: position gain Kp                                     //
//                  kd: derivative gain Kd                                   //
//                  ki: integral gain Ki                                     //
//                  il: integration limit IL                                 //
//                  ol: output limit OL                                      //
//                  cl: current limit CL                                     //
//                  el: position error limit EL                              //
//                  sr: servo rate divisor SR                                //
//                  dc: amplifier deadband compenstation DB                  //
//  Description:    Returns the most recently issued servo gain values for   //
//                  a PIC-SERVO module.  For PIC-SERVO SC modules, use       //
//                  ServoGetGain2().                                         //
//---------------------------------------------------------------------------//
extern "C" void ServoGetGain(byte addr, short int * kp, short int * kd, short int * ki,
				  short int * il, byte * ol, byte * cl, short int * el,
                  byte * sr, byte * dc);

//---------------------------------------------------------------------------//
//  Function Name:  ServoSetGain                                             //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  kp: Position gain Kp (0 - +32,767)                       //
//                  kd: Derivative gain Kd (0 - +32,767)                     //
//                  ki: Integral gain Ki (0 - +32,767)                       //
//                  ol: Output limit OL (0 - 255)                            //
//                  cl: Current limit CL (0 - 255)                           //
//                     (odd values: CUR_SENSE proportional to motor current) //
//                     (even values: CUR_SENSE inv. prop. to motor current)  //
//                  el: Position error limit EL (0 - +32,767)                //
//                  sr: Servo rate divisor SR (1 - 255)                      //
//                  dc: Amplifier deadband compenstation DB (0 - 255)        //
//  Description:    Sets most of the non-motion related operating parameters //
//                  of the PIC-SERVO.  New applications should use           //
//                  ServoSetGain2() for all versions of PIC-SERVO.           //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetGain(byte addr, short int kp, short int kd, short int ki,
				  short int il, byte ol, byte cl, short int el,
                  byte sr, byte dc);

//---------------------------------------------------------------------------//
//  Function Name:  ServoGetGain2                                            //
//  Return Value:   None                                                     //
//  Parameters:     addr: module address (1-32)                              //
//                  kp: position gain Kp                                     //
//                  kd: derivative gain Kd                                   //
//                  ki: integral gain Ki                                     //
//                  il: integration limit IL                                 //
//                  ol: output limit OL                                      //
//                  cl: current limit CL                                     //
//                  el: position error limit EL                              //
//                  sr: servo rate divisor SR                                //
//                  dc: amplifier deadband compenstation DB                  //
//                  sm: step rate multiplier SM                              //
//  Description:    Returns the most recently issued servo gain values for   //
//                  a PIC-SERVO SC module. For non-PIC-SERVO SC modules,     //
//                  use ServoGetGain().                                      //
//---------------------------------------------------------------------------//
extern "C" void ServoGetGain2(byte addr, short int * kp, short int * kd, short int * ki,
								short int * il, byte * ol, byte * cl, short int * el,
								byte * sr, byte * dc, byte * sm);

//---------------------------------------------------------------------------//
//  Function Name:  ServoSetGain2                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  kp: Position gain Kp (0 - +32,767)                       //
//                  kd: Derivative gain Kd (0 - +32,767)                     //
//                  ki: Integral gain Ki (0 - +32,767)                       //
//                  ol: Output limit OL (0 - 255)                            //
//                  cl: Current limit CL (0 - 255)                           //
//                     (odd values: CUR_SENSE proportional to motor current) //
//                     (even values: CUR_SENSE inv. prop. to motor current)  //
//                  el: Position error limit EL (0 - +32,767)                //
//                  sr: Servo rate divisor SR (1 - 255)                      //
//                  dc: Amplifier deadband compenstation DB (0 - 255)        //
//                  sm: Step rate multiplier (1 - 255)                       //
//  Description:    Sets most of the non-motion related operating parameters //
//                  of the PIC-SERVO.  New applications should use this      //
//                  version of the Set Gain command (rather than             //
//                  ServoSetGain()) for all versions of the PIC-SERVO.       //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetGain2(byte addr, short int kp, short int kd, short int ki,
							   short int il, byte ol, byte cl, short int el,
							   byte sr, byte dc, byte sm);

//---------------------------------------------------------------------------//
//  Function Name:  ServoResetPos                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module addr (1-32)                                 //
//  Description:    Resets the position counter to zero.                     //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoResetPos(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoResetRelHome                                        //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Resets the position of a module relative to the home     //
//                  position register (home position is now zero position).  //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoResetRelHome(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoSetPos                                              //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  pos: position (-2,147,483,648 - +2,147,483,647)          //
//  Description:    Sets the module position to the specified value.         //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetPos(byte addr, int pos);

//---------------------------------------------------------------------------//
//  Function Name:  ServoClearBits                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Clears the latched status bits (OVERCURRENT and          //
//                  POS_ERROR bits in status byte, and POS_WRAP and          //
//                  SERVO_OVERRUN bits in auxiliary status byte).            //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoClearBits(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoStopMotor                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of stop mode bits                       //
//  Description:    Stop the motor in the manner specified by mode.          //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoStopMotor(byte addr, byte mode);

//---------------------------------------------------------------------------//
//  Function Name:  ServoStopHere                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of the stop mode bits (see picservo.h)  //
//                  pos: unprofiled command position                         //
//  Description:    Stop the motor at the specified position.                //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoStopHere(byte addr, byte mode, int pos);

//---------------------------------------------------------------------------//
//  Function Name:  ServoSetIoCtrl                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of I/O control bits (see picservo.h)    //
//  Description:    Controls the configuration of the LIMIT1 and LIMIT2      //
//                  I/O pins, as well as other miscellaneous functions.      //
//                  CAUTION: Use extreme care in setting the parameters for  //
//                  this command - incorrect settings could damage your      //
//                  amplifier or the PIC-SERVO chip.                         //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetIoCtrl(byte addr, byte mode);

//---------------------------------------------------------------------------//
//  Function Name:  ServoLoadTraj                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of the load trajectory mode bits        //
//                        (see picservo.h)                                   //
//                  pos: Position data if LOAD_POS bit of mode is set        //
//                       (-2,147,483,648 - +2,147,483,647)                   //
//                  vel: Velocity data is LOAD_VEL bit of mode is set        //
//                       (0 - +83,886,080)                                   //
//                  acc: Acceleration data is LOAD_ACC bit of mode is set    //
//                       (0 - +2,147,483,647)                                //
//                  pwm: PWM data is LOAD_PWM bit of mode is set (0 - +255)  //
//  Description:    Loads motion trajectory and PWM information.             //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoLoadTraj(byte addr, byte mode, int pos, int vel, int acc, byte pwm);

//---------------------------------------------------------------------------//
//  Function Name:  ServoInitPath                                            //
//  Return Value:   None                                                     //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Initializes the starting point of a path to the current  //
//                  motor position.                                          //
//---------------------------------------------------------------------------//
extern "C" void ServoInitPath(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  ServoAddPathPoints                                       //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  npoints: number of points in list (1-7)                  //
//                  path: path points list of absolute position data         //
//                  freq: path point frequency (P_30HZ, P_60HZ, P-120HZ)     //
//  Description:    Adds a set of path points for path mode operation.  Use  //
//                  ServoStartPathMode() to start path mode.                 //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoAddPathpoints(byte addr, int npoints, int *path, int freq);

//---------------------------------------------------------------------------//
//  Function Name:  ServoStartPathMode                                       //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     groupaddr: module addr( 1-32) or group addr (0x80-0xFF)  //
//                  groupleader: group leader address                        //
//                    if groupaddr individual use: groupleader=groupaddr     //
//                    if groupaddr group use: groupleader=group leader addr  //
//                    (if no group leader use: groupleader = 0)              //
//  Description:    Starts execution of the path loaded into the internal    //
//                  path point buffer.                                       //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoStartPathMode(byte groupaddr, byte groupleader);

//---------------------------------------------------------------------------//
//  Function Name:  ServoStartMove                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     groupaddr: module addr (1-32) or group addr (0x80-0xFF)  //
//                  groupleader: group leader address                        //
//                    if groupaddr individual use: groupleader=groupaddr     //
//                    if groupaddr group use: groupleader=group leader addr  //
//                    (if no group leader use: groupleader = 0)              //
//  Description:    Synchronously start motions that have been preloaded     //
//                  using ServoLoadTraj().                                   //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoStartMove(byte groupaddr, byte groupleader);

//---------------------------------------------------------------------------//
//  Function Name:  ServoSetHoming                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of the homing mode bits (see picservo.h)//
//  Description:    Sets homing mode parameters for capturing the home       //
//                  position.                                                //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetHoming(byte addr, byte mode);

extern "C" BOOL ServoSetPhase(byte addr, int padvance, int poffset, int maxpwm);

//---------------------------------------------------------------------------//
//  Function Name:  ServoHardReset                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of reset control bits (see picservo.h)  //
//  Description:    Reset the controller to it's power-up state and          //
//                  optionally store configuration data in EEPROM.           //
//                  (Only valid for PIC-SERVO SC - v.10 and greater)         //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoHardReset(byte addr, byte mode);


