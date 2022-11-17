//
//  ECTriangle.cpp
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#include "ECTriangle.h"
#include <cmath>
using namespace std;

// your code goes here

bool ECTriangle::IsConvex() const {
    // Triangle is always convex
    return true;
}

double ECTriangle::GetArea() const {

    EC2DPoint p1 = GetP(1);
    EC2DPoint p2 = GetP(2);
    EC2DPoint p3 = GetP(3);

    double x1 = p1.xCoord;
    double y1 = p1.yCoord;

    double x2 = p2.xCoord;
    double y2 = p2.yCoord;

    double x3 = p3.xCoord;
    double y3 = p3.yCoord;

    double area = (x1*y2) + (x2*y3) + (x3*y1) - (y1*x2) - (y2*x3) - (y3 * x1);
    area = abs(area/2);
    return area;
}

bool ECTriangle::IsPointInside(const EC2DPoint &pt) const {
    
    // Get Area of 3 Triangles formed by subbing pt for each vertex
    // If Triangle Area is less than the sum of those triangles's area, then pt not in triangle

    double TArea = GetArea();
    
    ECTriangle a(pt, GetP(2), GetP(3));
    ECTriangle b(GetP(1), pt, GetP(3));
    ECTriangle c(GetP(1), GetP(2), pt);

    double areaA = a.GetArea();
    double areaB = b.GetArea();
    double areaC = c.GetArea();

    double sumMiniTris = areaA + areaB + areaC;
    if (sumMiniTris > TArea) {
        return false;
    } else {
    return true;
    }
}

//bool IsContaining(const ECTriangle &rhs) const;

bool ECTriangle::IsContaining(const ECTriangle &rhs) const {
    
    EC2DPoint p1 = rhs.GetP(1);
    EC2DPoint p2 = rhs.GetP(2);
    EC2DPoint p3 = rhs.GetP(3);

    vector<EC2DPoint> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    for (auto pt : points) {
        if (!IsPointInside(pt)) {
            return false;
        }
    }
    return true;
}

//bool IsIntersecting(const ECTriangle &rhs) const;
bool ECTriangle::IsIntersecting(const ECTriangle &rhs) const {

    EC2DPoint p1 = GetP(1);
    EC2DPoint p2 = GetP(2);
    EC2DPoint p3 = GetP(3);

    ECLineSegment seg1(p1,p2);
    ECLineSegment seg2(p2,p3);
    ECLineSegment seg3(p3,p1);

    vector<ECLineSegment> t1;

    t1.push_back(seg1);
    t1.push_back(seg2);
    t1.push_back(seg3);

    EC2DPoint p4 = rhs.GetP(1);
    EC2DPoint p5 = rhs.GetP(2);
    EC2DPoint p6 = rhs.GetP(3);

    ECLineSegment seg4(p4,p5);
    ECLineSegment seg5(p5,p6);
    ECLineSegment seg6(p6,p4);

    vector<ECLineSegment> t2;

    t2.push_back(seg4);
    t2.push_back(seg5);
    t2.push_back(seg6);

    cout << "TRI 1: " << p1 << p2 << p3 << endl;
    cout << "TRI 2: " << p4 << p5 << p6 << endl; 

    for (auto t1Seg : t1) {
        for (auto t2Seg : t2) {
            if (t1Seg.IsIntersect(t2Seg)) {
                return true;
            }
        }
    }
    return false;
}
