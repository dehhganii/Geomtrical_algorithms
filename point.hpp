#include <vector>
#pragma once
class point
{
public:
    //Constructor with no arguments: define a degenerate point with all its coordinates equal to zero.
    point();
    //Constructor with one arguments: define a degenerate point with  its coordinates equal.
    point(const double &_x);
    //Constructor with two arguments: define a degenerate point with  its coordinates being x, and y.
    point(const double &_x, const double &_y);

    //Change (or initialize) the coordinates of the point
    void set_cooridnates(const double &_x, const double &_y);
    //Return the coordinates of the point
    std::vector<double> get_coordinates() const;

private:
    //The initial coordinates of point
    double x = 0, y = 0;
};