
/**
 * @file ClosestPair.cpp
 * @author dehghh1@mcmaster.ca
 * @brief In this class a vector of points is as an input.
 * There is an algorithm for finding the closest pair of points in terms of distance.
 * The brute force algorithm is of order O(n^2).
 * However, the implemented algorithm is order of O(n log n) with using sweep line approach. 
 * @version 0.1
 * @date 2021-12-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Utility.hpp"
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
/**
 * @brief Read points from a file and store them in a vector of points as a object of the class.
 * Use already defined method of the Utility class.
 * 
 * @param address the string hols address of the file code reads from that
 */
void ClosestPair::read_points(std::string address)
{  
    points = Utility::read_points(address);
}

/**
 * @brief A method to compute the distance of two points. Using square root of already defined method of Utility class.
 * 
 * @param p1 The first point
 * @param p2 The second point to compute the distance with.
 * @return double Return the distance of two points.
 */
double ClosestPair::dist(const point &p1, const point &p2) const
{
    return sqrt(Utility::square_distance(p1, p2));
}

/**
 * @brief The method compare two values and return the smaller one.
 * 
 * @param x The first input for comparison.
 * @param y The second input for comparison.
 * @return double Return the smaller value.
 */
double ClosestPair::min(double x, double y)
{
    if( x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

/**
 * @brief A method to find the distance between the closest points of strip of a given size.
 * The length of vector strip cannot be greater than 6 because the minimum distance could not be d anymore.
 * As a result the time complexity of the method remain O(n)
 * @param strip Vector of points sorted based on y coordinates. With d as the upper bound for distance
 * @param size The size of the strip vector
 * @param d The upper bound distance between
 * @return double Return the new minimum distance of two points.
 */
double ClosestPair::strip_closest(vector<point> strip,uint64_t size, double d)
{
    double min = d;

    for(size_t i=0; i < size; i++)
    {
        for(size_t j = i + 1; j < size && (strip[j].get_coordinates()[1] - strip[i].get_coordinates()[1]) < min; j++)
        {
            if(dist(strip[i], strip[j]) < min)
            {
                min = dist(strip[i], strip[j]);
            }
        }
    }
    return min;
}

/**
 * @brief A recursive function to find the smallest distance
 * 
 * @param px Contains all pointes sorted according to x coordinates.
 * @param py Contains all pointes sorted according to y coordinates.
 * @param n  Number of points.    
 * @return double Return thee minimum distace of two points based on the length of given arrays.
 */
double ClosestPair::closest_util(vector<point> px, vector<point> py, uint64_t n)
{
    // if n < 3
    uint64_t mid = n / 2;
    point midPoint = px[mid];
    vector<point> points_y_left(mid);
    vector<point> points_y_right(n - mid);
    uint64_t li = 0;
    uint64_t ri = 0;
    for(size_t i = 0; i < n; i++)
    {
       if((py[i].get_coordinates()[0] < midPoint.get_coordinates()[0] || (py[i].get_coordinates()[0] == midPoint.get_coordinates()[0])) && li < mid)
       {
           points_y_left[li++] = py[i];
       }
       else
       {
           points_y_right[ri++] = py[i];
       }
    }
    double dl = closest_util(px, points_y_left, mid);
    double dr = closest_util(Utility::return_part(px, mid-1), points_y_right, n-mid);

    double d = min(dl, dr);

    vector<point> strip(n);
    uint64_t j = 0;
    for(size_t i = 0; i < n; i++)
    {
        if(abs(py[i].get_coordinates()[0] - midPoint.get_coordinates()[0]) < d)
        {
            strip[j] = py[i];
            j++;
        }
    }
    return strip_closest(strip, j, d);

}
/**
 * @brief Main method to find the closest pairs. Calling other methods.
 * Print out the result
 */
void ClosestPair::solve()
{
    uint64_t n = points.size();
    vector<point> px;
    vector<point> py;
    px.assign(points.begin(), points.end());
    py.assign(points.begin(), points.end());
    sort(px.begin(), px.end(),
    [&](const point& lhs, const point& rhs)->bool
    {
        if(lhs.get_coordinates()[0] != rhs.get_coordinates()[0])
        {
            if((lhs.get_coordinates()[0] - rhs.get_coordinates()[0] > 0))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if((lhs.get_coordinates()[1] - rhs.get_coordinates()[1] > 0))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    });
    sort(py.begin(), py.end(),
    [&](const point& lhs, const point& rhs)->bool
    {
        if(lhs.get_coordinates()[1] != rhs.get_coordinates()[1])
        {
            if((lhs.get_coordinates()[1] - rhs.get_coordinates()[1] > 0))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if((lhs.get_coordinates()[0] - rhs.get_coordinates()[0] > 0))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    });
    
    cout << "The answer" << closest_util(px, py, n) << endl;
}
