/*
================================================================================
Filename: smooth_polygon.cpp
Description: Definition of the SmoothPolygon class methods.
================================================================================
*/

#define _USE_MATH_DEFINES
#include <math.h>

// Program includes:
#include "smooth_path.h"
#include "misc_functions.h"



SmoothPath::SmoothPath(Point startPoint, vector<Point> area, float rq, int sp)
{
    // create the polygon
    this->entryPoint = closestPoint(startPoint, area);
    this->secondPoint = closestPoint(entryPoint, area);
    this->entryPath.push_back(startPoint);
    this->entryPath.push_back(entryPoint);
    this->entryPath.push_back(secondPoint);

    this->num_major_points = entryPath.size();
    this->num_smooth_points = sp;
    this->num_minor_points = this->num_smooth_points + 2;

    // round qualities
    this->round_qualities = rq;

    // Calculate coordinates of the polygon major and minor points (de Casteljan algorithm)
    this->setMajorPoints(entryPath);
    this->minor_points.push_back(startPoint);
    this->calcMinorPointsCenter();
    this->minor_points.push_back(this->secondPoint);

}


void SmoothPath::setMajorPoints(vector<Point> mp)
{
    for (int i = 0; i < this->num_major_points; ++i)
    { 
        this->major_points.push_back(mp[i]);
    }
    
}

void SmoothPath::calcMinorPointsCenter()
{
    /* Method for calculation of the minor polygon points. Calculations are performed
       utilizing de Casteljan algorithm. */

    Point prev_major_point;  // Previous major point of the polygon
    Point cur_major_point;  // Curent major point of the polygon
    Point next_major_point;  // Next major point of the polygon

    Point begin_edge_point;  // Begin edge point of the Bezier curve
    Point end_edge_point;  // End edge point of the Bezier curve
    Point result_minor_point;  // Point sliding the edge between prev and next major points

    int i, j;  // Temporary counters
    float round_quality;  // Current major point round quality value
    float delta_t;  // Delta t parameter for Bezier points calculation
    float t;  // t parameter for Bezier points calculation (0 - 1)
    int centerI = this->major_points.size()/2;
    // Clear the vector of minor polygon points
    
    cur_major_point = this->major_points[centerI];

    prev_major_point = this->major_points[centerI - 1];


    next_major_point = this->major_points[centerI + 1];

    // Calculate the begin and end point for Bezier points calculation:
    round_quality = this->round_qualities;
    delta_t = 1.0f / (this->num_smooth_points - 1);
    t = 0.0f;

    begin_edge_point = find_between_point(prev_major_point, cur_major_point,
        (1.0f - round_quality));
    end_edge_point = find_between_point(cur_major_point, next_major_point, round_quality);

    // Cycle to calculate the minor point positions
    for (j = 0; j < this->num_smooth_points; ++j)
    {
        result_minor_point = calc_bezier_point(begin_edge_point, cur_major_point,
            end_edge_point, t);
        this->minor_points.push_back(result_minor_point);


        t += delta_t;
    }
    
}


double dist(double x1, double y1, double x2, double y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

Point closestPoint(Point s, vector<Point> v) {
    Point cp = v[0];
    double minDist = dist(cp.a, cp.b, s.a, s.b);

    // get vertex closest to the current position
    for (int i = 0; i < v.size(); i++) {
        double d = dist(v[i].a, v[i].b, s.a, s.b);
        if (minDist > d && d >= 1.0) {
            cp = v[i];
            minDist = d;
        }
    }
    return cp;
}
