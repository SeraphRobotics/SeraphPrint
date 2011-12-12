#ifndef PATH_H
#define PATH_H

#include <QObject>
#include <QVector>
#include "../../shared/math/vector3.h"

class QDomNode;


class XdflPath : public QObject
{
public:
    Q_OBJECT
    XdflPath();

    /**
     * Constructs a path froma DOM node in an XDFL file
     * from a configuration file of the printer.
     */
    XdflPath(const QDomNode& sourceDomNode);

    /**
     *Destructor
     */
    ~XdflPath();


public slots:
    /**
     * returns the materialID of the path, 0 if there is no material set
     */
    int getMaterialID() const;


    /**
     * returns a copy of the points
     */
    QVector<Vector3> getPoints();


    /**
     *adds a point to the end of the Path
     */
    void addPoint(Vector3 p);




private:
    int materialID_;
    QVector<Vector3> points_;
    double pathSpeed_;


};

#endif // PATH_H
