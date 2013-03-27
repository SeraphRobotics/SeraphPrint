#include "coordinatedmotion.h"
#include <math.h>
#include <QTextStream>
#include <QDebug>

CoordinatedMotion::CoordinatedMotion():initialized_(false),pathbegan_(false),frequency_(P_30HZ)
{
}


CoordinatedMotion::CoordinatedMotion(QMap<int,Motor*> motors):initialized_(false), motors_(motors),pathbegan_(false),frequency_(P_30HZ){}

void CoordinatedMotion::setMotors(QMap<int,Motor*> motors)
{
    motors_=motors;

    backlash_vector = State(motors.size()+1,0.0);
    appliedLash_=State(motors.size()+1,0.0);

    //Reset position of all motors.
    QMapIterator<int,Motor*> i(motors_);
    while(i.hasNext()){
        i.next();
        i.value()->resetPosition(); // reset motors
        addressMap[i.key()] = i.value()->getAddress(); //populate address map for integer of the state variable to the motor address
        scales[i.key()]=i.value()->getCountsPerRev(); //populate the scaling factors for the motors
        backlash_vector[i.key()]=i.value()->getBacklash();
    }
}

State CoordinatedMotion::getAppliedLash(){
    return State(appliedLash_);
}


NPath CoordinatedMotion::applyBacklash(NPath path){
    /**
     * a change of direction is when sign(Vi-1) != sign(Vi)
     * singe sign is not dependant on the dt component due to time being unidirectional
     * It is possible to compare signs of the delta
     * so change of direction when sign(dXi-1) != sign(dXi)
     **/

    path.toRelative();
    NPath newpath(path.stateSize(),true);
    newpath.setOrigin(path.origin());


    for(int i=0;i<path.numberOfStates();i++){
        State currentState = path.getState(i);
        State newstate = copyState(currentState);
        //detect and apply backlash
        for(int j=1;j<path.stateSize();j++){
            int signLash = (appliedLash_[j] > 0) - (appliedLash_[j] < 0);
            int signVc = (currentState[j] > 0) - (currentState[j] < 0);
            if ((signLash!=signVc) && (fabs(signVc)>0) ){//&&(fabs(currentState[j]-previousState[j])>0.0001)
                newstate[j]=currentState[j]+signVc*backlash_vector[j];
                appliedLash_[j]+= signVc*backlash_vector[j];
                qDebug()<<"\tLASH"<<j<<appliedLash_[j]<<"\t"<<currentState.at(j)<<"\t"<<newstate.at(j);
            }
        }
        newpath.addState(newstate);
    }
    return newpath;

}


State CoordinatedMotion::currentState() {
    State cp(getStateSize(),0.0);
    QMapIterator<int,Motor*> i(motors_);
    while(i.hasNext()) {
        i.next();
        double p = i.value()->getPosition();
        cp[i.key()]=p;
    }
    return cp;
}


int CoordinatedMotion::getStateSize()
{
    return getNumberOfAxes()+1;
}

int CoordinatedMotion::getNumberOfAxes()
{
    return motors_.size();
}

void CoordinatedMotion::setGroupAddress(byte address)
{
    X_Y_Z_GROUP_ADDRESS = address;
}

void CoordinatedMotion::setBufferSize(int buffsize)
{
    BUFF_SIZE = buffsize;
}

void CoordinatedMotion::setFrequency(int frequency)
{
    frequency_=frequency;
}

int CoordinatedMotion::getFrequency(){
    return frequency_;
}

bool CoordinatedMotion::initializePathMode()
{

    if(initialized_){return true;}
    // Check to see if sufficent number of motors have been added
    if ((motors_.size()<3)||!X_Y_Z_GROUP_ADDRESS){
        qDebug("Not enough motors");
        error_string = "not enough motors";
        return false;
    }


    bool tempInitialized=true;

    QMapIterator<int,Motor*> j(motors_);
    while(j.hasNext()){
        j.next();

        tempInitialized = tempInitialized && j.value()->setGroup(X_Y_Z_GROUP_ADDRESS,(j.key()==1));// the i.key()==1 sets id 1 as the group leader
    }
    initialized_= tempInitialized &&
                  NP::SetPathParams(
                    getNumberOfAxes(),
                    frequency_, //path frequency
                    BUFF_SIZE,
                    //Max number of points in the path point buffer at one time.  Max value is 87.
                    //A higher value results in longer downloads to the path point buffer.
                    addressMap,
                    X_Y_Z_GROUP_ADDRESS,
                    motors_[1]->getAddress(), //group leader
                    scales,
                    &error_string
                    ) == 0;
    if(!initialized_){error_string = "failed to initialize pathmode";}
    return initialized_;
}



bool CoordinatedMotion::moveAlongPath(NPath states){
    return moveAlongPath(states,0);
}

bool CoordinatedMotion::moveAlongPath(NPath states,int startPointIndex){
    if(states.numberOfStates() == 0) {return false;}
    if(!validateNPath(states)){
        error_string+=" STATES INVALID";
        return false;
    }

    qDebug()<<"\nPath";
    NPath newstates = applyBacklash(states);
    NP::HzPath hpath = NP::toHzPath(&newstates,startPointIndex);
    
    if (!pathbegan_){
        NP::InitPath(&error_string);
        pathbegan_=true;
    }
    NP::AddStates(hpath);
    int result = NP::DlPathPoints(&error_string);   //send path points to the printer and start path
    if (result == -2) error_string += "\n error adding points";
    return true;
}

bool CoordinatedMotion::resetPosition(){

    pathbegan_=(bool) NP::InitPath(&error_string);
    return pathbegan_;
}


QString CoordinatedMotion::getErrors(){
    return error_string;
}


bool CoordinatedMotion::validateNPath(NPath path){
    if (path.stateSize()!=(motors_.size()+1)){return false;}

    path.toRelative();
    double dt = 0;
    double v=0,a=0,v0=0;
    double maxv=0,maxa=0;
    double dx=0;

    State laststate = State(path.stateSize(),0.0);
    for(int j=0;j<path.numberOfStates();j++){
        State curstate = path.getState(j);
        dt = curstate.at(0);
        if (0==dt){dt=1.0/30.0;}
        for(int i=1;i<(motors_.size()+1);i++){
            dx = curstate.at(i);
            maxv=motors_[i]->getMaxVelocity();
            maxa=motors_[i]->getMaxAcceleration();
            v = dx/dt;
            v0 = laststate.at(i) -laststate.at(0);
            a = fabs(v-v0)/frequency_;
            if (v>maxv){
                QTextStream ss(&error_string,QIODevice::ReadOnly);
                ss<<"\t V>Vmax V is"<<v<<"VMax is "<<maxv<<"\t State: "<<j;
                qDebug()<<"\t V>Vmax V is"<<v<<"VMax is "<<maxv<<"\t State: "<<j;
                return false;}
            if (a>maxa){
                QTextStream ss(&error_string,QIODevice::ReadOnly);
                ss<<"\t A>Amax A is"<<a<<"AMax is "<<maxa<<"\t State:"<<j;
                qDebug()<<"\t A>Amax A is"<<a<<"AMax is "<<maxa<<"\t State:"<<j;
                return false;}
        }
    }
    return true;
}


QMap<int,int> CoordinatedMotion::getIdToStateIndexMap(){
    QMap<int,int> idToState;
    foreach(int state,motors_.keys()){
        int id = motors_[state]->getID();
        idToState[id]=state;
    }
    return idToState;
}
