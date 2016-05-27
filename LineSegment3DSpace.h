#ifndef LINESEGMENT3DSPACE_H
#define LINESEGMENT3DSPACE_H
#include "Point3DSpace.h"

class LineSegment3DSpace {
private:
    Point3DSpace start;
    Point3DSpace end;
public:
    LineSegment3DSpace();
    LineSegment3DSpace(Point3DSpace, Point3DSpace);
    BigNumber segmentLength();
    Point3DSpace getStart();
    Point3DSpace getEnd();
    void setStart(Point3DSpace);
    void setEnd(Point3DSpace);
};

#endif
