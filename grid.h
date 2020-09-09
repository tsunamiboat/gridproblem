#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;


class point
{
    public:
        double x;
        double y;
        string input;
        point();
};

class grid
{
    public:
        int grid_size;
        int num_points;
        point * points;

        grid();
        
        //These functions sort an unsorted random grid
        void top_down_sort();
        void flip_grid();
        void flip_rows();
        void row_sort();
        void col_sort();

        void insert_point(int, int); //Takes point at input param 2 and puts it in input param 1

        double slope(point, point);

        //These functions refactor a uniform grid by moving, scaling, and rotating.
        void scale(double factor);
        void shift(double x, double y);
        //void rotate(double angle);

};