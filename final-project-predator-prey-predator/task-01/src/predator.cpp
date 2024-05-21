#include "predator.h"
#include "prey.h"
#include "environment.h"

#include <algorithm>
#include <cmath>
#include <vector>
#include<random>

auto Predator::chase(const double time_delta, std::vector<Prey>& preys, const Environment& environment) -> void
{
    auto current_prey_size = preys.size();
    auto get_closest_prey = [&](const Prey& p1, const Prey& p2) -> bool
        {
            auto d1 = std::hypot(
                p1.position[0] - position[0], // dx
                p1.position[1] - position[1]  // dy
            );
            auto d2 = std::hypot(
                p2.position[0] - position[0], // dx
                p2.position[1] - position[1]  // dy
            );
            return d1 < d2;
        };
    auto closest_prey = std::ranges::min_element(preys, get_closest_prey);

    auto angle = std::atan2(
        closest_prey->position[1] - position[1],
        closest_prey->position[0] - position[0]
    );
    auto distance = std::hypot(
        closest_prey->position[0] - position[0],
        closest_prey->position[1] - position[1]
    );
    current_prey.position = closest_prey->position;
    if (distance < 1.0 && closest_prey->prey_amount> 0)
    {
        prey_amount += closest_prey->deplete(1);
    }
    else if (current_prey_size < total_prey)
    {
        total_prey = current_prey_size;
        position[0] += predator_speed[0] * std::cos(angle) * time_delta;
        position[1] += predator_speed[1] * std::sin(angle) * time_delta;
    }
    else
    {
        auto old_angle = std::atan2(
            current_prey.position[1] - position[1],
            current_prey.position[0] - position[0]
        );
        position[0] += predator_speed[0] * std::cos(old_angle) * time_delta;
        position[1] += predator_speed[1] * std::sin(old_angle) * time_delta;
    }


    environment.restrict_position(position);
    environment.reflect(position, predator_speed);

}