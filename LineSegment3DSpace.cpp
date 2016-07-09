#include "LineSegment3DSpace.h"

LineSegment3DSpace::LineSegment3DSpace(void)
{
    // Default constructor
}

LineSegment3DSpace::LineSegment3DSpace(Point3DSpace start, Point3DSpace end)
{
    setStart(start);
    setEnd(end);
}

AccurateNumber LineSegment3DSpace::segmentLength(void)
{
    // The following uses the Pythagorean theorem to compute the distance between the end point and the start point.
    AccurateNumber segmentLength = ((end.getX_Coordinate().difference(start.getX_Coordinate())).sum(end.getY_Coordinate().difference(start.getY_Coordinate())).sum(end.getZ_Coordinate().difference(start.getZ_Coordinate()))).root(2);
    return segmentLength;
}

Point3DSpace LineSegment3DSpace::getStart(void)
{
    return start;
}

Point3DSpace LineSegment3DSpace::getEnd(void)
{
    return end;
}

void LineSegment3DSpace::setStart(Point3DSpace start)
{
    LineSegment3DSpace::start = start;
}

void LineSegment3DSpace::setEnd(Point3DSpace end)
{
    LineSegment3DSpace::end = end;
}
