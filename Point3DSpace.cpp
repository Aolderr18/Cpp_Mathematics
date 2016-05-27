#include "Point3DSpace.h"

Point3DSpace::Point3DSpace()
{
    // Default constructor
}

Point3DSpace::Point3DSpace(BigNumber X_Coordinate, BigNumber Y_Coordinate, BigNumber Z_Coordinate)
{
    setX_Coordinate(X_Coordinate);
    setY_Coordinate(Y_Coordinate);
    setZ_Coordinate(Z_Coordinate);
}

BigNumber Point3DSpace::getX_Coordinate()
{
    return X_Coordinate;
}

BigNumber Point3DSpace::getY_Coordinate()
{
    return Y_Coordinate;
}

BigNumber Point3DSpace::getZ_Coordinate()
{
    return Z_Coordinate;
}

void Point3DSpace::setX_Coordinate(BigNumber X_Coordinate)
{
    this->X_Coordinate = X_Coordinate;
}

void Point3DSpace::setY_Coordinate(BigNumber Y_Coordinate)
{
    this->Y_Coordinate = Y_Coordinate;
}

void Point3DSpace::setZ_Coordinate(BigNumber Z_Coordinate)
{
    this->Z_Coordinate = Z_Coordinate;
}
