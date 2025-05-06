#include "./math.hpp"

#include <cmath>

bool float_equal(float a, float b) {
    if (!(std::isfinite(a) && std::isfinite(b)))
        return a == b;

    constexpr float absolute_tolerance = std::numeric_limits<float>::min();
    constexpr float relative_tolerance = std::numeric_limits<float>::epsilon();

    const auto diff = std::abs(a - b);

    return diff <= absolute_tolerance ||
           diff <= relative_tolerance * std::max(std::abs(a), std::abs(b));
}
