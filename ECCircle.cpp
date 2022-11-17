#include "ECCircle.h"
#include <cmath>
using namespace std;

//*************************************************************************************
// Circle
ECCircle::ECCircle(double x, double y, double radius) : _xCenter(x), _yCenter(y), _radius(radius) {}

void ECCircle::GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const {
    
    double xMax = _xCenter + _radius;
    double xMin = _xCenter - _radius;
    double yMax = _yCenter + _radius;
    double yMin = _yCenter - _radius;

    xUpperLeft = xMin;
    xLowerRight = xMax;

    yUpperLeft = yMin;
    yLowerRight = yMax;
}

// is the shape intersecting with point (px, py)
bool ECCircle::IsPointInside(const EC2DPoint &pt) const {

    // sqrt( (x_p - x_c)^2 + (y_p - y_c)^2 ) <= radius if point is inside

    double xp = pt.xCoord;
    double yp = pt.yCoord;

    double xc = _xCenter;
    double yc = _yCenter;

    double term1 = pow((xp - xc),2);
    double term2 = pow((yp - yc),2);

    double result = sqrt(term1 + term2);

    return result <= _radius;

}

double ECCircle::GetArea() const {
    return PI * _radius * _radius;
}
void ECCircle::GetCenter(double &xc, double &yc) const {
    xc = _xCenter;
    yc = _yCenter;
}



//*************************************************************************************
// Ellipse

ECEllipse::ECEllipse(double x, double y, double radiusx, double radiusy) : _xCenter(x), _yCenter(y), _radiusX(radiusx), _radiusY(radiusy) {}

void ECEllipse::GetBoundingBox(double &xUpperLeft, double &yUpperLeft, double &xLowerRight, double &yLowerRight) const {
    
    double xMax = _xCenter + _radiusX;
    double xMin = _xCenter - _radiusX;

    double yMax = _yCenter + _radiusY;
    double yMin = _yCenter - _radiusY;

    xUpperLeft = xMin;
    xLowerRight = xMax;

    yUpperLeft = yMin;
    yLowerRight = yMax;
}

// is the shape intersecting with point (px, py)
bool ECEllipse::IsPointInside(const EC2DPoint &pt) const {
    
    // [ (x-h)^2 / r_x^2 ] + [ (y-k)^2 / r_y^2 ] <= 1 if inside ellipse

    double h = _xCenter;
    double k = _yCenter;

    double x = pt.xCoord;
    double y = pt.yCoord;

    double term1 = ( pow((x-h), 2) ) / ( pow(_radiusX, 2) );
    double term2 = ( pow((y-k), 2) ) / ( pow(_radiusY, 2) );

    double result = term1 + term2;
    
    return result <= 1;

}

double ECEllipse::GetArea() const {
    return PI * _radiusX * _radiusY;
}
void ECEllipse::GetCenter(double &xc, double &yc) const {
    xc = _xCenter;
    yc = _yCenter;
}