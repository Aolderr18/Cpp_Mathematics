#include "Point3DSpace.h"

Point3DSpace::Point3DSpace(void)
{
    // Default constructor
}

Point3DSpace::Point3DSpace(AccurateNumber X_Coordinate, AccurateNumber Y_Coordinate, AccurateNumber Z_Coordinate)
{
    setX_Coordinate(X_Coordinate);
    setY_Coordinate(Y_Coordinate);
    setZ_Coordinate(Z_Coordinate);
}

AccurateNumber Point3DSpace::getX_Coordinate(void)
{
    return X_Coordinate;
}

AccurateNumber Point3DSpace::getY_Coordinate(void)
{
    return Y_Coordinate;
}

AccurateNumber Point3DSpace::getZ_Coordinate(void)
{
    return Z_Coordinate;
}

void Point3DSpace::setX_Coordinate(AccurateNumber X_Coordinate)
{
    Point3DSpace::X_Coordinate = X_Coordinate;
}

void Point3DSpace::setY_Coordinate(AccurateNumber Y_Coordinate)
{
    Point3DSpace::Y_Coordinate = Y_Coordinate;
}

void Point3DSpace::setZ_Coordinate(AccurateNumber Z_Coordinate)
{
    Point3DSpace::Z_Coordinate = Z_Coordinate;
}
