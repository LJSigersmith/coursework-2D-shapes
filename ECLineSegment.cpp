//
//  ECLineSegment.cpp
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#include "ECLineSegment.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <ostream>
using namespace std;

// -----------------------------------------------------------------------------
// Point on 2D plane

// your code goes here

// -----------------------------------------------------------------------------
// Line segment on 2D plane

// your code goes here

double crossProduct(EC2DPoint &p1, EC2DPoint &p2) {
    //p1 x p2 = x1y2 - x2y1
    double x1 = p1.xCoord;
    double y1 = p1.yCoord;

    double x2 = p2.xCoord;
    double y2 = p2.yCoord;

    return (x1 * y2) - (x2 * y1);

}

double direction(EC2DPoint &p1, EC2DPoint &p2, EC2DPoint &p3) {
    EC2DPoint a = p3 - p1;
    //std::cout << p3 << " - " << p1 << "=" << a << endl;
    EC2DPoint b = p2 - p1;
    return crossProduct(a,b);
}

bool onSegment(EC2DPoint p1, EC2DPoint p2, EC2DPoint p3) {
    double xi = p1.xCoord;
    double yi = p1.yCoord;

    double xj = p2.xCoord;
    double yj = p2.yCoord;

    double xk = p3.xCoord;
    double yk = p3.yCoord;

    if (((min(xi,xj)<=xk) && (xk <= max(xi,xj))) && ((min(yi,yj) <= yk) && (yk <= max(yi,yj)))) {
        return true;
    } else {
        return false;
    }
}

bool ECLineSegment::IsIntersect(const ECLineSegment &rhs) const {

    EC2DPoint p1 = pStart;
    EC2DPoint p2 = pEnd;

    EC2DPoint p3 = rhs.pStart;
    EC2DPoint p4 = rhs.pEnd;

    double d1 = direction(p3,  p4, p1);
    double d2 = direction(p3, p4, p2);
    double d3 = direction(p1, p2, p3);
    double d4 = direction(p1, p2, p4);

    if ( ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)) ) {
        return true;
    } else if (d1 == 0 && onSegment(p3,p4,p1)) { return true;
    } else if (d2 == 0 && onSegment(p3,p4,p2)) { return true;
    } else if (d3 == 0 && onSegment(p1,p2,p3)) { return true;
    } else if (d4 == 0 && onSegment(p1,p2,p4)) { return true;
    } else { return false; }
    
}

std::ostream& operator<<(std::ostream& os, const EC2DPoint &p) {
    os << "(" << p.xCoord << "," << p.yCoord << ")";
    return os;
}
