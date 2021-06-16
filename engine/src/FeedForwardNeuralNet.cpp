#include "FeedForwardNeuralNet.h"


void FeedForwardNeuralNet::input(float * inputs) {
    for (int i = 0; i < inputData.rows(); i++) {
        inputData(i, 0) = inputs[i];
    }
}

float * FeedForwardNeuralNet::compute(int layers) {
    
}

float FeedForwardNeuralNet::cost(float * targets) {
    
}

void FeedForwardNeuralNet::initialise(int nlayers, int * nnodes) {
    
}

void FeedForwardNeuralNet::randomise(int layer) {
    
}

float * FeedForwardNeuralNet::getWeights(int layer, int node) {
    
}

float FeedForwardNeuralNet::getBias(int layer, int node) {
    
}
