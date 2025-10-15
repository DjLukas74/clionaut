#include "Spacecraft.hpp"

void Spacecraft::update() {
    if (engine_on && fuel > 0) {
        double pitch_rad = pitch * DEG2RAD;
        double yaw_rad   = yaw * DEG2RAD;

        Vec3 thrust_dir{
            std::cos(pitch_rad) * std::cos(yaw_rad),
            std::sin(pitch_rad),
            std::cos(pitch_rad) * std::sin(yaw_rad)
        };

        double accel = thrust * 0.05;
        vel.x += thrust_dir.x * accel * DT;
        vel.y += thrust_dir.y * accel * DT;
        vel.z += thrust_dir.z * accel * DT;

        fuel -= thrust * 0.01 * DT;
        if (fuel < 0) fuel = 0;
    }

    pos.x += vel.x * DT;
    pos.y += vel.y * DT;
    pos.z += vel.z * DT;
}
