#include "LineSegment3DSpace.h"

LineSegment3DSpace::LineSegment3DSpace()
{
    // Default constructor
}

LineSegment3DSpace::LineSegment3DSpace(Point3DSpace start, Point3DSpace end)
{
    setStart(start);
    setEnd(end);
}

BigNumber LineSegment3DSpace::segmentLength()
{
    // The following uses the Pythagorean theorem to compute the distance between the end point and the start point.
    BigNumber segmentLength = ((end.getX_Coordinate().difference(start.getX_Coordinate())).sum(end.getY_Coordinate().difference(start.getY_Coordinate())).sum(end.getZ_Coordinate().difference(start.getZ_Coordinate()))).root(2);
    return segmentLength;
}

Point3DSpace LineSegment3DSpace::getStart()
{
    return start;
}

Point3DSpace LineSegment3DSpace::getEnd()
{
    return end;
}

void LineSegment3DSpace::setStart(Point3DSpace start)
{
    this->start = start;
}

void LineSegment3DSpace::setEnd(Point3DSpace end)
{
    this->end = end;
}
