//
//  ECTriangle.h
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#ifndef ECTriangle_h
#define ECTriangle_h

#include "ECLineSegment.h"
#include "ECAbstractConvexPolygon.h"

// -----------------------------------------------------------------------------
// Triangle on 2D plane

class ECTriangle : public ECAbstractConvexPolygon
{
public:
    ECTriangle(const EC2DPoint &p1, const EC2DPoint &p2, const EC2DPoint &p3) : p1(p1), p2(p2), p3(p3) {}
    
    // Test if the polygon is convex? Return false if not
    virtual bool IsConvex() const;
    
    // Get area of the triangle
    virtual double GetArea() const;
    
    EC2DPoint GetP(int p) const {
        
        switch (p)
        {
        case 1:
            return p1;
            break;
        case 2:
            return p2;
            break;
        case 3:
            return p3;
            break;
        default:
            throw "Three Points";
            break;
        }
    
    }
     // Test if a point is inside the triangle (if on the edge, consider it is inside)
    bool IsPointInside(const EC2DPoint &pt) const;
    
    // Test if the passed-in triangle is contained within this triangle
    // again, if the triangle (rhs) has vertex on the side of this triangle, it is allowed (considered to be contained)
    bool IsContaining(const ECTriangle &rhs) const;
    
    // Test if two triangles intersects (i.e. has non-empty common area)
    bool IsIntersecting(const ECTriangle &rhs) const;
    // your code here if needed

private:
    
    EC2DPoint p1;
    EC2DPoint p2;
    EC2DPoint p3;
};


#endif /* ECTriangle_h */
