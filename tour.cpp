//
// Created by Brendan on 2022-11-11.
//

#include "tour.hpp"

void tour::addToTour(city *city) {
    cities.push_back(city);
}

double tour::getFitness() const {
    return fitness;
}

vector<city *> tour::getCities() {
    return cities;
}

void tour::setFitness(double fit) {
    fitness = fit;
}

double tour::get_distance_between_cities(city *a, city *b) {
    return sqrt((pow(a->getX() - b->getX(), 2)) + (pow(a->getY() - b->getY(), 2)));
}
