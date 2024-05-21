#include "model.h"

#include <fstream>
#include <numbers>

#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std::numbers;

Model::Model(const std::string& file_path)
{
    time = 0.0;
    auto cfs = std::ifstream{ file_path };
    config = json::parse(cfs);
    initialize();
}

void Model::initialize()
{
    auto number_of_preys = config["number_of_preys"].get<std::size_t>();
    preys.resize(number_of_preys);

    auto seed = config["seed"].get<std::size_t>();
    auto prey_speed = config["prey_speed"].get<std::double_t>();
    auto region_limit = config["region_limit"].get<std::double_t>();
    auto predator_speed = config["predator_speed"].get<std::double_t>();

    environment.x_limit = std::array<double, 2>{ -region_limit, region_limit };
    environment.y_limit = std::array<double, 2>{ -region_limit, region_limit };

    auto eng = std::mt19937{ seed };
    auto dis = std::uniform_real_distribution<>{ -region_limit, region_limit };

    predator.predator_speed[0] = predator_speed;
    predator.predator_speed[1] = predator_speed;
    predator.position[0] = dis(eng);
    predator.position[1] = dis(eng);
    predator.total_prey = number_of_preys;

    std::ranges::generate(preys, [&]() -> Prey {
        return {
            1,
            1.0,
            {dis(eng), dis(eng)},
            {prey_speed, prey_speed},
            {dis(eng), dis(eng)},
            {eng},
            {dis}
        };});

    predator.current_prey = preys[1];

    auto terrain_dis = std::uniform_real_distribution<>{ region_limit - 10.0, region_limit - 50.0 };
    auto min_lim = terrain_dis(eng);
    auto max_lim = terrain_dis(eng);
    environment.speed_x_terrain[0] = min_lim - 10.0;
    environment.speed_x_terrain[1] = max_lim - 5.0;
    environment.speed_y_terrain[0] = min_lim - 60.0;
    environment.speed_y_terrain[1] = max_lim - 15.0;

    environment.slow_x_terrain[0] = min_lim - 110.0;
    environment.slow_x_terrain[1] = max_lim - 60.0;
    environment.slow_y_terrain[0] = min_lim - 150.0;
    environment.slow_y_terrain[1] = max_lim - 100.0;

}

void Model::update(const double time_delta)
{
    time += time_delta;
    for (auto& prey : preys)
    {
        prey.flee(time_delta, predator, environment);
    }
    std::erase_if(preys, [](Prey p) {return p.prey_amount == 0;});

    predator.chase(time_delta, preys, environment);
}

void Model::finalize()
{}