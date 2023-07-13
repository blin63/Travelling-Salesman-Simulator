//
// Created by Brendan on 2022-11-18.
//

#include "population.hpp"
#include <random>
#include <vector>

double population::generateRandomCoordinate() const {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(MIN, MAX);

    return distribution(generator);
}

void population::setTour(tour * tour) {
    tours.push_back(tour);
}

vector<tour*> population::getTours() {
    return tours;
}

vector<tour *> population::copyTours(vector<tour*> t) {
    //Create new vector of tours
    vector<tour*> ct;

    //Copy the tours to the new vector of tours
    for (tour* et : t) {
        ct.push_back(new tour(*et));
    }

    return ct;
}

population::~population() {

    //Delete both the cities and tours
    for (tour* i : tours) {
        for (city* j : i->getCities()) {
            delete j;
        }

        delete i;
    }
}
