/*
 * This objects this class creates a blueprint for represent
 * points in 3 dimensional space. 3 numeric values each 
 * represent coordinates along the X, Y, and Z axes.
 */

#ifndef POINT3DSPACE_H
#define POINT3DSPACE_H
#include "AccurateNumber.h"

class Point3DSpace {
private:
    AccurateNumber X_Coordinate;
    AccurateNumber Y_Coordinate;
    AccurateNumber Z_Coordinate;
public:
    Point3DSpace(); // Default point at the origin
    Point3DSpace(AccurateNumber, AccurateNumber, AccurateNumber);
    AccurateNumber getX_Coordinate(void);
    AccurateNumber getY_Coordinate(void);
    AccurateNumber getZ_Coordinate(void);
    void setX_Coordinate(AccurateNumber);
    void setY_Coordinate(AccurateNumber);
    void setZ_Coordinate(AccurateNumber);
};

#endif
