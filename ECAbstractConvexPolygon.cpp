//
//  ECAbstractConvexPolygon.h
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//


#include "ECAbstractConvexPolygon.h"
#include <iostream>
using namespace std;

// Convex polygon on 2D plane: interface class

// Get bounding box (i.e. smallest rectangle contaiing the shape with sides parellel to axes) of the shape
// the left-upper corner of the window is (0,0)
void ECAbstractConvexPolygon::GetBoundingBox( double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight ) const {

    // Check for empty list
    if (listNodes.size() == 0) { xUpperLeft = yUpperLeft = xLowerRight = yLowerRight = 0; return; }
    
    // Find max/min X and Y values
    double xInit = listNodes[0].xCoord;
    double yInit = listNodes[0].yCoord;
    double xMax = xInit,yMax = yInit,xMin = xInit,yMin = yInit;

    for (EC2DPoint p : listNodes) {
        if (p.xCoord > xMax) { xMax = p.xCoord; }
        if (p.xCoord < xMin) { xMin = p.xCoord; }
        if (p.yCoord > yMax) { yMax = p.yCoord; }
        if (p.yCoord < yMin) { yMin = p.yCoord; }
    }

    // Upper left is actually lower left if left-upper window is (0,0)
    // Lower right is actually upper right
    // Upper left: (xMin, yMax)    (xMax,yMax)
    // Lower left : (xMin, yMin)   (xMax,yMin)
    xUpperLeft = xMin;
    xLowerRight = xMax;

    yUpperLeft = yMin;
    yLowerRight = yMax;
}
    
// find out the center of the shape and store in (xc,yc); round down to the closest integer
void ECAbstractConvexPolygon::GetCenter(double &xc, double &yc) const {
    
    double x1, x2, y1, y2;
    GetBoundingBox(x1,y1,x2,y2);
    xc = (x1 + x2) / 2;
    yc = (y1 + y2) / 2;

}

bool ECAbstractConvexPolygon::IsIntersecting(const ECAbstractConvexPolygon &rhs) const {

    // If either polygon has less than 3 nodes, its not a polygon
    // Test cases indicate returning true in that case
    if (listNodes.size() < 3 || rhs.listNodes.size() < 3) { return true; }

    // If point in this is inside rhs, they must intersect
    for (EC2DPoint p : listNodes) {
        if (rhs.IsPointInside(p) == true) { cout << p << " is inside" << endl; return true; }
    }

    // If point in rhs is inside this, they must intersect
    for (EC2DPoint p : rhs.listNodes) {
        if (IsPointInside(p) == true) { cout << p << " is inside" << endl; return true; }
    }

    // Create vector of all line segments making up this
    vector<ECLineSegment> poly1Lines;
    for (int i = 0; i < listNodes.size(); i++) {
        EC2DPoint p1 = listNodes[i];
        EC2DPoint p2 = listNodes[(i+1)%listNodes.size()];
        ECLineSegment seg(p1,p2);
        poly1Lines.push_back(seg);
    }

    // Create vector of all line segments making up rhs
    vector<ECLineSegment> poly2Lines;
    for (int i = 0; i < rhs.listNodes.size(); i++) {
        EC2DPoint p1 = rhs.listNodes[i];
        EC2DPoint p2 = rhs.listNodes[(i+1)%rhs.listNodes.size()];
        ECLineSegment seg(p1,p2);
        poly2Lines.push_back(seg);
    }

    // If any line segment from one polygon intersects with another, they must intersect
    for (ECLineSegment seg1 : poly1Lines) {
        for (ECLineSegment seg2: poly2Lines) {
            if (seg1.IsIntersect(seg2)) { return true; }
        }
    }

    // If lines are not inersecting, and no points are within another polygon, the polygons do not intersect
    return false;
}

bool ECAbstractConvexPolygon::IsPointInside(const EC2DPoint &pt) const {
    
    // If the point is a vertex, obviously it is inside that counts as inside
    for (auto p : listNodes) {
        if (pt == p) { return true; }
    }

    // Get the max and min x and y coordinate of the polygon
    double xInit = listNodes[0].xCoord;
    double yInit = listNodes[0].yCoord;
    double xMax = xInit,yMax = yInit,xMin = xInit,yMin = yInit;

    for (EC2DPoint p : listNodes) {
        if (p.xCoord > xMax) { xMax = p.xCoord; }
        if (p.xCoord < xMin) { xMin = p.xCoord; }
        if (p.yCoord > yMax) { yMax = p.yCoord; }
        if (p.yCoord < yMin) { yMin = p.yCoord; }
    }
    
    // If the x or y coordinate of the point exceeds or does not reach any of the x or y min/maxes, it is outside the polygon
    if (pt.xCoord < xMin || pt.xCoord > xMax || pt.yCoord > yMax || pt.yCoord < yMin) {
        return false;
    }
    
    // Create a point far left and far right on same y axis as the point to represent an "infinite" line
    EC2DPoint p1(-9999, pt.yCoord);
    EC2DPoint p2(9999, pt.yCoord);
    ECLineSegment infLine(p1,p2);

    // Create vector of all line segments that make up polygon
    vector<ECLineSegment> polyLines;
    for (int i = 0; i < listNodes.size(); i++) {
        EC2DPoint p1 = listNodes[i];
        EC2DPoint p2 = listNodes[(i+1)%listNodes.size()];
        ECLineSegment seg(p1,p2);
        polyLines.push_back(seg);
    }

    // Search for line segments that intersect with the "infinite" line extended from the point, add to a vector to test
    vector<ECLineSegment> linesToTest;
    for (ECLineSegment seg : polyLines) {
        if (seg.IsIntersect(infLine)) {
            linesToTest.push_back(seg);
        }
    }

    // Test line segments using the math this guy describes
    // https://towardsdatascience.com/is-the-point-inside-the-polygon-574b86472119

    int turns = 0;
    for (ECLineSegment seg : linesToTest) {
        EC2DPoint pA = seg.pStart;
        EC2DPoint pB = seg.pEnd;

        double result = (pt.yCoord - pA.yCoord) * (pB.xCoord - pA.xCoord)
            - (pt.xCoord - pA.xCoord) * (pB.yCoord - pA.yCoord);
        
        // If the result of that calculation is less than 0, representing the point is to the left of the line, decrement turns
        // If its greater than 0, representing point is to the right, increment turns

        if (result > 0) { turns--;}
        if (result < 0) { turns++; }
    }

    // If the number of turns is 0, the point is outside the polygon
    // If its not 0, it is inside the polygon
    if (turns == 0) { return false; } else { return true; }

}

bool ECAbstractConvexPolygon::IsContaining(const ECAbstractConvexPolygon &rhs) const {
    
    // If any point in rhs is not within this, the polygon itself cannot be within it either
    for (EC2DPoint pt : rhs.listNodes) {
        if (!IsPointInside(pt)) { return false; }
    }
    return true;
}