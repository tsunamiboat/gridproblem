# gridproblem

gridproblem was written in Visual C Studio on an Ubuntu machine.

As compiled, it should take in an input file passed in as the first argument to be run. It will read each line as a point in the form: number,number\r\n where number represents decimal values.

grid.h and grid.cpp are include files for a grid class that sorts the points into rows and columns for later reading.
There are also included a number of functions to manipulate the grid in specific ways. All appear to work except for rotate which would require some more work to troubleshoot. My assumption about it's current state is that in rotating the grid, the series of math operations shifts the points in the grid just enough to change the slope between the points rendering the sorting solution less than function.

As is, the program makes the following assumptions:

1. Points should be returned to the user in the format they are entered into the program. Regarless of the math done, the initial point should be returned.
2. Rows are always presented from left to right, top to bottom.
3. Cols are always presented from top to bottom, left to right.
4. Alpha (or the deviation from the x axis) will always range from -45 to 0 degrees or 0 to 45 degrees, not including 45 degrees.
  Should the grid be rotated 45 degrees from the x axis, Row 0 will always form to the left, so an exactly equal 45 degree grid will be -45 degrees.
5. Any deviation of alpha above 45 degrees will swap rows into columns and columns into rows keeping the value low.

Building the solution

This code was built with g++ using the comand line command below. All files were stored in /home/mbrown/projects/gridproblem/ Replacing the directory of your choice should likely build it for you as well. 

/usr/bin/g++ -std=c++11 -g /home/mbrown/projects/gridproblem/*.cpp -o gridproblem
