#include<iostream>
#include <vector>
#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include "Utility.hpp"
#include "ConvexHull.hpp"
#include "graphic.hpp"
#include "ClosestPair.hpp"
using namespace std;

int main()
{
    
    string file = Utility::address = "points.txt";
    vector<point> points;
    
    GeometryAlgorithms* alg;

    ConvexHull convex_hull;

    alg = &convex_hull;
    alg->read_points("points.txt");
    alg->solve();

    /*

    const int64_t width = 200;
    const int64_t height = 200;

    Graphic graphic(width, height);

    for (int y=0; y < height; y++)
    {
        for(int x=0; x < width; x++)
        {
            graphic.set_color(Color(100, 100, 100), x, y);
        }
    }


    for (int y=40; y < 60; y++)
    {    
        graphic.set_color(Color(200, 100, 0), 40, y);
    }
    graphic.Export("image.bmp");
    
    GeometryAlgorithms* alg1;
    ClosestPair closest_pair;

    alg1 = &closest_pair;
    alg1->read_points("points.txt");
    alg1->solve();
    */

    ClosestPair closest;
    //closest.read_points("points.txt");
    //closest.solve();
    
}

