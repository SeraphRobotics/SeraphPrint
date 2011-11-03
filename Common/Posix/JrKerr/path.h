//---------------------------------------------------------------------------
#ifndef pathH
#define pathH
//---------------------------------------------------------------------------
//Defines:

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

typedef int ip[3];  //integer 3x1 vector

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
//Function prototypes:
float mag(fp p);
float dot(fp x, fp y);
void cross(fp x, fp y, fp z);
float normalize(fp x, fp y);
void fvmult(frame *F, fp x, fp y);
void finvert(frame A, frame *B);
int GetTanVect(segment *s, fp p, int endpoint);
void GetArcFrame(segment *seg, frame *F);
void GetLineSegPoint(segment *seg, float s, fp p);
int GetNextPathpoint(int *xp, int *yp, int *zp);

//Path mode API functions:
extern "C" void SetTangentTolerance(float theta);

/**
  Clear the current segment list and initialize the starting point
 */
extern "C" void ClearSegList(float x, float y, float z);

   /**
     Add a line segment to the segment list
     @return position in segment list if OK
          -1 if segment is not tangent
          -2 if segment list is full
    Function assumes the normal vector of any previous arc segment is accurate
    */
extern "C" int AddLineSeg(float x, float y, float z);

extern "C" int AddArcSeg( float x, float y, float z,        //end point
                          float cx, float cy, float cz,     //center point
                          float nx, float ny, float nz );    //normal
/**
  Set feedrate in units per second
 */
extern "C" void SetFeedrate(float fr);
extern "C" void SetOrigin(float xoffset, float yoffset, float zoffset);
extern "C" int SetPathParams(int freq, int nbuf,
                             int xaxis, int yaxis, int zaxis, int groupaddr, int leaderaddr,
                             float xscale, float yscale, float zscale,
                             float accel );
  /**
    Initialize various parameters for this path generation module
    @return -1 if Status items are not set properly,
            -2 if scale facotrs are zero
   */
extern "C" int SetPathParams2(int freq, int nbuf,
                              int xaxis, int yaxis, int zaxis, int groupaddr, int leaderaddr,
                              float xscale, float yscale, float zscale,
                              float accel );
/**
  Starts the path execution once the buffer of points is full
 */
extern "C" float InitPath();

/**
  Adds the points of the path to a buffer until it is full
 */
extern "C" int AddPathPoints();

//---------------------------------------------------------------------------
#endif
