#include "grid.h"
#include <math.h>

#define PI 3.141592654

/*
Container class for points
*/

//Empty Constructor
point::point()
{

}

/*
Grid class
*/

//Empty Constructor
grid::grid()
{

}

//Sorting functions for an input grid

//Sorts all points by lowest y value, then x if y values are equal
void grid::bottom_up_sort()
{
    for ( int i = 0; i < num_points; i++)
    {
        for ( int j = (i+1); j < num_points; j++)
        {
            if (points[j].y < points[i].y)
            {
                insert_point(i, j);
            }
            else if (points[j].y == points[i].y)
            {
                if (points[j].x < points[i].x)
                {
                    insert_point(i, j);
                }
            }
        }
    }
}

//Swaps x and y values, essentially flipping the grid about y=x
void grid::flip_grid()
{
    for (int i = 0; i < num_points; i++)
    {
        double temp = points[i].x;
        points[i].x = points[i].y;
        points[i].y = temp;
    }
}

//With a pre-sorted bottom-up grid, this creates rows by matching points with similar slopes 
void grid::row_sort()
{
    //Compute slope of line for first two points
    if ((points[1].x-points[0].x) == 0)
    {
        return; //Board is parallel to x axis, already sorted by rows
    }

    double row_slope = slope(points[0], points[1]);

    int i, j;
    for (i = 0; i < num_points; i++)
    {
        int last_point = i; //This is the prior point in the row
        i++;
        for (j = i; j < num_points; j++)
        {
            double slope_check = slope(points[last_point], points[j]);
            //Find the next point in the row. If none found, we're at the end of a row anyways.
            if (slope_check == row_slope) 
            {
                insert_point(i, j);
            } 
        }
    }
}

//Take point2 and put it in the place of point1 shifting all other points over.
//Yes, this could also be done by simply making the points a linked list, but that didn't seem necessary.
void grid::insert_point(int point1, int point2)
{
    point temp = points[point2];

    for ( int i = point2 ; i > point1; i--)
    {
        points[i] = points[i-1];
    }
    points[point1] = temp;
}

//Algebraic y=mx+b slope where point2=x2,y2, point1=x1,y1
double grid::slope(point point1, point point2)
{
    return (point2.y - point1.y)/(point2.x - point1.x);
}



//Scales the grid out (or in) about points[0]. Meant for testing work at scale
void grid::scale(double factor)
{
    point origin = points[0];
    shift(-origin.x, -origin.y);
    for (int i = 0; i < num_points; i++)
    {
        points[i].x = factor*points[i].x;
        points[i].y = factor*points[i].y;
    }
    shift(origin.x, origin.y);
}

//Moves all points in the grid by (xShift, yShift)
void grid::shift(double xShift, double yShift)
{
    for (int i = 0; i < num_points; i++)
    {
        points[i].x += xShift;
        points[i].y += yShift;
    }
}

/*
// Rotates all points in the grid about points[0] by polar transformation and 
// back to cartesian coordinates after adding the angle
// Doesn't seem to work entirely correctly. Would require some more troubleshooting.
void grid::rotate(double angle)
{
    point origin = points[0];
    shift(-origin.x, -origin.y);
    for (int i = 1; i < num_points; i++)
    {
        double slope_to_point;
        if(points[i].x == 0)
        {
            slope_to_point = 90;
        }
        else
        {
            slope_to_point = slope(points[0], points[i]);
        }

        double curr_angle = atan(slope_to_point)*180/PI;
        double dist_to_origin = sqrt(points[i].x*points[i].x + points[i].y*points[i].y);
        double new_angle = curr_angle + angle;

        points[i].x = dist_to_origin*cos(new_angle*PI/180);
        points[i].y = dist_to_origin*sin(new_angle*PI/180);
    }
    shift(origin.x, origin.y);
}
*/