#ifndef ClosestPair_HPP

#define ClosestPair_HPP

#include "point.hpp"
#include "GeometryAlgorithms.hpp"

#include <vector>


class ClosestPair : public GeometryAlgorithms
{
public:
    void solve() override;
    void read_points(std::string address) override;
    double dist(const point &p1, const point &p2) const;
    double min(double x, double y);
    double strip_closest(std::vector<point> strip,uint64_t size, double d);
    double closest_util(std::vector<point> px, std::vector<point> py, uint64_t n);
private:
    std::vector<point> points;
};

#endif