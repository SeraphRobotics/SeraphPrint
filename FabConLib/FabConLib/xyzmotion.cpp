#include "xyzmotion.h"
#include "jsnpath.h"
#include <stdio.h>
#include <math.h>

XYZMotion::XYZMotion() :acceleration_(0),statesize_(0),frequency_(30.0)
{
}

XYZMotion::XYZMotion(const QDomNode& sourceDomNode):statesize_(0){
    QDomNodeList bayChildren = sourceDomNode.childNodes();
    for(int i=0; i<bayChildren.length();i++){
        QDomNode bchild = bayChildren.at(i);
        if (bchild.isComment()){continue;}
        if ("acceleration" == bchild.nodeName().toLower()){
            acceleration_ = bchild.toElement().text().toDouble();
        }else if("axis" == bchild.nodeName().toLower()){
            axis a;
            QDomNodeList bchildren = bchild.childNodes();
            for(int j=0;j<bchildren.size();j++){
                 QDomNode achild = bchildren.at(j);
                if(achild.isComment()){continue;}
                if("actuatorid"==achild.nodeName().toLower()){
                    a.actuatorID = achild.toElement().text().toInt();
                }else if ("revolutionsperdistance"==achild.nodeName().toLower()){
                    a.revPerDist = achild.toElement().text().toDouble();
                }else if ("range"==achild.nodeName().toLower()){
                    a.range = achild.toElement().text().toDouble();
                }else if ("name"== achild.nodeName().toLower()){
                    a.name = achild.toElement().text().toLower();
                }
            }
            axismap_[a.name] = a;


        }
    }

}

void XYZMotion::setAxes(QMap<QString,axis> axismap){
    foreach(QString s,axismap.keys()){
        axismap_[s.toLower()]=axismap[s];
    }
}


void XYZMotion::setAcceleration(double a){
    if (0!=a){acceleration_=a;}
}
double XYZMotion::getAcceleration()const{
    return acceleration_;
}

void XYZMotion::setFrequency(int frequency){
    frequency_=frequency;
}

void XYZMotion::setIdMap(QMap<int,int> map){
    idToStateIndex_ = map;
    statesize_ = map.keys().size()+1;
}

void XYZMotion::accelerateAlong(NPath* np, QList<Point> accel_list, double dist_a,bool deccel){
    /*
    Target Points are the state locaitonsi n XYZ
    Waypoints are the points in the path list
    The goal is to accelerate along the waypoints.
    */
    QListIterator<Point> accelIt(accel_list);
    Point lastpoint;
    Point curpoint;
    Point between_point;

    State tempState(statesize_,0.0);
    double coef= acceleration_/2.0/frequency_/frequency_;
    double v0=0;

    double dt=1.0/frequency_;
    double t1  = sqrt(2.0*dist_a/acceleration_);
    double timesteps = floor(t1*frequency_);

    double ri=0; //1/2*A*t_i^2  total distance from origin along the path to targetpoint
    double Rj=0; //sum(Dn,J)  total distance along waypoints to waypoint j
    double di=0; // r_i - Rj  Distance between current waypoint and target position
    double dj=0; // distance between current waypoint and the next

    if (deccel){
        v0 = acceleration_*t1/frequency_;
        coef = -coef;// Invert for decelleration
    }


    lastpoint = accelIt.next();
    curpoint = accelIt.next();
    dj = distance(lastpoint,curpoint);
    for (int i=1;i<=timesteps;i++){
        ri = v0*i + coef*i*i;
        di = ri-Rj;

        if(di>dj && accelIt.hasNext()){
            dj = distance(lastpoint,curpoint);
            Rj +=dj;
            lastpoint = curpoint;
            curpoint = accelIt.next();
            di = ri-Rj;
        }
        between_point = pointBetween(lastpoint,curpoint,di);
        tempState = positionToState(between_point.x,between_point.y,between_point.z);
        tempState[0] = dt;
        np->addState(State(tempState));
    }
}

NPath XYZMotion::pathAlong(XDFLPath path,double speed){

//    XDFLPath grPath = path.getAsGlobalRelative();
    Point origin = path.start();
    if (0==acceleration_ || 0==frequency_){return NPath(statesize_);}

    speed = fabs(speed);
    NPath np(statesize_,false);
    State tempState(statesize_,0.0);
    double dist=0;
    double dist_a = speed*speed/2.0/acceleration_;
    double dj=0;
    path.toRelative();
    QList<Point> points = path.getGlobalRelativePoints();
    Point lastpoint = points.first();
    Point curpoint;
    QList<Point> accel_list;
    QList<Point> deccel_list;
    QList<Point> coast_list;

    //Ensure that the system can accelerate over the distance of the path
    if(path.length()<2.0*dist_a){
        dist_a = .5*path.length();
    }


    //Populate acceleration list and find endpoint of acceleration
    int accelInt=0;
    for(accelInt=0;accelInt<points.length();accelInt++){

        if (dist + distance(lastpoint,points[accelInt]) >= dist_a) {
            double d = dist_a-dist;
            Point accelstop = pointBetween(lastpoint,points[accelInt],d);
            accel_list.append(accelstop);
            break;
        }
        dist += distance(lastpoint,points[accelInt]);
        accel_list.append(points[accelInt]);
        lastpoint = points[accelInt];
    }


    //Populate decceleration list and find startpoint of decceleration
    int deccelInt=0;
    dist=0;
    lastpoint=points.last();
    for(deccelInt=points.length()-1;deccelInt>-1;deccelInt--){
        if (dist + distance(lastpoint,points[deccelInt]) >= dist_a) {
            double d = dist_a-dist;
            Point accelstop = pointBetween(lastpoint,points[deccelInt],d);
            deccel_list.prepend(accelstop);

            break;
        }
        dist += distance(lastpoint,points[deccelInt]);
        deccel_list.prepend(points[deccelInt]);
        lastpoint = points[deccelInt];
    }

    // Populate coasting list
    coast_list.append(accel_list.last());

    for(int i=accelInt;i<deccelInt+1;i++){
        coast_list.append(points[i]);
    }
    coast_list.append(deccel_list.first());


//    {//TESTING
//    printf("\nACCELERATION size:%i",accel_list.length());
//    for(int i=0;i<accel_list.length();i++){
//        Point p=accel_list.at(i);
//        printf("\n\t %f, %f, %f",p.x,p.y,p.z);
//    }

//    printf("\n\nCOAST size:%i",coast_list.length());
//    for(int i=0;i<coast_list.length();i++){
//        Point p=coast_list.at(i);
//        printf("\n\t %f, %f, %f",p.x,p.y,p.z);
//    }

//    printf("\n\nDECEL size:%i",deccel_list.length());
//    for(int i=0;i<deccel_list.length();i++){
//        Point p=deccel_list.at(i);
//        printf("\n\t %f, %f, %f",p.x,p.y,p.z);
//    }
//    }


    accelerateAlong(&np,accel_list,dist_a,false);//acceleration


    //Coasting
    if (coast_list.size()>1){
        QListIterator<Point> coasting(coast_list);
        lastpoint = coast_list.first();
        curpoint = coasting.next();
        while (coasting.hasNext()){
            lastpoint = curpoint;
            curpoint = coasting.next();
            tempState = positionToState(curpoint.x,curpoint.y,curpoint.z);
            dj = distance(lastpoint,curpoint);
            tempState[0] = dj/speed; // TODO: this could lead to problems it dt<1/30
            np.addState(State(tempState));
        }
    }
    //deceleration
    accelerateAlong(&np,deccel_list,dist_a,true);

    State temp = positionToState(origin.x,origin.y,origin.z);
    np.setOrigin(temp);
    np.toRelative();
    return np;


}


NPath XYZMotion::pathTo(double x, double y, double z, double speed){
    // see http://people.mech.kuleuven.be/~bruyninc/blender/doc/interpolation-api.html#trapezoidal-velocity
    // dx_i = x_i/dist*a^2/(v^2*f^2)*(2i-1)


    NPath np(statesize_,false);
    double dist = sqrt(x*x+y*y+z*z);
    if (0==acceleration_ || 0==frequency_ || 0==speed || 0==dist){return NPath(statesize_);}
    double dist_a = speed*speed/acceleration_/2.0;
    double dist_v =0;
    int xindex = idToStateIndex_[axismap_["x"].actuatorID];
    int yindex = idToStateIndex_[axismap_["y"].actuatorID];
    int zindex = idToStateIndex_[axismap_["z"].actuatorID];
    double xscale = axismap_["x"].revPerDist;
    double yscale = axismap_["y"].revPerDist;
    double zscale = axismap_["z"].revPerDist;
    double norm_x = x/dist;
    double norm_y = y/dist;
    double norm_z = z/dist;
    double coef=0;
    double timesteps=0;
    double dt=0;
    double v1 =0;
    double x1 = 0;

    //    double D=0;

    State tempState(statesize_,0.0);
    coef = acceleration_/2.0/frequency_/frequency_;
    dt = 1.0/frequency_;

    if(dist<dist_a*2){// Special case, acceleration distance is larger than distance
        dist_a = dist/2.0;
        double t1  = sqrt(2.0*dist_a/acceleration_);
        timesteps = floor(t1*frequency_);

        v1 = acceleration_*t1;
        x1 = acceleration_/2.0*t1*t1;
        for (int i=0;i<=timesteps;i++){
            tempState[0] = 1.0/frequency_;
            tempState[xindex] = xscale*norm_x*coef*i*i;
            tempState[yindex] = yscale*norm_y*coef*i*i;
            tempState[zindex] = zscale*norm_z*coef*i*i;
            np.addState(State(tempState));
            //            D=sqrt(norm_x*xscale*(coef*i*i)*norm_x*xscale*(coef*i*i)
            //                   + norm_y*yscale*(coef*i*i)*norm_y*yscale*(coef*i*i)
            //                   + norm_z*zscale*(coef*i*i)*norm_z*zscale*(coef*i*i));
            //            printf("\nD:%f",D);

        }

        //deceleration
        for (int i=0;i<timesteps+1;i++){
            tempState[0] = 1.0/frequency_;
            tempState[xindex] = norm_x*xscale*(x1+v1*i*dt-coef*i*i);//(2.0*i-1.0);
            tempState[yindex] = norm_y*yscale*(x1+v1*i*dt-coef*i*i);//(2.0*i-1.0);
            tempState[zindex] = norm_z*zscale*(x1+v1*i*dt-coef*i*i);//(2.0*i-1.0);
            np.addState(State(tempState));
            //            D=sqrt(norm_x*xscale*(x1+v1*i*dt-coef*i*i)*norm_x*xscale*(x1+v1*i*dt-coef*i*i)
            //                   + norm_y*yscale*(x1+v1*i*dt-coef*i*i)*norm_y*yscale*(x1+v1*i*dt-coef*i*i)
            //                   + norm_z*zscale*(x1+v1*i*dt-coef*i*i)*norm_z*zscale*(x1+v1*i*dt-coef*i*i));
            //            printf("\nD:%f",D);
            //            printf("\nD:%f\tdy:%f\tdist:%f\trevy:%f\tvy:%f",D,norm_y*coef*i*i,norm_y*coef*(2*i-1),norm_y*coef*(2*i-1)*yscale,norm_y*coef*(2*i-1)*frequency_);
        }

        // make sure to end on the target point
        tempState[0] = 1.0/frequency_;
        tempState[xindex] = xscale*x;
        tempState[yindex] = yscale*y;
        tempState[zindex] = zscale*z;
        np.addState(State(tempState));
        //        D=sqrt(xscale*x*xscale*x+yscale*y*yscale*y+zscale*z*zscale*z);
        //        printf("\n D:%f",D);

    } else{
        //make the ramp up .

        dist_v = dist-2.0*dist_a;
        double t1  = speed/acceleration_;
        timesteps = floor(t1*frequency_);

        v1 = acceleration_*t1;
        x1 = acceleration_/2.0*t1*t1;

        for (int i=0;i<=timesteps;i++){
            tempState[0] = 1.0/frequency_;
            tempState[xindex] = xscale*norm_x*coef*i*i;
            tempState[yindex] = yscale*norm_y*coef*i*i;
            tempState[zindex] = zscale*norm_z*coef*i*i;
            //            D=sqrt(norm_x*xscale*(coef*i*i)*norm_x*xscale*(coef*i*i)
            //                   + norm_y*yscale*(coef*i*i)*norm_y*yscale*(coef*i*i)
            //                   + norm_z*zscale*(coef*i*i)*norm_z*zscale*(coef*i*i));
            //            printf("\nD:%f",D);
            np.addState(State(tempState));
        }

        // coast state;
        double x2=x1+dist_v;
        tempState[0] = dist_v/speed;
        tempState[xindex] = x2*norm_x*xscale;
        tempState[yindex] = x2*norm_y*yscale;
        tempState[zindex] = x2*norm_z*zscale;
        np.addState(State(tempState));
        //        D=x2;
        //        printf("\n\nD:%f\n",D);


        //Ramp down
        for (int i=1;i<timesteps;i++){
            tempState[0] = 1.0/frequency_;
            tempState[xindex] = norm_x*xscale*(x2+speed*i*dt-coef*i*i);//(2.0*i-1.0);
            tempState[yindex] = norm_y*yscale*(x2+speed*i*dt-coef*i*i);//(2.0*i-1.0);
            tempState[zindex] = norm_z*zscale*(x2+speed*i*dt-coef*i*i);//(2.0*i-1.0);
            np.addState(State(tempState));
            //            D=sqrt(norm_x*xscale*(x2+speed*i*dt-coef*i*i)*norm_x*xscale*(x2+speed*i*dt-coef*i*i)
            //                   + norm_y*yscale*(x2+speed*i*dt-coef*i*i)*norm_y*yscale*(x2+speed*i*dt-coef*i*i)
            //                   + norm_z*zscale*(x2+speed*i*dt-coef*i*i)*norm_z*zscale*(x2+speed*i*dt-coef*i*i));
            //            printf("\nD:%f",D);
        }
        tempState[0] = 1.0/frequency_;
        tempState[xindex] = xscale*x;
        tempState[yindex] = yscale*y;
        tempState[zindex] = zscale*z;
        np.addState(State(tempState));
        np.addState(State(tempState));
        //        D=sqrt(xscale*x*xscale*x+yscale*y*yscale*y+zscale*z*zscale*z);
        //        printf("\n D:%f",D);
    }
    //    printf("\ndistA: %f",dist_a);
    //    printf("\nTimeSteps:%f",timesteps);
    //    printf("\ndt:%f",1.0/frequency_);
    np.toRelative();
    return np;
}


State XYZMotion::positionToState(double x,double y,double z){
    int xindex = idToStateIndex_[axismap_["x"].actuatorID];
    double xscale = axismap_["x"].revPerDist;
    int yindex = idToStateIndex_[axismap_["y"].actuatorID];
    double yscale = axismap_["y"].revPerDist;
    int zindex = idToStateIndex_[axismap_["z"].actuatorID];
    double zscale = axismap_["z"].revPerDist;
    State temp(statesize_,0.0);
    temp[xindex] = x*xscale;
    temp[yindex] = y*yscale;
    temp[zindex] = z*zscale;
    return temp;
}

double XYZMotion::distanceFromState(State* state){
    int xindex = idToStateIndex_[axismap_["x"].actuatorID];
    double xscale = axismap_["x"].revPerDist;
    int yindex = idToStateIndex_[axismap_["y"].actuatorID];
    double yscale = axismap_["y"].revPerDist;
    int zindex = idToStateIndex_[axismap_["z"].actuatorID];
    double zscale = axismap_["z"].revPerDist;
    double x,y,z;
    x = state->at(xindex)/xscale;
    y = state->at(yindex)/yscale;
    z = state->at(zindex)/zscale;
    return sqrt(x*x+y*y+z*z);


}
