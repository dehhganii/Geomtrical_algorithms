#include <vector>
#include "Utility.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "point.hpp"
using namespace std;

vector<point> Utility::read_points(string address)
{
    vector<point> points;
    ifstream input(address);
    if(!input.is_open())
    {
        cout << "Error opening file" << std::endl; 
        exit(-1);
    }
    string line;
    while(getline(input, line))
    {   
        uint64_t pos = line.find(",");
        if(pos == string::npos && line.size() == 0)
        {
            points.push_back(point());
        }
        else
        {
            if(pos == string::npos)
            {
                points.push_back(point(stod(line)));
            }
            else
            {
                points.push_back(point(stod(line.substr(0, pos)), stod(line.substr(pos + 1))));
            }
        }
    }
    return points;
}

double Utility::square_distance(const point &p1, const point &p2)
{
    return  ((p1.get_coordinates()[0] - p2.get_coordinates()[0]) * (p1.get_coordinates()[0] - p2.get_coordinates()[0])) + 
            ((p1.get_coordinates()[1] - p2.get_coordinates()[1]) * (p1.get_coordinates()[1] - p2.get_coordinates()[1]));
            
}

vector<point> Utility::return_part(vector<point> points, uint64_t part)
{
    vector<point> answer;
    for(size_t i = part; i < points.size(); i++)
    {
        answer.push_back(points[i]);
    }
    return answer;
}
