#pragma once

#include <vector>
#include <array>

#include "prey.h"
#include "environment.h"

struct Predator
{
    auto chase(const double time_delta, std::vector<Prey>& preys, const Environment& environment) -> void;
    int prey_amount{ 0 };
    Prey current_prey{};
    std::size_t total_prey{};
    std::array<double, 2> position{};
    std::array<double, 2> predator_speed{};
};