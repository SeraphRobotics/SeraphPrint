#ifndef XDFLPATH_H
#define XDFLPATH_H

#include <QList>
#include <QtScript>
#include <QDomNode>

struct Point{// this will need to be redone to handel uvw later
    double x;
    double y;
    double z;
};

double distance(Point p1, Point p2);

Point pointBetween(Point p1, Point p2, double dist);

bool pointsEqual(Point p1, Point p2,double rounding = 0.01);

Point pointFromQVector(QVector<double> v);

/**
 * A container class for the XDFL paths.
 */
class XDFLPath
{
public:

    //There are three states, absolute, local relative (euclidian) and global relative. toRelative makes it local relative.
    explicit XDFLPath(int material_id =0, bool relative = false);

    XDFLPath(const XDFLPath &path);

    double length();

    Point start();
    Point end();

    void toRelative();
    void toAbsolute();
    bool isNull();
    QList<Point> getPoints();
    QList<Point> getGlobalRelativePoints();

public:
    QList<Point> points;
    double speed;
    int materialID;
    bool relative_;

};


XDFLPath pathFromQDom(QDomNode node);

Q_DECLARE_METATYPE(XDFLPath)

QScriptValue objFromPath(QScriptEngine *engine, const XDFLPath &path);

void pathFromObj(const QScriptValue &obj, XDFLPath &path);

Point subtractpoints(Point p1, Point p2);

Point addpoints(Point p1, Point p2);


#endif // XDFLPATH_H
