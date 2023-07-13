//
// Created by Brendan on 2022-11-11.
//

#ifndef LAB1TEMPLATE_TOUR_HPP
#define LAB1TEMPLATE_TOUR_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "city.hpp"

class tour {
private:
    vector<city*> cities; //List of all cities to visit in tour
    double fitness; //Total distance to travel to all cities and back to first

public:
    tour(const tour& t) : fitness(t.fitness) {
        for (city* c : t.cities) {
            cities.push_back(c);
        }
    }

    tour() {}

    void addToTour(city* city);
    double getFitness() const;
    void setFitness(double fit);
    vector<city*> getCities();
    double get_distance_between_cities(city* a, city* b);

    void tourSwap(tour& t1, tour& t2) {
        std::swap(t1.fitness, t2.fitness);
        for(int i = 0; i < (int) t1.cities.size(); i++) {
            t1.cities.at(i) = t2.cities.at(i);
        }
    }

    tour& operator=(tour t) {
        tourSwap(*this,t);
        return *this;
    }
};

#endif //LAB1TEMPLATE_TOUR_HPP
