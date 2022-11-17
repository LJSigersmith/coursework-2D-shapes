//
//  ECLineSegment.h
//  
//
//  Created by Yufeng Wu on 1/22/21.
//
//

#ifndef ECLineSegment_h
#define ECLineSegment_h
#include <iostream>
// -----------------------------------------------------------------------------
// Point on 2D plane

class EC2DPoint
{
public:
    EC2DPoint(double x, double y) : xCoord(x), yCoord(y) {};
    double xCoord;
    double yCoord;

    EC2DPoint operator + (EC2DPoint const &p) const {
        double x = xCoord + p.xCoord;
        double y = yCoord + p.yCoord;
        return EC2DPoint(x,y);
    }

    EC2DPoint operator - (EC2DPoint const &p) const {
        double x = xCoord - p.xCoord;
        double y = yCoord - p.yCoord;
        return EC2DPoint(x,y);
    }

    bool operator == (EC2DPoint const &p) const {
        return (xCoord == p.xCoord) && (yCoord == p.yCoord);
    }
    
    bool operator < (EC2DPoint const &p) const {
        return true;
    }

    bool operator > (EC2DPoint const &p) const {
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const EC2DPoint &p);
    
private:
    // your code goes here
};

// -----------------------------------------------------------------------------
// Line segment on 2D plane

class ECLineSegment
{
public:
    ECLineSegment(const EC2DPoint &pStart, const EC2DPoint &pEnd) : pStart(pStart), pEnd(pEnd) {}
    
    // Is this segment intersect with the other?
    bool IsIntersect(const ECLineSegment &rhs) const;
    
    // your code goes here
    EC2DPoint pStart;
    EC2DPoint pEnd;
    
private:
    // your code goes here
};


#endif /* ECLineSegment_h */
