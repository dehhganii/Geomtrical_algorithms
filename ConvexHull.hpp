#ifndef ConvexHull_HPP

#define ConvexHull_HPP

#include "point.hpp"
#include "GeometryAlgorithms.hpp"
#include <vector>
#include <stack>
class ConvexHull : public GeometryAlgorithms
{
public:
    void solve() override;
    void read_points(std::string) override;
    point nextToTop(std::stack<point> &s);
    void swap(point &p1, point &p2);
    int compare(const void *vp1, const void *vp2);
    int orientation(const point &p, const point &q, const point &r);
    point p0;   
private:
    std::vector<point> points;

};

#endif