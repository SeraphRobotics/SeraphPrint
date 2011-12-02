#include "xdflpath.h"
#include <math.h>

XDFLPath::XDFLPath(int material_id,bool relative):points(),materialID(material_id),relative_(relative),speed(0)
{
}

XDFLPath::XDFLPath(const XDFLPath &path){
    materialID = path.materialID;
    points=QList<Point>::QList(path.points);
}

double XDFLPath::length(){
    if (points.isEmpty()){return 0;}
    Point lastpoint = points.at(0);
    double dist=0;
    for(int i=1; i<points.length(); i++){
        dist += distance(lastpoint,points.at(i));
        lastpoint = points.at(i);
    }
    return dist;
}
void XDFLPath::toRelative(){
    relative_ = true;
}
void XDFLPath::toAbsolute(){
    relative_ = false;
}

bool XDFLPath::isNull(){
    bool null;
    null = (points.length()<2)||((0==materialID)&&(0==speed));// false if points empty or if the matieral and speed are zero
    return null;
}

QList<Point> XDFLPath::getPoints(){
    QList<Point> returnPoints;
    if(relative_){
        Point p;
        Point p1;
        Point p2;
        p.x=0;
        p.y=0;
        p.z=0;
        returnPoints.append(p);
        for(int i=1;i<points.length();i++){
            p2 = points.at(i);
            p1 = points.at(i-1);
            returnPoints.append(subtractpoints(p2,p1));
        }
    }else{
        for(int i=0;i<points.length();i++){
            returnPoints.append(points.at(i));
        }
    }
    return returnPoints;
}

QList<Point> XDFLPath::getGlobalRelativePoints(){
    QList<Point> grpoints;
    Point origin = start();
    for(int i=0;i<points.length();i++){
        grpoints.append(subtractpoints(points.at(i),origin));
    }
    return grpoints;

}


Point XDFLPath::start(){
    Point p;
    p=points.first();
    return p;
}
Point XDFLPath::end(){
    Point p;
    p = points.last();
    return p;
}



double distance(Point p1, Point p2){
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) +(p1.z-p2.z)*(p1.z-p2.z));
}

Point subtractpoints(Point p1, Point p2){
    Point p;
    p.x = p1.x - p2.x;
    p.y = p1.y - p2.y;
    p.z = p1.z - p2.z;
    return p;
}

Point addpoints(Point p1, Point p2){
    Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    p.z = p1.z + p2.z;
    return p;
}

Point pointBetween(Point p1, Point p2, double dist){
    double d = distance(p1,p2);
    Point p3;
    p3.x= dist*(p2.x-p1.x)/d + p1.x;
    p3.y= dist*(p2.y-p1.y)/d + p1.y;
    p3.z= dist*(p2.z-p1.z)/d + p1.z;
    return p3;

}

bool pointsEqual(Point p1, Point p2,double rounding){
    bool equal;
    equal = ((p1.x-p2.x)<rounding)&&((p1.y-p2.y)<rounding)&&((p1.z-p2.z)<rounding);
    return equal;
}

Point pointFromQVector(QVector<double> v){
    Point p;
    p.x = v.at(0);
    p.y = v.at(1);
    p.z = v.at(2);
    return p;
}


QScriptValue objFromPath(QScriptEngine *engine, const XDFLPath &path){
    QScriptValue obj = engine->newObject();
    obj.setProperty("materialID",path.materialID);

    QScriptValue pointlist = engine->newArray(path.points.size());
    for(int i=0;i<path.points.size();i++){
        QScriptValue spoint = engine->newArray(3);
        spoint.setProperty("x",path.points.at(i).x);
        spoint.setProperty("y",path.points.at(i).y);
        spoint.setProperty("z",path.points.at(i).z);
        pointlist.setProperty(i,spoint);
    }
    obj.setProperty("points",pointlist);

    return obj;
}


void pathFromObj(const QScriptValue &obj, XDFLPath &path){
    path.materialID = obj.property("materialID").toInt32();
    path.points.clear();
    int len = obj.property("points").property("length").toInt32();
    QScriptValue spoints = obj.property("points");
    for(int i=0;i<len;i++){
        Point p;
        p.x = spoints.property(i).property("x").toNumber();
        p.y = spoints.property(i).property("y").toNumber();
        p.z = spoints.property(i).property("z").toNumber();
        path.points.append(p);
    }
}


XDFLPath pathFromQDom(QDomNode node){
    XDFLPath path(0);
    QDomNodeList pathChildren = node.childNodes();
    QDomNodeList pointChildren;
    QDomElement pchild;
    QDomElement coordNode;
    Point p;
    for (int i=0;i<pathChildren.size();i++){
        pchild = pathChildren.at(i).toElement();
        if (pchild.isComment()){continue;}
        if ("materialid"==pchild.nodeName().toLower()){
            path.materialID = pchild.text().toInt();
        }else if("speed"==pchild.nodeName().toLower()){
            path.speed = pchild.text().toDouble();
        }else if("point"==pchild.nodeName().toLower()){

            p.x=0;
            p.y=0;
            p.z=0;
            pointChildren = pchild.childNodes();
            for(int j=0;j<pointChildren.size();j++){
                if (pointChildren.at(j).isComment()){continue;}
                coordNode = pointChildren.at(j).toElement();

                QString temp = coordNode.nodeName().toLower();
                double tempd = coordNode.text().toDouble();

                if("x" == temp){
                    p.x = tempd;
                }else if("y" == temp){
                    p.y = tempd;
                }else if("z" == temp){
                    p.z = tempd;
                }
            }
            path.points.append(p);
        }
    }
    return path;

}
