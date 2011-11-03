//---------------------------------------------------------------------------
#ifndef PIC_SERVO_PATH_H
#define PIC_SERVO_PATH_H
//---------------------------------------------------------------------------
//Defines:

#include <QLibrary>

//Segment types:
#define LINE 0
#define ARC 1

#define MAXSEG 1000     //Maximum number of segments
#define PI 3.14159
#define TWOPI 6.28319
#define DTOR 0.017453

//Valuse for tangent tolerance
#define TAN_1DEGREE 0.99985
#define TAN_3DEGREE 0.99863
#define TAN_5DEGREE 0.99619
#define TAN_10DEGREE 0.98481
#define TAN_20DEGREE 0.93969
#define TAN_45DEGREE 0.70711

#define ONLINE 1
//---------------------------------------------------------------------------
//Data types:

typedef float fp[3];     //floating point 3x1 vector

typedef long int ip[3];  //integer 3x1 vector

typedef struct {         //data type for line segments or arc segments
                        int type;		//LINE or ARC
                        fp p1;          //Starting point
            fp p2;          //Ending point
            fp c;           //Center point (arcs only)
            fp norm;        //Normal vector (arcs only)
            float len;		//Segment length
            float r;		//Radius (arcs only)
            } segment;

typedef struct {         //data type for a coordinate frame
                        fp	x;
            fp	y;
            fp	z;
            fp	p;
            } frame;

//---------------------------------------------------------------------------


//Load functions from DLL.

static void (*SetTangentTolerance)(float) = reinterpret_cast<void(*)(float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","SetTangentTolerance"));
static void (*ClearSegList)(float,float,float) = reinterpret_cast<void(*)(float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","ClearSegList"));
static int (*AddLineSeg)(float,float,float) = reinterpret_cast<int(*)(float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","AddLineSeg"));
static int (*AddArcSeg)(float,float,float,float,float,float,float,float,float) = reinterpret_cast<int(*)(float,float,float,float,float,float,float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","AddArcSeg"));
static void (*SetFeedrate)(float) = reinterpret_cast<void(*)(float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","SetFeedrate"));
static void (*SetOrigin)(float,float,float) = reinterpret_cast<void(*)(float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","SetOrigin"));
static int (*SetPathParams)(int,int,int,int,int,int,int,float,float,float,float) = reinterpret_cast<int(*)(int,int,int,int,int,int,int,float,float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","SetPathParams"));
static int (*SetPathParams2)(int,int,int,int,int,int,int,float,float,float,float) = reinterpret_cast<int(*)(int,int,int,int,int,int,int,float,float,float,float)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","SetPathParams2"));
static float (*InitPath)(void) = reinterpret_cast<float(*)(void)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","InitPath"));
static int (*AddPathPoints)(void) = reinterpret_cast<int(*)(void)>(QLibrary::resolve("../Common/Windows/JrKerr/PATHLIB4","AddPathPoints"));



#endif //ndef PIC_SERVO_PATH_H
