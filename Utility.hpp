
/**
 * @file Utility.hpp
 * @author dehghh1@mcmaster.ca
 * @brief This class is for method that is used in different algorithms
 * @version 0.1
 * @date 2021-12-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <vector>
#include <string>
#include "point.hpp"
class Utility
{
public:
    static std::vector<point> read_points(std::string);
    static double square_distance(const point &p1, const point &p2);
    static std::vector<point> return_part(std::vector<point> points, uint64_t part);
    
};
