#pragma once

#include <random>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "prey.h"
#include "predator.h"
#include "environment.h"

struct Model
{
    Model(const std::string& file_path);

    void initialize();
    void update(const double time_delta);
    void finalize();

    double time{};
    json config{};
    Predator predator{};
    std::vector<Prey> preys{};
    Environment environment{};
};