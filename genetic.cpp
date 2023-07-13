//
// Created by Brendan on 2022-11-18.
//

#include "genetic.hpp"
#include <random>
#include <iostream>

vector<city*> genetic::createCityMasterList(vector<city*> masterList) {
    for (int i = 0; i < CITIES_IN_TOUR; i++) {
        //Create name for city
        std::string name = "city " + std::to_string(i);

        //Create new city with random coordinates
        city* c = new city(name, p->generateRandomCoordinate(),
                           p->generateRandomCoordinate());

        //Add city to master list
        masterList.push_back(c);
    }

    return masterList;
}

tour* genetic::createTour(vector<city *> masterList) {

    vector<city*> newCities = masterList;

    //Create a random seed
    random_device rd;

    //Shuffle cities
    shuffle(std::begin(newCities),std::end(newCities), std::default_random_engine(rd()));

    //Create tour
    tour* t = new tour;

    //Add cities to tour
    for (int i = 0; i < (int) newCities.size(); i++) {
        t->addToTour(newCities.at(i));
    }

    //Calculate the tour's fitness rating
    for (int i = 0; i < (int) t->getCities().size() - 1; i++) {
        double tourFitness = t->get_distance_between_cities(t->getCities().at(i),
                                                            t->getCities().at(i + 1));
        t->setFitness(tourFitness);
    }

    return t;
}

void genetic::createPopulation(vector<city*> masterList) {
    //Create population
    for (int i = 0; i < POPULATION_SIZE; i++) {
        //Create tour
        tour* t = createTour(masterList);

        //Add tour to population
        p->setTour(t);
    }
}

double genetic::findFittestTour() {

    //Initialize fittest
    double fittest = p->getTours().front()->getFitness();

    //Finds the fittest tour by getting the lowest fitness rating out of the population
    //Also get the index of the fittest tour in the tours vector
    for (int i = 1; i < (int) p->getTours().size(); i++) {
        if (p->getTours().at(i)->getFitness() <= fittest) {
            fittest = p->getTours().at(i)->getFitness();
            fitnessLoc = i;
        }
    }

    return fittest;
}

double genetic::findFittestTour2() {
    //Initialize fittest
    double fittest = popTours.front()->getFitness();

    //Finds the fittest tour by getting the lowest fitness rating out of the population
    //Also get the index of the fittest tour in the tours vector
    for (int i = 1; i < (int) popTours.size(); i++) {
        if (popTours.at(i)->getFitness() < fittest) {
            fittest = popTours.at(i)->getFitness();
            fitnessLoc = i;
        }
    }

    return fittest;
}

int genetic::findFittestTourIndex(vector<tour *> t) {

    //Initialize fittest
    double fittest = t.front()->getFitness();
    int index = 0;

    //Find the index of the fittest tour for crossover
    for (int i = 0; i < (int) t.size(); i++) {
        if (t.at(i)->getFitness() < fittest) {
            index = i;
        }
    }

    return index;
}

void genetic::swapTours(int index) {
    //Swap tour at front of tours vector with elite tour
    std::swap(popTours.front(),popTours.at(index));
}

int genetic::randomNumberGenerator(int min, int max) {
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(min, max);

    return distribution(generator);
}

tour *genetic::createChildTour(tour* a, tour* b) {
    //Get random index
    int randomIndex = randomNumberGenerator(0, (int) a->getCities().size() - 1);

    //Create child tour
    tour* child = new tour;

    //Copy cities from set 1 up-to and including randomIndex
    for (int i = 0; i < (int) randomIndex; i++) {
        child->setFitness(child->get_distance_between_cities(a->getCities().at(i),
                                                             a->getCities().at(i+1)));
        child->addToTour(a->getCities().at(i));
    }

    //Copy the remaining cities from set 2 (no duplicates)
    bool isDuplicate = false;
    for (int i = randomIndex + 1; child->getCities().size() != b->getCities().size(); i++) {
        //Set i to randomIndex + 1. If i is equal to last element in vector, then reset to 0
        //to wrap loop around, until all cities are added to child
        if (i == (int) b->getCities().size()) {
            i = 0;
        }

        city* cityToAdd = b->getCities().at(i);

        //Check if cityToAdd is in child, if so don't add it. Else, add the city to child
        for (int j = 0; j < (int) child->getCities().size(); j++) {
            if (cityToAdd == child->getCities().at(j)) {
                isDuplicate = true;
            }
        }

        if (!isDuplicate) {
            if (i == (int) b->getCities().size() - 1) {
                child->setFitness(child->get_distance_between_cities(a->getCities().at(i),
                                                                     a->getCities().at(0)));
            } else {
                child->setFitness(child->get_distance_between_cities(a->getCities().at(i),
                                                                     a->getCities().at(i+1)));
            }

            child->addToTour(cityToAdd);
        }

        isDuplicate = false;
    }

    return child;
}

void genetic::crossover() {
    vector<tour*> crosses; //New tour of crossover tours
    vector<tour*> set1; //Parent A
    vector<tour*> set2; //Parent B
    tour* fittest1; //Fittest tour in set1
    tour* fittest2; //Fittest tour in set2
    int fittest1Index; //Index number of the fittest tour in set 1
    int fittest2Index; //Index number of the fittest tour in set 2

    //Move elite tour to the crosses tour
    crosses.push_back(popTours.front());

    for (int k = 1; k < CITIES_IN_TOUR; k++) {
        //Delete and clear sets vectors
        set1.clear();
        set2.clear();

        //Select 5 random tours for each parent that are unique
        for (int i = 0; i < PARENT_POOL_SIZE; i++) {
            set1.push_back(popTours.at(randomNumberGenerator(1,
                                                                  (int) p->getTours().size() - 1)));
        }

        //Select another 5 random tours that are not in the first set
        for (int j = 0; j < PARENT_POOL_SIZE; j++) {
            set2.push_back(popTours.at(randomNumberGenerator(1,
                                                                  (int) p->getTours().size() - 1)));
        }

        //Get the indexes of the fittest tours in both set 1 and 2
        fittest1Index = findFittestTourIndex(set1);
        fittest2Index = findFittestTourIndex(set2);

        //Assign the fittest tour in each set to the fittest variables
        fittest1 = set1.at(fittest1Index);
        fittest2 = set2.at(fittest2Index);

        //Perform the crossover to generate a new child tour
        crosses.push_back(createChildTour(fittest1,fittest2));
    }

    //Re-populate population with next generation of tours
    for (int i = 0; i < (int) popTours.size(); i++) {
        *popTours.at(i) = *crosses.at(i);
    }

   //Reset the crosses vector
    crosses.clear();
}

void genetic::mutate() {
    for (int i = 1; i < (int) popTours.size(); i++) {
        //Generate random tour mutation rate
        int mutationRate = randomNumberGenerator(0, 100);

        if (mutationRate < MUTATION_RATE) {
            if (i == (int) popTours.size() - 1) {
                tour* t1 = popTours.at(i);
                tour* t2 = popTours.at(0);
                popTours.at(i) = t2;
                popTours.at(0) = t1;
            } else {
                tour* t1 = popTours.at(i);
                tour* t2 = popTours.at(i + 1);
                popTours.at(i) = t2;
                popTours.at(i + 1) = t1;
            }
        }
    }
}

void genetic::report() {

    //Get current tours in population
    vector<tour*> t = popTours;

    //On first iteration display original elite distance
    if (firstIteration) {
        std::cout << "--STARTING ALGORITHM--" << std::endl;
        std::cout << "Iteration: " << counter << std::endl;
        std::cout << "NEW ELITE FOUND:" << std::endl;
        std::cout << "Original elite distance: " << std::to_string(originalEliteDistance) << std::endl;
        std::cout << "(";

        for (int i = 0; i < (int) t.size() - 1; i++) {
            std::cout << t.front()->getCities().at(i)->getName() << "->";
        }

        std::cout << t.front()->getCities().back()->getName() << ")" << std::endl;
        std::cout << std::endl;

        //Copy initial tour of cities
        originalElite = p->copyTours(t);

        firstIteration = false;
    } else {
        //In all other cases after first iteration, display appropriate message depending on
        //if a new elite was found or not
        std::cout << "Iteration: " << counter << std::endl;

        if (updateElite) {
            std::cout << "NEW ELITE FOUND:" << std::endl;
            std::cout << "Distance: " << std::to_string(fitness) << std::endl;
            updateElite = false;
        } else {
            std::cout << "Elite distance: " << std::to_string(fitness) << std::endl;
            std::cout << "Best non-elite distance: " << std::to_string(curFitness) << std::endl;
        }

        std::cout << std::endl;
        std::cout << "(";

        for (int i = 0; i < (int) p->getTours().size() - 1; i++) {
            std::cout << p->getTours().front()->getCities().at(i)->getName() << "->";
        }

        std::cout << p->getTours().front()->getCities().back()->getName() << ")" << std::endl;

        std::cout << "Improvement over base: " << std::to_string(curFitness / fitness) << std::endl;
        std::cout << std::endl;
    }

    //Reset t for next iteration
    t.clear();
}

void genetic::reportResults(vector<tour*> originalElite) {
    std::cout << "--FINISHED ALGORITHM--" << std::endl;
    std::cout << "Original elite:" << std::endl;
    std::cout << "Distance: " << std::to_string(originalEliteDistance) << std::endl;
    std::cout << "(";

    for (int i = 0; i < (int) originalElite.size() - 1; i++) {
        std::cout << originalElite.front()->getCities().at(i)->getName() << "->";
    }

    std::cout << originalElite.front()->getCities().back()->getName() << ")" << std::endl;
    std::cout << std::endl;

    std::cout << "Best elite: " << std::endl;
    std::cout << "Distance: " << std::to_string(fitness) << std::endl;
    std::cout << "(";

    //Get current tours in population
    vector<tour*> t = popTours;

    for (int i = 0; i < (int) t.size() - 1; i++) {
        std::cout << t.front()->getCities().at(i)->getName() << "->";
    }

    std::cout << t.front()->getCities().back()->getName() << ")" << std::endl;

    if ((curFitness / fitness) >= IMPROVEMENT_FACTOR) {
        std::cout << "Improvement factor reached!" << std::endl;
    }

    std::cout << "Improvement factor: " << std::to_string(curFitness / fitness) << std::endl;
}

void genetic::runGenetic() {
    //Create master list of cities
    vector<city*> masterList;
    masterList = createCityMasterList(masterList);

    //Create tours and population
    createPopulation(masterList);

    //Evaluate population
    curFitness = findFittestTour(); //Base distance (current fittest tour in this generation)
    fitness = curFitness; //Overall fittest tour in entire run (Best distance)
    originalEliteDistance = fitness; //Set original elite's distance
    //originalElite = p->copyTours(p->getTours()); //Set original elite to initial state
    popTours = p->getTours(); //Initialize next generation population with initial population

    //loop until improvement factor or number of iterations go over limit
    while ((curFitness / fitness) < IMPROVEMENT_FACTOR && counter <= ITERATIONS) {
        //Move the elite to the front of the tours vector
        swapTours(fitnessLoc);

        //Perform crossover
        crossover();

        //Perform mutation
        mutate();

        //Re-evaluate population
        curFitness = findFittestTour2();

        //If current fitness in this generation is better than the previous, update overall fitness
        if (curFitness < fitness) {
            fitness = curFitness;
            updateElite = true;
        }

        //Report the progress of the algorithm
        report();

        //Iterate to next loop
        counter++;
    }

    //Report results
    reportResults(originalElite);
}
