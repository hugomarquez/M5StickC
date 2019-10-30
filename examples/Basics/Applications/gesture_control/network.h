#pragma once
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include "./matrix.h"

namespace nnet {
  class Network {
  public:
    std::vector<Matrix<double>> weight;
    std::vector<Matrix<double>> bias;

    Network(std::vector<int> neurons, double learningRate);
    Matrix<double> computeOutput(std::vector<double> input);
    void learn(std::vector<double> expectedOutput);

    static double random(double x);
    static double sigmoid(double x);
    static double sigmoidPrime(double x);
    static double stepFunction(double x);
  private:
    std::vector<Matrix<double>> hidden;
    std::vector<Matrix<double>> dEdW;
    std::vector<Matrix<double>> dEdB;
    Matrix<double> output;
    int hiddenLayersCount;
    double learningRate;
  };
}
