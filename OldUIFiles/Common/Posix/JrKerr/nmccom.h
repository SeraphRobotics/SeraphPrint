//---------------------------------------------------------------------------
#ifndef nmccomH
#define nmccomH
//---------------------------------------------------------------------------
#endif

//#include <unistd.h>
//#include <stdio.h>
#include "qextserialport.h"

typedef unsigned char byte;

// Non-windows platforms need these too -BR
//typedef int 		BOOL;  //0=false, <>0 true 
//typedef int 		HANDLE;
//typedef unsigned int 	DWORD;
//#define INVALID_HANDLE_VALUE -1




//jrc352: below taken from "sioutil.h"
// Non-windows platforms need these too -BR
typedef int             BOOL;  //0=false, <>0 true
typedef unsigned int   DWORD;
#define INVALID_HANDLE_VALUE -1

typedef struct _NMCMOD {
        byte	modtype;		//module type
    byte	modver;			//module version number
        byte	statusitems;	//definition of items to be returned
        byte	stat;  			//status byte
    byte	groupaddr;		//current group address
    BOOL	groupleader;	//TRUE if group leader
    void *	p;				//pointer to specific module's data structure
    } NMCMOD;

//Define PIC baud rate divisors
#define	PB19200		63
#define	PB57600		20
#define	PB115200	10
#define	PB230400	5

//Module type definitions:
#define	SERVOMODTYPE	0
#define	ADCMODTYPE		1
#define	IOMODTYPE		2
#define	STEPMODTYPE		3
//The following must be created for each new module type:
//		data structure XXXMOD
//		Initializer function NewXXXMod
//		Status reading function GetXXXStat
//		NMCInit and SendNmcCmd must be modified to include calls
//			to the two functions above

#define CKSUM_ERROR		0x02	//Checksum error bit in status byte


#define MAXNUMMOD	33

//--------------------- ADC Module specific stuff --------------------------
typedef struct _ADCMOD {
    //******  Move all this data to the NMCMOD structure *******
	short int ad0;	//definition of items to be returned
	short int ad1;
	short int ad2;
	short int ad3;
	short int ad4;
	short int ad5;
    } ADCMOD;


#define MAXNUMMOD	33

//Function prototypes:
extern "C" ADCMOD * AdcNewMod();
extern "C" BOOL AdcGetStat(byte addr);

//Initialization and shutdown
//---------------------------------------------------------------------------//
//  Function Name:  NmcInit                                                  //
//  Return Value:   Returns the number of controller found on network        //
//  Parameters:     portname: name of COM port ("COMn:", where n=1-8)        //
//                  baudrate: 19200, 57600, 115200, 230400 (PIC-SERVO only)  //
//  Description:    Initialize the network of controllers with sequential    //
//                  addresses starting at 1.                                 //
//---------------------------------------------------------------------------//
extern "C" int NmcInit(char *portname, unsigned int baudrate);

//---------------------------------------------------------------------------//
//  Function Name:  InitVars (Internal Library Function)                     //
//  Return Value:   None                                                     //
//  Parameters:     None                                                     //
//  Description:    Initialize misc network variables.                       //
//---------------------------------------------------------------------------//
extern "C" void InitVars(void);

//---------------------------------------------------------------------------//
//  Function Name:  NmcSendCmd (Internal Library Function)                   //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32) or group address (0x80-0xFF) //
//                  cmd: command type from PIC-SERVO.H, PIC_STEP.H, PIC_IO.H //
//                  datastr: string containing additional command data       //
//                  n: number of additional command data bytes               //
//                  stataddr: status data address                            //
//  Description:    Sends a command to addr and shoves the returned status   //
//                  data in the structure for module address stataddr.  If   //
//                  stataddr = 0, the command is taken as a group command    //
//                  with no group leader (no status returned).  n is the     //
//                  number of auxilliary data bytes.                         //
//---------------------------------------------------------------------------//

extern "C" BOOL NmcSendCmd(byte addr, byte cmd, char *datastr, byte n, byte stataddr);
//---------------------------------------------------------------------------//
//  Function Name:  FixSioError (Internal Library Function)                  //
//  Return Value:   None                                                     //
//  Parameters:     None                                                     //
//  Description:    Attempt to re-synch communications.                      //
//---------------------------------------------------------------------------//
extern "C" void FixSioError(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcShutdown                                              //
//  Return Value:   None                                                     //
//  Parameters:     None                                                     //
//  Description:    Resets controllers assuming a default group address of   //
//                  0xFF, then closes COM port in use.                       //
//---------------------------------------------------------------------------//
extern "C" void NmcShutdown(void);

//Module type independant commands (supported by all module types)
//---------------------------------------------------------------------------//
//  Function Name:  NmcSetGroupAddr                                          //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  groupaddr: module's group address (0x80-0xFF)            //
//                  leader: 1 = group leader, 0 = group member               //
//  Description:    Sets module's group address.                             //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcSetGroupAddr(byte addr, byte groupaddr, BOOL leader);

//---------------------------------------------------------------------------//
//  Function Name:  NmcDefineStatus                                          //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  statusitems: logical or of status items to be returned   //
//                               (from PIC-SERVO.H, PIC-STEP.H, or PIC-IO.H) //
//  Description:    Defines what status data is returned after each command  //
//                  packet sent.                                             //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcDefineStatus(byte addr, byte statusitems);

//---------------------------------------------------------------------------//
//  Function Name:  NmcReadStatus                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module addr (1-32)                                 //
//                  statusitems: logical or of status items to be returned   //
//                               (from PIC-SERVO.H, PIC-STEP.H, or PIC-IO.H) //
//  Description:    Returns the specified status items once.                 //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcReadStatus(byte addr, byte statusitems);

//---------------------------------------------------------------------------//
//  Function Name:  NmcSynchOutput                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     groupaddr: module addr (1-32) or group addr (0x80-0xFF)  //
//                  leaderaddr: if individual groupaddr: leaderaddr = addr   //
//                              if group groupaddr: leaderaddr = group leader//
//                              (if no group leader: leaderaddr = 0          //
//  Description:    Synchronous output command issued to groupaddr.  Status  //
//                  data goes to leaderaddr.  If no leader, use leaderaddr=0.//                        //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcSynchOutput(byte groupaddr, byte leaderaddr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcChangeBaud                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     groupaddr: group address (0x80 - 0xFF)                   //
//                  baudrate: 19200, 57600, 115200, 230400 (PIC-SERVO only)  //
//  Description:    Change the baud rate of all controllers with group       //
//                  address 'groupaddr' (should include all modules) and     //
//                  also changes host's baud rate.  There should be no group //
//                  leader for 'groupaddr'.                                  //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcChangeBaud(byte groupaddr, unsigned int baudrate);

//---------------------------------------------------------------------------//
//  Function Name:  NmcSynchInput                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     groupaddr: module addr (1-32) or group addr (0x80-0xFF)  //
//                  leaderaddr: if individual groupaddr: leaderaddr = addr   //
//                              if group groupaddr: leaderaddr = group leader//
//                              (if no group leader: leaderaddr = 0          //
//  Description:    Synchronous input command issued to groupaddr.  Status   //
//                  data goes to leaderaddr.  If no leader, use leaderaddr=0.//
//---------------------------------------------------------------------------//
extern "C" BOOL NmcSynchInput(byte groupaddr, byte leaderaddr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcNoOp                                                  //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module addr (1-32)                                 //
//  Description:    No operation - module returns it's current status.       //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcNoOp(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcHardReset                                             //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32) or group address (0x80-0xFF) //
//  Description:    Resets all controllers with group address 'addr'         //
//                  (should include all modules).                            //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcHardReset(byte addr);

//Retrieve module type independant data from a module's data structure

//---------------------------------------------------------------------------//
//  Function Name:  NmcGetStat                                               //
//  Return Value:   Current status byte (stored locally) of a controller     //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the module's current status byte.                //
//---------------------------------------------------------------------------//
extern "C" byte NmcGetStat(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcGetStatItems                                          //
//  Return Value:   Byte specifying default status items                     //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the byte specifying which default status items   //
//                  are returned in a module's status data packet.           //
//---------------------------------------------------------------------------//
extern "C" byte NmcGetStatItems(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcGetModType                                            //
//  Return Value:   module type (0=PIC-SERVO, 2=PIC-IO, 3=PIC-STEP)          //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns the module type of a specified module.           //
//---------------------------------------------------------------------------//
extern "C" byte NmcGetModType(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcGetModVer                                             //
//  Return Value:   module version (stored as integer is single byte)        //
//  Parameters:     addr: module type (1-32)                                 //
//  Description:    Returns the firmware version of the specified module.    //
//---------------------------------------------------------------------------//
extern "C" byte NmcGetModVer(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcGetGroupAddr                                          //
//  Return Value:   group address (0x80 - 0xFF)                              //
//  Parameters:     addr: module address (1 - 32)                            //
//  Description:    Returns the group address of the specified module.       //
//---------------------------------------------------------------------------//
extern "C" byte NmcGetGroupAddr(byte addr);

//---------------------------------------------------------------------------//
//  Function Name:  NmcGroupLeader                                           //
//  Return Value:   0=module is not group leader, 1=module is group leader   //
//  Parameters:     addr: module address (1-32)                              //
//  Description:    Returns true if the specified module is a group leader,  //
//                  otherwise false.                                         //
//---------------------------------------------------------------------------//
extern "C" BOOL NmcGroupLeader(byte addr);

//Returns a reference to the ComPort in order for it to be used in picservo.h for reading purposes
extern "C" QextSerialPort* getComPort();

