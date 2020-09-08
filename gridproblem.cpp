#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <math.h>
#include "grid.h"

using namespace std;

#define PI 3.141592654

int calc_grid_size(int num_points)
{
    int grid_size = 1;
    int sq_pts = 1;
    while( sq_pts < num_points ){
        sq_pts = ++grid_size*grid_size;
    }
    return grid_size;
}

int count_file_lines(string file_name)
{
    int num_lines;
    ifstream inFile;
    string line;
    inFile.open(file_name);
    while(getline(inFile,line))
    {
        ++num_lines;
    }
    inFile.close();
    return num_lines;
}


int main(int argc, char** argv)
{
    string file_name=argv[1];

    int num_points = count_file_lines(file_name);

    point points[num_points];  //Array to store all grid_points

    //Read and Store Input
    ifstream inFile;
    inFile.open(file_name);
    if(inFile.is_open()){
        string point;
        string delim=",";
        int delimPos;
        double x,y;
        
        for (int i = 0; i < num_points; i++)
        {
            getline(inFile, point);   
            point.pop_back();        // remove trailing \r
            points[i].input = point; // store string for output later

            //Split string into x and y
            delimPos = point.find(delim);
            points[i].x = stof(point.substr(0, delimPos));
            point.erase(0, delimPos+1);
            points[i].y = stof(point);
        }
    }
    inFile.close();

    int grid_size = calc_grid_size(num_points);
    grid in_grid;
    in_grid.grid_size = grid_size;
    in_grid.num_points = num_points;
    in_grid.points = points;


/*
    //TEST_SPACE
    in_grid.shift(-points[0].x, -points[0].y);
    in_grid.scale(.00001);
    in_grid.rotate(30);
*/

    // Algorithms to sort rows
    // First sort all points by lowest y value then calculate slope between first two points
    // Check slope between subsequent points and find the next point that is equal, this creates rows
    in_grid.bottom_up_sort();
    in_grid.row_sort();

    //Compute Alpha - Due to how rows are sorted above, expected values are from -45 to 0 and 0 to 45
    double alpha = atan(in_grid.slope(in_grid.points[0], in_grid.points[1])) * 180/PI;

    //Output message
    for (int i = 0; i < grid_size; i++)
    {
        cout << "Row " << i << ": ";
        for (int j = 0; j < grid_size; j++)
        {
            point current_point = in_grid.points[i*(grid_size)+j];
            //cout << current_point.x << "," << current_point.y; //Output calculated values
            cout << current_point.input; //Output original input, not calculated values
            if (j != (grid_size-1))
                cout << " - ";
        }
        cout << endl;

    }

    // Flip all points about y=x and resort for columns
    in_grid.flip_grid();
    in_grid.bottom_up_sort();
    in_grid.row_sort();
    in_grid.flip_grid();



    for (int i = 0; i < grid_size; i++)
    {
        cout << "Col " << i << ": ";
        for (int j = 0; j < grid_size; j++)
        {
            point current_point = in_grid.points[i*(grid_size)+j];
            //cout << current_point.x << "," << current_point.y; //Output calculated values
            cout << current_point.input; //Output originla input, not calculated values
            if (j != (grid_size-1))
                cout << " - ";
        }
        cout << endl;

    }

    cout << "Alpha=" << alpha << " degrees" << endl;
}