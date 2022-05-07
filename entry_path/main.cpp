/*
================================================================================
Filename: main.cpp
Description: Main program file with entrance point. Create Polygon and get smoothing Points
================================================================================
*/

#include "smooth_path.h"
#include <vector>
#include <iostream>


using namespace std;



int main(int argc, char** argv)
{
    vector<Point> area1;
    Point startPoint;
    float smooth_quality = 0.45f; // 0.05 <= smooth_quilty <= 0.45
    int smooth_points = 10;

    // Create the goal area
    area1.push_back(Point(0.0f, 0.0f));
    area1.push_back(Point(15.0f, 2.0f));
    area1.push_back(Point(27.0f, 17.2f));
    area1.push_back(Point(17.4f, 22.7f));
    area1.push_back(Point(-10.0f, 15.24f));
    startPoint = Point(27.0f, 0.0f); // ugv's current Position



    SmoothPath* smoothEntryPath = new SmoothPath(startPoint, area1, smooth_quality, smooth_points);

    cout << "Major Points" << endl;
    for (int i = 0; i < smoothEntryPath->num_major_points; ++i)
        cout << smoothEntryPath->major_points[i] << endl;

    cout << "======================" << endl << endl;

    // output : smooth polygon edge points(minor points)
    cout << "Minor Points" << endl;
    for (int i = 0; i < smoothEntryPath->num_minor_points; ++i)
        cout << smoothEntryPath->minor_points[i] << endl;

}
