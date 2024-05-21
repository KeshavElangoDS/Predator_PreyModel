#include "prey.h"
#include "predator.h"
#include "environment.h"

#include <algorithm>
#include <cmath>

auto Prey::flee(const double time_delta, Predator& predator, const Environment& environment) -> void
{

    auto waypoint_distance = std::hypot(
        waypoint[0] - position[0],
        waypoint[1] - position[1]
    );

    auto predator_distance = std::hypot(
        predator.position[0] - position[0],
        predator.position[1] - position[1]
    );

    auto angle = std::atan2(
        waypoint[0] - position[0],
        waypoint[1] - position[1]
    );

    if (waypoint_distance <= 1.0)
    {
        auto point = dis(eng);
        waypoint[0] = point;
        waypoint[1] = point;
    }
    else if (predator_distance <= 10.0)
    {
        position[0] += (prey_speed[0] * std::cos(angle * 3.14) * time_delta) * -5;
        position[1] += (prey_speed[1] * std::sin(angle * 3.14) * time_delta) * -5;
    }
    else if (environment.speed_terrain(position))
    {
        position[0] += (prey_speed[0] * std::cos(angle) * time_delta) * 3;
        position[1] += (prey_speed[1] * std::sin(angle) * time_delta) * 3;
    }
    else if (environment.slow_terrain(position))
    {
        position[0] += (prey_speed[0] * std::cos(angle) * time_delta) / 10;
        position[1] += (prey_speed[1] * std::sin(angle) * time_delta) / 10;
    }
    else
    {
        auto modification = environment.get_multiplier(position);
        position[0] += prey_speed[0] * std::cos(angle) * modification[0] * time_delta;
        position[1] += prey_speed[1] * std::sin(angle) * modification[1] * time_delta;
    }
    environment.restrict_position(position);
    environment.reflect(position, prey_speed);
}
auto Prey::deplete(int requested) -> int
{
    auto amount = std::min(requested, prey_amount);
    prey_amount -= amount;
    return amount;
}
