
#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

 int BOARD_SIZE ;
const int POPULATION_SIZE = 1000;
const int MUTATION_RATE = 5; // Percentage
const int MAX_GENERATIONS = 10000;

// Calculates fitness based on number of non-attacking pairs
int calculateFitness(const vector<int> &genes) {
    int fitness = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = i + 1; j < BOARD_SIZE; ++j) {
            if (genes[i] != genes[j] && abs(genes[i] - genes[j]) != j - i)
                fitness++;
        }
    }
    return fitness;
}

// Initializes the population with random positions
vector<vector<int>> initializePopulation() {
    vector<vector<int>> population(POPULATION_SIZE, vector<int>(BOARD_SIZE));
    for (auto &genes : population) {
        for (int &gene : genes) {
            gene = rand() % BOARD_SIZE;
        }
    }
    return population;
}

// Selects a parent based on fitness (roulette wheel selection)
vector<int> selectParent(const vector<vector<int>> &population, const vector<int> &fitnesses) {
    int totalFitness = accumulate(fitnesses.begin(), fitnesses.end(), 0);
    int randomFitness = rand() % totalFitness;
    int runningSum = 0;
    for (int i = 0; i < POPULATION_SIZE; ++i) {
        runningSum += fitnesses[i];
        if (runningSum > randomFitness)
            return population[i];
    }
    return population.back();
}

// Crosses two parents to create a child
vector<int> crossover(const vector<int> &parent1, const vector<int> &parent2) {
    vector<int> child(BOARD_SIZE);
    int crossoverPoint = rand() % BOARD_SIZE;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        child[i] = (i < crossoverPoint) ? parent1[i] : parent2[i];
    }
    return child;
}

// Mutates an individual by changing one of its genes randomly
void mutate(vector<int> &genes) {
    if (rand() % 100 < MUTATION_RATE) {
        int mutationPoint = rand() % BOARD_SIZE;
        genes[mutationPoint] = rand() % BOARD_SIZE;
    }
}

// Runs the genetic algorithm
void geneticAlgorithm() {
    vector<vector<int>> population = initializePopulation();
    vector<int> fitnesses(POPULATION_SIZE);

    for (int generation = 0; generation < MAX_GENERATIONS; ++generation) {
        // Calculate fitness for each individual
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            fitnesses[i] = calculateFitness(population[i]);
        }

        // Sort population based on fitness
        auto maxFitness = (BOARD_SIZE * (BOARD_SIZE - 1)) / 2; // Maximum fitness for non-attacking pairs
        int bestIndex = max_element(fitnesses.begin(), fitnesses.end()) - fitnesses.begin();

        // If a solution is found
        if (fitnesses[bestIndex] == maxFitness) {
            cout << "Solution found in generation " << generation << ":\n";
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    cout << (population[bestIndex][i] == j ? "Q " : ". ");
                }
                cout << endl;
            }
            return;
        }

        // Create a new population
        vector<vector<int>> newPopulation;
        for (int i = 0; i < POPULATION_SIZE; ++i) {
            vector<int> parent1 = selectParent(population, fitnesses);
            vector<int> parent2 = selectParent(population, fitnesses);
            vector<int> child = crossover(parent1, parent2);
            mutate(child);
            newPopulation.push_back(child);
        }
        population = newPopulation;
    }
    cout << "Solution not found within max generations." << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    cout << "Enter Board Size: ";
    cin >> BOARD_SIZE;
    geneticAlgorithm();
    return 0;
}












