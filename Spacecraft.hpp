#pragma once
#include <cmath>

constexpr double DT = 0.1;
constexpr double DEG2RAD = M_PI / 180.0;

struct Vec3 {
    double x{}, y{}, z{};
};

class Spacecraft {
public:
    Vec3 pos{};
    Vec3 vel{};
    double pitch{0}, yaw{0};   // degrees
    double thrust{0};          // 0–1
    double fuel{100};          // %
    bool engine_on{false};

    void update();
};
