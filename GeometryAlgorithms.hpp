#ifndef GeometryAlgorithms_HPP

#define GeometryAlgorithms_HPP
#include "point.hpp"
#include <vector>
#include <string>

class GeometryAlgorithms
{
public:
    virtual void read_points(std::string address);
    virtual void solve();
};

#endif