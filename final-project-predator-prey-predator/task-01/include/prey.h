#pragma once

#include "environment.h"

struct Predator;
struct Prey
{
    auto flee(const double time_delta, Predator& predator, const Environment& environment) -> void;
    
    auto deplete(int requested) -> int;
    
    int prey_amount{ 0 };

    double direction{};
    std::array<double, 2> position{};
    std::array<double, 2> prey_speed{};
    std::array<double, 2> waypoint{};
    std::mt19937 eng{};
    std::uniform_real_distribution<> dis{};
};