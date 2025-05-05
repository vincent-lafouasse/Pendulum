#include "Vec2.hpp"

#include <sstream>

std::string Vec2::repr() const {
    std::stringstream s;

    s << "Vec2 { " << x << ", " << y << " }";
    return s.str();
}
