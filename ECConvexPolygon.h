//
//  ECConvexPolygon.h
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//

#ifndef ECConvexPolygon_h
#define ECConvexPolygon_h

#include <vector>
#include "ECLineSegment.h"
#include "ECAbstractConvexPolygon.h"

// -----------------------------------------------------------------------------
// Convex polygon on 2D plane: implementing polygon for non-triangles

class ECConvexPolygon : public ECAbstractConvexPolygon
{
public:

    ECConvexPolygon() {};
    // Consructor takes a list of nodes, which are the nodes of the polygon
    // ordered sequentially (either clockwise or counter clockwise
    ECConvexPolygon(const std::vector<EC2DPoint> &list);
    
    // Test if the polygon is convex? Return false if not
    virtual bool IsConvex() const;
    
    // Calculate total area of the polygon (you can assume it is indeed convex)
    virtual double GetArea() const;
    
    //bool IsPointInside(const EC2DPoint &pt) const;
    // your code here if needed
    
};


#endif /* ECConvexPolygon_h */
