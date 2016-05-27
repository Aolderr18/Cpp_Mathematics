/*
 * This objects this class creates a blueprint for represent
 * points in 3 dimensional space. 3 numeric values each 
 * represent coordinates along the X, Y, and Z axes.
 */

#ifndef POINT3DSPACE_H
#define POINT3DSPACE_H
#include "BigNumber.h"

class Point3DSpace {
private:
    BigNumber X_Coordinate;
    BigNumber Y_Coordinate;
    BigNumber Z_Coordinate;
public:
    Point3DSpace(); // Default point at the origin
    Point3DSpace(BigNumber, BigNumber, BigNumber);
    BigNumber getX_Coordinate();
    BigNumber getY_Coordinate();
    BigNumber getZ_Coordinate();
    void setX_Coordinate(BigNumber);
    void setY_Coordinate(BigNumber);
    void setZ_Coordinate(BigNumber);
};

#endif
