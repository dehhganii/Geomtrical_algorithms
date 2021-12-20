#include "ClosestPair.hpp"
#include "Utility.hpp"
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

void ClosestPair::read_points(std::string address)
{  
    points = Utility::read_points(address);
}

double ClosestPair::dist(const point &p1, const point &p2) const
{
    return sqrt(Utility::square_distance(p1, p2));
}


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