#ifndef LINESEGMENT3DSPACE_H
#define LINESEGMENT3DSPACE_H
#include "Point3DSpace.h"

class LineSegment3DSpace {
private:
    Point3DSpace start;
    Point3DSpace end;
public:
    LineSegment3DSpace(void);
    LineSegment3DSpace(Point3DSpace, Point3DSpace);
    BigNumber segmentLength(void);
    Point3DSpace getStart(void);
    Point3DSpace getEnd(void);
    void setStart(Point3DSpace);
    void setEnd(Point3DSpace);
};

#endif
