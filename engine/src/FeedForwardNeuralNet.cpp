#include "FeedForwardNeuralNet.h"
#include <math.h>


void FeedForwardNeuralNet::input(float * inputs) {
    for (int i = 0; i < inputData.rows(); i++) {
        inputData(i, 0) = inputs[i];
    }
}

float * FeedForwardNeuralNet::compute(int _nlayers) {
    Matrix<float, Dynamic, 1> result = inputData;
    int layerNum = 0;
    int nlayers = (nlayers==-1) ? layers.size() : _nlayers;
    while (layerNum < nlayers && layerNum < layers.size()) {
        result = ((layers[layerNum].weights * result) + layers[layerNum].biases).unaryExpr([](float x){return (0.5*x)/(1+abs(x)) + 0.5;});
        layerNum++;
    }
    float * returnvalue = new float[result.rows()];
    for (int i = 0; i < result.rows(); i++) returnvalue[i] = result(i,0);
    return returnvalue;
}

float FeedForwardNeuralNet::cost(float * targets) {
    int outputlength = layers[layers.size()-1].biases.rows();
    float returnvalue = 0;
    float * results = compute (-1);
    for (int i = 0; i < outputlength; i++) {
        returnvalue += powf((results[i]-targets[i]),2);
    }
    return returnvalue;
}

void FeedForwardNeuralNet::initialise(int nlayers, int * nnodes) {
    
}

void FeedForwardNeuralNet::randomise(int layer) {
    
}

float * FeedForwardNeuralNet::getWeights(int layer, int node) {
    
}

float FeedForwardNeuralNet::getBias(int layer, int node) {
    
}
