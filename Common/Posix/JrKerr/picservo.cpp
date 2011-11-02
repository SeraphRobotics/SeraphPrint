//---------------------------------------------------------------------------

#include "nmccom.h"
#include "picservo.h"
#include "qextserialport.h"
#include <stdio.h>
#include <unistd.h>
#include <QDebug>

//---------------------------------------------------------------------------
extern NMCMOD	mod[]; 		//Array of modules
extern int nummod;

//---------------------------------------------------------------------------
//Returns pointer to an initialized IOMOD structure
extern "C" SERVOMOD * ServoNewMod()
{
SERVOMOD *p;

p = new SERVOMOD;
p->pos = 0;
p->ad = 0;
p->vel = 0;
p->aux = 0;
p->home = 0;
p->perror = 0;
p->cmdpos = 0;
p->cmdvel = 0;
p->cmdacc = 0;
p->cmdpwm = 0;

(p->gain).kp = 0;
(p->gain).kd = 0;
(p->gain).ki = 0;
(p->gain).il = 0;
(p->gain).ol = 0;
(p->gain).cl = 0;
(p->gain).el = 0;
(p->gain).sr = 1;
(p->gain).dc = 0;
(p->gain).sm = 1;

p->stoppos = 0;
p->ioctrl = 0;
p->homectrl = 0;
p->movectrl = 0;
p->stopctrl = 0;
p->ph_adv = 0;
p->ph_off = 0;
return p;
}

//---------------------------------------------------------------------------
extern "C" BOOL ServoGetStat(byte addr)
{
int numbytes, numrcvd;
int i, bytecount;
byte cksum;
byte inbuf[20];
SERVOMOD *p;
//char msgstr[80];

p = (SERVOMOD *)(mod[addr].p);  //cast the data pointer to the right type


//Find number of bytes to read:
numbytes = 2;       //start with stat & cksum
if ( (mod[addr].statusitems) & SEND_POS )	numbytes +=4;
if ( (mod[addr].statusitems) & SEND_AD ) 	numbytes +=1;
if ( (mod[addr].statusitems) & SEND_VEL ) 	numbytes +=2;
if ( (mod[addr].statusitems) & SEND_AUX ) 	numbytes +=1;
if ( (mod[addr].statusitems) & SEND_HOME )	numbytes +=4;
if ( (mod[addr].statusitems) & SEND_ID ) 	numbytes +=2;
if ( (mod[addr].statusitems) & SEND_PERROR ) numbytes +=2;
if ( (mod[addr].statusitems) & SEND_NPOINTS ) numbytes +=1;
QextSerialPort* ComPort = getComPort();

for (i = 0, numrcvd = 0; i < numbytes; i++)
{
    byte* temp = &inbuf[i];
    if (ComPort->read((char *) temp, 1)) numrcvd++;
}


//Verify enough data was read
if (numrcvd != numbytes)
	{
    qDebug() << "ServoGetStat " << addr << " failed to read chars";
    qDebug() << "Read " << numrcvd << " bytes out of " << numbytes << " bytes.";
    return false;
    }

//Verify checksum:
cksum = 0;
for (i=0; i<numbytes-1; i++) cksum = (byte)(cksum + inbuf[i]);
if (cksum != inbuf[numbytes-1])
	{
    qDebug() << "ServoGetStat" << addr << ": checksum error";
    return false;
    }

//Verify command was received intact before updating status data
mod[addr].stat = inbuf[0];
if (mod[addr].stat & CKSUM_ERROR)
	{
    qDebug() << "Command checksum error!";
    return false;
    }

//Finally, fill in status data
bytecount = 1;
if ( (mod[addr].statusitems) & SEND_POS )
	{
        p->pos = *( (int *)(inbuf + bytecount) );
    bytecount +=4;
    }
if ( (mod[addr].statusitems) & SEND_AD )
	{
    p->ad = inbuf[bytecount];
    bytecount +=1;
    }
if ( (mod[addr].statusitems) & SEND_VEL )
	{
	p->vel = *( (short int *)(inbuf + bytecount) );
    bytecount +=2;
    }
if ( (mod[addr].statusitems) & SEND_AUX )
	{
    p->aux = inbuf[bytecount];
    bytecount +=1;
    }
if ( (mod[addr].statusitems) & SEND_HOME )
	{
    p->home = *( (unsigned int *)(inbuf + bytecount) );
    bytecount +=4;
    }
if ( (mod[addr].statusitems) & SEND_ID )
	{
    mod[addr].modtype = inbuf[bytecount];
    mod[addr].modver = inbuf[bytecount+1];
    bytecount +=2;
    }
if ( (mod[addr].statusitems) & SEND_PERROR )
	{
	p->perror = *( (short int *)(inbuf + bytecount) );
    bytecount +=2;
    }
if ( (mod[addr].statusitems) & SEND_NPOINTS )
	{
    byte temp = inbuf[bytecount];
    p->npoints = inbuf[bytecount];
    //bytecount +=1;
    }

return(true);
}
//---------------------------------------------------------------------------
extern "C" int ServoGetPos(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->pos;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetAD(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->ad;
}
//---------------------------------------------------------------------------
extern "C" short int ServoGetVel(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->vel;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetAux(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->aux;
}
//---------------------------------------------------------------------------
extern "C" int ServoGetHome(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->home;
}
//---------------------------------------------------------------------------
extern "C" short int ServoGetPError(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->perror;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetNPoints(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->npoints;
}
//---------------------------------------------------------------------------
extern "C" int ServoGetCmdPos(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->cmdpos;
}
//---------------------------------------------------------------------------
extern "C" int ServoGetCmdVel(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->cmdvel;
}
//---------------------------------------------------------------------------
extern "C" int ServoGetCmdAcc(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->cmdacc;
}
//---------------------------------------------------------------------------
extern "C" int ServoGetStopPos(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->stoppos;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetCmdPwm(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->cmdpwm;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetIoCtrl(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->ioctrl;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetHomeCtrl(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->homectrl;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetStopCtrl(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->stopctrl;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetMoveCtrl(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->movectrl;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetPhAdv(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->ph_adv;
}
//---------------------------------------------------------------------------
extern "C" byte ServoGetPhOff(byte addr)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
return p->ph_off;
}
//---------------------------------------------------------------------------
extern "C" void ServoGetGain(byte addr, short int * kp, short int * kd, short int * ki,
				  short int * il, byte * ol, byte * cl, short int * el,
                  byte * sr, byte * dc)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
*kp = (p->gain).kp;
*kd = (p->gain).kd;
*ki = (p->gain).ki;
*il = (p->gain).il;
*ol = (p->gain).ol;
*cl = (p->gain).cl;
*el = (p->gain).el;
*sr = (p->gain).sr;
*dc = (p->gain).dc;
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoSetGain(byte addr, short int kp, short int kd, short int ki,
				  short int il, byte ol, byte cl, short int el,
                  byte sr, byte dc)
{
SERVOMOD * p;
char cmdstr[16];

p = (SERVOMOD *)(mod[addr].p);
//TODO: break out of method if there is a segmentation fault
(p->gain).kp = kp;
(p->gain).kd = kd;
(p->gain).ki = ki;
(p->gain).il = il;
(p->gain).ol = ol;
(p->gain).cl = cl;
(p->gain).el = el;
(p->gain).sr = sr;
(p->gain).dc = dc;

*( (short int *)(cmdstr) ) = kp;
*( (short int *)(cmdstr+2) ) = kd;
*( (short int *)(cmdstr+4) ) = ki;
*( (short int *)(cmdstr+6) ) = il;
*( (byte *)(cmdstr+8) ) = ol;
*( (byte *)(cmdstr+9) ) = cl;
*( (short int *)(cmdstr+10) ) = el;
*( (byte *)(cmdstr+12) ) = sr;
*( (byte *)(cmdstr+13) ) = dc;


usleep(51000);


return NmcSendCmd(addr, SET_GAIN, cmdstr, 14, addr);
}
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
							   byte * sr, byte * dc, byte * sm)
{
	SERVOMOD * p;
	
	p = (SERVOMOD *)(mod[addr].p);
	*kp = (p->gain).kp;
	*kd = (p->gain).kd;
	*ki = (p->gain).ki;
	*il = (p->gain).il;
	*ol = (p->gain).ol;
	*cl = (p->gain).cl;
	*el = (p->gain).el;
	*sr = (p->gain).sr;
	*dc = (p->gain).dc;
	*sm = (p->gain).sm;
}
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
							   byte sr, byte dc, byte sm)
{
	SERVOMOD * p;
	char cmdstr[16];
	
	p = (SERVOMOD *)(mod[addr].p);
	(p->gain).kp = kp;
	(p->gain).kd = kd;
	(p->gain).ki = ki;
	(p->gain).il = il;
	(p->gain).ol = ol;
	(p->gain).cl = cl;
	(p->gain).el = el;
	(p->gain).sr = sr;
	(p->gain).dc = dc;
	(p->gain).sm = sm;
	
	*( (short int *)(cmdstr) ) = kp;
	*( (short int *)(cmdstr+2) ) = kd;
	*( (short int *)(cmdstr+4) ) = ki;
	*( (short int *)(cmdstr+6) ) = il;
	*( (byte *)(cmdstr+8) ) = ol;
	*( (byte *)(cmdstr+9) ) = cl;
	*( (short int *)(cmdstr+10) ) = el;
	*( (byte *)(cmdstr+12) ) = sr;
	*( (byte *)(cmdstr+13) ) = dc;
	*( (byte *)(cmdstr+14) ) = sm;
	
	return NmcSendCmd(addr, SET_GAIN, cmdstr, 15, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoLoadTraj(byte addr, byte mode, int pos, int vel, int acc, byte pwm)
{
SERVOMOD * p;
char cmdstr[16];
int count;

p = (SERVOMOD *)(mod[addr].p);
p->movectrl = mode;
p->cmdpos = pos;
p->cmdvel = vel;
p->cmdacc = acc;
p->cmdpwm = pwm;

count = 0;
*( (byte *)(cmdstr + count) ) = mode;  count += 1;
if (mode & LOAD_POS) { *( (int *)(cmdstr + count) ) = pos; count += 4; }
if (mode & LOAD_VEL) { *( (int *)(cmdstr + count) ) = vel; count += 4; }
if (mode & LOAD_ACC) { *( (int *)(cmdstr + count) ) = acc; count += 4; }
if (mode & LOAD_PWM) { *( (byte *)(cmdstr + count) ) = pwm; count += 1; }

return NmcSendCmd(addr, LOAD_TRAJ, cmdstr, (byte)count, addr);
}
//---------------------------------------------------------------------------
extern "C" void ServoInitPath(byte addr)
{
SERVOMOD * p;

NmcReadStatus(addr, SEND_POS | SEND_PERROR);

p = (SERVOMOD *)(mod[addr].p);
p->last_ppoint = p->pos + p->perror;
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoAddPathpoints(byte addr, int npoints, int *path, int freq)
{
SERVOMOD * p;
char cmdstr[16];
int diff;
int rev;
int i;

//npoints must be greater than 0
if (npoints <= 0) return 0;

p = (SERVOMOD *)(mod[addr].p);

for (i=0; i<npoints; i++)
  {
  diff = path[i] - p->last_ppoint;
  if (diff<0)
    {
    rev = 0x01;
    diff = -diff;
    }
  else rev = 0x00;

  //Scale the difference appropriately for path freq. used
  if (p->ioctrl & FAST_PATH)  //scale for 60/120 Hz fast path
    {
    if (freq == P_60HZ)
      {
      diff *= (256/32);
      diff |= 0x02;     //60 Hz -> set bit 1 = 1
      }
    else if (freq == P_120HZ) diff *= (256/16);
    else return(false);
    }
  else  //scale for 30/60 Hz slow path
    {
    if (freq == P_30HZ)
      {
      diff *= (256/64);
      diff |= 0x02;     //30 Hz -> set bit 1 = 1
      }
    else if (freq == P_60HZ) diff *= (256/32);
    else return(false);
    }

  diff |= rev;  //bit 0 = reverse bit

  *( (short int *)(cmdstr + 2*i) ) = (short int)diff;

  p->last_ppoint = path[i];
  }


return NmcSendCmd(addr, ADD_PATHPOINT, cmdstr, (byte)(npoints*2), addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoStartPathMode(byte groupaddr, byte groupleader)
{
return NmcSendCmd(groupaddr, ADD_PATHPOINT, NULL, 0, groupleader);
}
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
extern "C" BOOL ServoStartMove(byte groupaddr, byte groupleader)
{
	return NmcSendCmd(groupaddr, START_MOVE, NULL, 0, groupleader);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoResetPos(byte addr)
{
return NmcSendCmd(addr, RESET_POS, NULL, 0, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoResetRelHome(byte addr)
{
byte mode;

mode = REL_HOME;
return NmcSendCmd(addr, RESET_POS, (char *)(&mode), 1, addr);
}
//---------------------------------------------------------------------------//
//  Function Name:  ServoSetPos                                              //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  pos: position (-2,147,483,648 - +2,147,483,647)          //
//  Description:    Sets the module position to the specified value.         //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoSetPos(byte addr, int pos)
{
	char cmdstr[6];
	
	cmdstr[0] = SET_POS;          //mode byte for reset pos
        *( (int *)(cmdstr + 1) ) = pos;
	
	return NmcSendCmd(addr, RESET_POS, cmdstr, 5, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoClearBits(byte addr)
{
return NmcSendCmd(addr, CLEAR_BITS, NULL, 0, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoStopMotor(byte addr, byte mode)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);

mode &= (byte)(~STOP_HERE);
p->stopctrl = mode;       //make sure STOP_HERE bit is cleared

return NmcSendCmd(addr, STOP_MOTOR, (char *)(&mode), 1, addr);
}
//---------------------------------------------------------------------------//
//  Function Name:  ServoStopHere                                            //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of the stop mode bits (see picservo.h)  //
//                  pos: unprofiled command position                         //
//  Description:    Stop the motor at the specified position.                //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoStopHere(byte addr, byte mode, int pos)
{
	SERVOMOD * p;
	char cmdstr[6];
	
	p = (SERVOMOD *)(mod[addr].p);
	
	p->stopctrl = mode;
	
	cmdstr[0] = mode;
        *( (int *)(cmdstr + 1) ) = pos;
	
	return NmcSendCmd(addr, STOP_MOTOR, cmdstr, 5, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoSetIoCtrl(byte addr, byte mode)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);

p->ioctrl = mode;

return NmcSendCmd(addr, IO_CTRL, (char *)(&mode), 1, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoSetHoming(byte addr, byte mode)
{
SERVOMOD * p;

p = (SERVOMOD *)(mod[addr].p);
p->homectrl = mode;

return NmcSendCmd(addr, SET_HOMING, (char *)(&mode), 1, addr);
}
//---------------------------------------------------------------------------
extern "C" BOOL ServoSetPhase(byte addr, int padvance, int poffset, int maxpwm)
{
int i;
char mode;
SERVOMOD * p;

if (maxpwm>255 || maxpwm<128) return(false);

p = (SERVOMOD *)(mod[addr].p);
p->ph_adv = (byte)padvance;
p->ph_off = (byte)poffset;


//First set PWM to 0:
ServoLoadTraj(addr, 0x88, 0, 0, 0, 0);  //set PWM to 0 now

//Set phase advance:
for (i=0; i<padvance; i++)
  {
  mode = 0xC0; 	//set dir bit hi
  NmcSendCmd(addr, 0x04, &mode, 1, addr);
  mode = 0x80; 	//set dir bit lo
  NmcSendCmd(addr, 0x04, &mode, 1, addr);
  }
//Toggle PWM high then low:
ServoLoadTraj(addr, 0x88, 0, 0, 0, 255);  //set PWM to 255 now
ServoLoadTraj(addr, 0x88, 0, 0, 0, 0);    //set PWM to 0 now

//Set index phasing count (icount):
for (i=0; i<poffset; i++)
  {
  mode = 0xC0; 	//set dir bit hi
  NmcSendCmd(addr, 0x04, &mode, 1, addr);
  mode = 0x80; 	//set dir bit lo
  NmcSendCmd(addr, 0x04, &mode, 1, addr);
  }

ServoClearBits(addr);  //Clear any position errors

for (i=127; i<=maxpwm; i++)    
  {
  ServoLoadTraj(addr, 0x88, 0, 0, 0, (byte)i);  //ramp up PWM to 255
  if ( (NmcGetStat(addr) & POS_ERR) )     //check if power still there
    {
    ServoLoadTraj(addr, 0x88, 0, 0, 0, 0);   // set PWM to zero on error
    break;
    }
  }

usleep(500);
return( ServoLoadTraj(addr, 0x88, 0, 0, 0, 0) );    //set PWM to 0 now

}
//---------------------------------------------------------------------------//
//  Function Name:  ServoHardReset                                           //
//  Return Value:   0=Fail, 1=Success                                        //
//  Parameters:     addr: module address (1-32)                              //
//                  mode: logical OR of reset control bits (see picservo.h)  //
//  Description:    Reset the controller to it's power-up state and          //
//                  optionally store configuration data in EEPROM.           //
//                  (Only valid for PIC-SERVO SC - v.10 and greater)         //
//---------------------------------------------------------------------------//
extern "C" BOOL ServoHardReset(byte addr, byte mode)
{
	return NmcSendCmd(addr, HARD_RESET, (char *)(&mode), 1, 0);
}
