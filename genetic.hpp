//
// Created by Brendan on 2022-11-18.
//

#ifndef LAB1TEMPLATE_GENETIC_HPP
#define LAB1TEMPLATE_GENETIC_HPP

#include "population.hpp"
#include <cfloat>

class genetic {
private:
    //Genetic constants and class variables
    static constexpr int ITERATIONS = 1000;
    static constexpr int PARENT_POOL_SIZE = 5;
    static constexpr int MUTATION_RATE = 15;
    static constexpr double IMPROVEMENT_FACTOR = 1.3; //Improvement factor set to 30%
    static constexpr int CITIES_IN_TOUR = 32;
    static constexpr int POPULATION_SIZE = 32;
    int counter = 0; //Counter to keep track of what iteration while loop is on
    double fitness = 0; //Best distance
    double curFitness = 0; //Base distance -> best tour in current generation of tours
    int fitnessLoc = 0; //Gets the location of the fittest tour in the tours vector
    double originalEliteDistance = 0;
    bool updateElite = false; //Switch to print update elite message if new fitness is found
    bool firstIteration = true; //Switch if the genetic algorithm is in its first iteration

    //Create new population
    population* p = new population(); //For initial population (iteration 1)
    vector<tour*> popTours; //For next generation populations (iteration 2+)
    vector<tour*> originalElite; //Retain master list of population
public:
    vector<city*> createCityMasterList(vector<city*> masterList);
    tour* createTour(vector<city*> masterList);
    void createPopulation(vector<city*> masterList);
    double findFittestTour(); //For population p
    double findFittestTour2(); //For popTours
    int findFittestTourIndex(vector<tour*> t);
    void swapTours(int index);
    int randomNumberGenerator(int min, int max);
    tour* createChildTour(tour* a, tour* b);
    void crossover();
    void mutate();
    void report();
    void reportResults(vector<tour*> originalElite);
    void runGenetic(); //Core of class. This function is where the genetic algorithm is contained
};

#endif //LAB1TEMPLATE_GENETIC_HPP
