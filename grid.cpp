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
void grid::top_down_sort()
{
    for ( int i = 0; i < num_points; i++)
    {
        for ( int j = (i+1); j < num_points; j++)
        {
            point points1 = points[j];
            point points2 = points[i];
            if (points1.y > points2.y)
            {
                insert_point(i, j);
            }
            else if (points1.y == points2.y)
            {
                if (points1.x > points2.x)
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

void grid::flip_rows()
{
    point row[grid_size];

    for (int row_num = 0; row_num < grid_size; row_num++)
    {
        for(int i = 0; i < grid_size; i++)
        {
            row[grid_size-(i+1)] = points[row_num*grid_size+i];
        }
        for(int j = 0; j < grid_size; j++)
        {
            points[row_num*grid_size+j] = row[j];
        }
    }
}

//With a pre-sorted bottom-up grid, this creates rows by matching points with similar slopes 
void grid::row_sort()
{
    double row_slope = slope(points[0], points[1]);

    //Sort points into rows by looking at slope between points
    for (int i = 0; i < num_points; i++)
    {
        int next_point = i+1;
        for (int j = next_point; j < num_points; j++)
        {
            double slope_check = slope(points[i], points[j]);
            //Find the next point in the row. If none found, we're at the end of a row anyways.
            if (slope_check == row_slope) 
            {
               insert_point(next_point, j);
               break;
            } 
        }
    }
    
    //If the grid is parallel to the x-axis or sloping upwards, flip the points in each row around.
    if(row_slope >= 0)
    {
        flip_rows();
    }

}

void grid::col_sort()
{
    point col_grid[num_points];
    for (int i = 0; i < num_points; i++)
    {
        col_grid[i] = points[(i%grid_size)*grid_size+i/grid_size];
    }
    for (int i = 0; i < num_points; i++)
    {
        points[i] = col_grid[i];
    }
}

//Take point2 and put it in the place of point1 shifting all other points over.
//Yes, this could also be done by simply making the points a linked list, but that didn't seem necessary.
void grid::insert_point(int point1, int point2)
{
    if (point1 == point2)
    {
        return;
    }
    point temp = points[point2];

    for ( int i = point2 ; i > point1; i--)
    {
        point this_point = points[i];
        point prev_point = points[i-1];
        this_point = prev_point;
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