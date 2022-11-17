//
//  ECConvexPolygon.cpp
//  
//
//  Created by Yufeng Wu on 1/29/21.
//
//

#include "ECConvexPolygon.h"
#include "ECTriangle.h"
#include <math.h>
#define PI 3.14159265

using namespace std;

// Convex polygon on 2D plane: implementing polygon for non-triangles

ECConvexPolygon::ECConvexPolygon(const std::vector<EC2DPoint> &list) {
    listNodes = list;
}

bool ECConvexPolygon::IsConvex() const {

    // If there are less than 3 nodes, not a polygon, much less a convex one
    if (listNodes.size() < 3) { return false; }

    // Create a vector of all the line segments that make up the polygon
    vector<ECLineSegment> polyLines;
    for (int i = 0; i < listNodes.size(); i++) {
        EC2DPoint p1 = listNodes[i];
        EC2DPoint p2 = listNodes[(i+1)%listNodes.size()];
        ECLineSegment seg(p1,p2);
        polyLines.push_back(seg);
    }

    // For each line, do some math
    // Math relies on the angle between two lines equals the difference of two angles of inclination
    // Each line's angle of inclination is equal to the arctan of the slope

    for (int i = 0; i < polyLines.size(); i++) {

        ECLineSegment seg1 = polyLines[i];
        ECLineSegment seg2 = polyLines[(i+1)%polyLines.size()];
        EC2DPoint p1 = seg1.pStart;
        EC2DPoint p2 = seg2.pStart;
        EC2DPoint p3 = seg2.pEnd;

        double slope1 = (p2.yCoord - p1.yCoord) / (p2.xCoord - p1.xCoord);
        double slope2 = (p3.yCoord - p2.yCoord) / (p3.xCoord - p2.xCoord);

        // Calculate angles of inclination, multiplying by 180/pi to get in degrees
        double angle1 = abs(atan(slope1) * (180/PI));
        double angle2 = abs(atan(slope2) * (180/PI));

        double totalAngle = abs(angle1 - angle2);
        
        // Arctan will return the acute angle, if the angle is obtuse it will come back as 0
        // An obtuse angle, greater than 180 means it is not convex
        //if (totalAngle > 180) { return false; }
        if (totalAngle == 0) { return false; }
    }
    
    // If there aren't any obtuse angles, it is convex
    return true;
}

// Shoelace Formula
// https://en.wikipedia.org/wiki/Shoelace_formula#:~:text=The%20shoelace%20formula%2C%20shoelace%20algorithm,Cartesian%20coordinates%20in%20the%20plane.
double ECConvexPolygon::GetArea() const {
    
    double area = 0.0;

    // Not a polygon = no area
    if (listNodes.size() < 3) { return area; }

    // Do shoelace formula, I don't understand the math so I won't try to explain it
    std::vector<EC2DPoint> nodes = listNodes;
    int j = nodes.size() - 1;
    for (int i = 0; i < nodes.size(); i++) {
        area += (nodes[i].xCoord + nodes[j].xCoord) * (nodes[j].yCoord - nodes[i].yCoord);
        j = i;
    }
    
    return abs(area / 2.0);
}
