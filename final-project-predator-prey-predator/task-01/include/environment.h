#pragma once

#include <array>
#include <random>

struct Environment
{
    auto restrict_position(std::array<double, 2>& position) const->void;

    auto reflect(const std::array<double, 2>& position, std::array<double, 2>& velocity) const->void;

    auto get_multiplier(const std::array<double, 2>& position) const->std::array<double, 2>;

    auto speed_terrain(const std::array<double, 2>& position) const->bool;

    auto slow_terrain(const std::array<double, 2>& position) const->bool;

    std::array<double, 2> speed_x_terrain{};
    std::array<double, 2> speed_y_terrain{};
    std::array<double, 2> slow_x_terrain{};
    std::array<double, 2> slow_y_terrain{};
    std::array<double, 2> x_limit{ -100, 100 };
    std::array<double, 2> y_limit{ -100, 100 };
};