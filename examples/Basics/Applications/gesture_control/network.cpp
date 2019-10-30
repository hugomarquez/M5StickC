#include "./network.h"

namespace nnet {
  Network::Network(std::vector<int> neurons, double learningRate) {
    srand (time(NULL));
    this->learningRate = learningRate;
    this->hiddenLayersCount = neurons.size() - 2;

    hidden = std::vector<Matrix<double>> (hiddenLayersCount + 2);
    weight = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    bias   = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    dEdW   = std::vector<Matrix<double>> (hiddenLayersCount + 1);
    dEdB   = std::vector<Matrix<double>> (hiddenLayersCount + 1);

    for (int i = 0; i < neurons.size() - 1; i++) {
      weight[i] = Matrix<double>(neurons[i], neurons[i + 1]);
      bias[i] = Matrix<double>(1, neurons[i + 1]);
      weight[i] = weight[i].applyFunction(random);
      bias[i] = bias[i].applyFunction(random);
    }
  }

  Matrix<double> Network::computeOutput(std::vector<double> input) {
    // row matrix
    hidden[0] = Matrix<double>({input});
    for (int i = 1; i < hiddenLayersCount + 2; i++) {
      hidden[i] = hidden[i - 1].dot(weight[i - 1]).add(bias[i - 1]).applyFunction(sigmoid);
    }
    return hidden[hiddenLayersCount + 1];
  }

  void Network::learn(std::vector<double> expectedOutput) {
    // row matrix
    output = Matrix<double>({expectedOutput});
    // Error E = 1/2 (expectedOutput - computedOutput)^2
    // Then, we need to calculate the partial derivative of E with respect to Weight and Bias

    // compute gradients
    dEdB[hiddenLayersCount] = hidden[hiddenLayersCount + 1].subtract(output).multiply(hidden[hiddenLayersCount].dot(weight[hiddenLayersCount]).add(bias[hiddenLayersCount]).applyFunction(sigmoidPrime));
    for (int i = hiddenLayersCount - 1; i >= 0; i--) {
      dEdB[i] = dEdB[i+1].dot(weight[i + 1].transpose()).multiply(hidden[i].dot(weight[i]).add(bias[i]).applyFunction(sigmoidPrime));
    }

    for (int i = 0; i < hiddenLayersCount + 1; i++) {
      dEdW[i] = hidden[i].transpose().dot(dEdB[i]);
    }
    // update weights
    for (int i = 0; i < hiddenLayersCount + 1; i++) {
      weight[i] = weight[i].subtract(dEdW[i].multiply(learningRate));
      bias[i] = bias[i].subtract(dEdB[i].multiply(learningRate));
    }
  }

  double Network::stepFunction(double x) {
    if(x > 0.9){
      return 1.0;
    }

    if(x < 0.1){
      return 0.0;
    }

    return x;
  }

  double Network::random(double x) {
    return (double)(rand() % 10000 + 1)/10000-0.5;
  }

  double Network::sigmoid(double x) {
    return 1 / (1 + exp(-x));
  }

  double Network::sigmoidPrime(double x) {
    return exp(-x) / (pow( 1+ exp(-x), 2));
  }
}
