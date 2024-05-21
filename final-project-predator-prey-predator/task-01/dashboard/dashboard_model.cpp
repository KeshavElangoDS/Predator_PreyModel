#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#include "model.h"
#include "prey.h"
#include "predator.h"
#include "environment.h"

PYBIND11_MODULE(model, m) {
    py::class_<Model>(m, "Model")
        .def(py::init<const std::string&>())
        .def("initialize", &Model::initialize)
        .def("update", &Model::update)
        .def("finalize", &Model::finalize)
        .def_readwrite("time", &Model::time)
        .def_readwrite("config", &Model::config)
        .def_readwrite("environment", &Model::environment)
        .def_readwrite("predator", &Model::predator)
        .def_readwrite("preys", &Model::preys);

    py::class_<Predator>(m, "Predator")
        .def_readwrite("position", &Predator::position)
        .def_readwrite("predator_speed", &Predator::predator_speed);

    py::class_<Prey>(m, "Prey")
        .def_readwrite("position", &Prey::position)
        .def_readwrite("prey_speed", &Prey::prey_speed);

    py::class_<Environment>(m, "Environment")
        .def_readwrite("x_limit", &Environment::x_limit)
        .def_readwrite("y_limit", &Environment::y_limit);
}
