#pragma once

#ifndef SMOOTH_POLYGON_H_
#define SMOOTH_POLYGON_H_

#include <vector>
#include <iostream>
using namespace std;




class Point
{
public:
    float a=0.0, b=0.0;
    Point() {};
    float x() {
        return a;
    }
    float y() {
        return b;
    }
    Point(float a, float b) {
        this->a = a;
        this->b = b;
    }
    void setX(float a) {
        this->a = a;
    }
    void setY(float b) {
        this->b = b;
    }
    friend std::ostream& operator << (std::ostream& out, const Point& point)
    {
        out << "( " << point.a << ", " << point.b << " )";

        return out;
    }
};

class SmoothPath
{
public:
    Point entryPoint;
    Point secondPoint;
    int num_major_points;  // Number of major points that form an outer polygon
    vector<Point> major_points;  // Vector of the major polygon points
    vector<Point> entryPath;

    float round_qualities;  // // Rounding quality of the polygon corners 
    int num_smooth_points;  // Number of the single corner smooth points
    int num_minor_points;  // Number of minor points that form a smoothed polygon
    vector<Point> minor_points;  // Vector of the minor polygon points

    SmoothPath(Point startPoint, vector<Point> mp, float rq, int sp);
private:

    // Method for calculation of the coordinates of major polygon points
    void setMajorPoints(vector<Point> mp);

    // Method for calculation of the coordinates of minoe polygon points
    void calcMinorPoints();

    void calcMinorPointsCenter();
};
double dist(double x1, double y1, double x2, double y2);
Point closestPoint(Point s, vector<Point> v);



#endif // SmoothPath
