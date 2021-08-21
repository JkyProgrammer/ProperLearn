#include "FeedForwardNeuralNet.h"
#include <math.h>
#include <iostream>

using namespace std;

// TODO: Implement checks on all functions
// TODO: Implement learning
// TODO: Write demo program
// TODO: Write GUI

/**
 * Commit a set of inputs to the neural net.
 * Parameters
 *  float * inputs - array of float inputs to configure the network with. Must be the same length as the first layer.
 * Return
 *  void
 * 
 **/
void FeedForwardNeuralNet::input(float * inputs) {
    for (int i = 0; i < inputData.rows(); i++) {
        inputData(i, 0) = inputs[i];
    }
    lastCalculationIsUpdated = false;
}

/**
 * Calculate the outputs of the first n layers of the network, and return the result as an array of floats. Expects
 * that input (float *) has already been called to configure the input data of the network. Can be passed
 * '-1' as opposed to an integer in order to compute all layers.
 * Parameters
 *  int _nlayers - the number of layers to evaluate from the front of the network.
 * Return
 *  float * - the array of outputs of the last layer of the network
 * 
 **/
float * FeedForwardNeuralNet::compute(int _nlayers) {
    Eigen::Matrix<float, Eigen::Dynamic, 1> result = inputData;
    int layerNum = 0;
    int nlayers = (nlayers==-1) ? layers.size() : _nlayers;
    while (layerNum < nlayers && layerNum < layers.size()) {
        result = (
            (layers[layerNum].weights * result) 
            + layers[layerNum].biases).unaryExpr(
                [](float x){
                    return (0.5f*x)/(1.0f+abs(x)) + 0.5f;
                    });
        layerNum++;
    }
    float * returnvalue = new float[result.rows()];
    for (int i = 0; i < result.rows(); i++) returnvalue[i] = result(i,0);
    lastCalculation = returnvalue;
    lastCalculationIsUpdated = true;
    return returnvalue;
}

/**
 * Calculate the total cost of the network for the current set of inputs, comparing it to a provided (expected)
 * set of outputs. Expects compute (int) has already been called, but if not it will call it itself.
 * Parameters
 *  float * targets - an array of floats which are the expected output, which the computed output will be compared to.
 * Return
 *  float - the total cost for this run of the network
 * 
 **/
float FeedForwardNeuralNet::cost(float * targets) {
    int outputlength = layers[layers.size()-1].count_nodes();
    float returnvalue = 0;
    float * results;
    if (lastCalculationIsUpdated) results = lastCalculation;
    else results = compute (-1);
    for (int i = 0; i < outputlength; i++) {
        returnvalue += powf((results[i]-targets[i]),2);
    }
    return returnvalue;
}

void FeedForwardNeuralNet::initialise(int nlayers, int * nnodes) {
    layers.clear ();
    // First 'layer' is input nodes, which isn't a real layer
    inputs = nnodes[0];
    for (int l = 1; l < nlayers; l++) {
        Layer layer;
        layer.weights.resize (nnodes[l], nnodes[l-1]);
        layer.biases.resize (nnodes[l]);
        layers.push_back (layer);
        randomise (l-1, 0);
    }
    
}

/**
 * Re-initialise a layer of the network with a new set of random weights and biases.
 * Parameters
 *  int layer - the layer index to perform the operation on
 *  long seed - the random seed to give to the C random generator function
 * Return
 *  void
 * 
 **/
void FeedForwardNeuralNet::randomise(int layer, unsigned int seed) {
    srand (seed);
    for (int n = 0; n < layers[layer].count_nodes(); n++) {
        for (int o = 0; o < layers[layer].weights.cols(); o++)
            layers[layer].weights(n, o) = (((float)rand()*2)/(float)RAND_MAX)-1;
        layers[layer].biases (n) = (((float)rand()*2)/(float)RAND_MAX)-1;
    }
}

/**
 * Fetch the input weights from a particular node in a particular layer.
 * Parameters
 *  int layer - the layer index to access
 *  int node - the node index within that layer to access
 * Return
 *  float * - an array of floats containing the set of input weights for the node fetched
 * 
 **/
float * FeedForwardNeuralNet::getWeights(int layer, int node) {
    float * returnvalue = new float[layers[layer].weights.cols()];
    for (int i = 0; i < layers[layer].weights.cols(); i++) returnvalue[i] = layers[layer].weights(node, i);
    return returnvalue;
}

/**
 * Fetch the bias from a particular node in a particular layer.
 * Parameters
 *  int layer - the layer index to access
 *  int node - the node index within that layer to access
 * Return
 *  float - the bias for the node fetched
 * 
 **/
float FeedForwardNeuralNet::getBias(int layer, int node) {
    float returnvalue = layers[layer].biases(node);
    return returnvalue;
}

int FeedForwardNeuralNet::count_layers () { return layers.size() + 1; }
int FeedForwardNeuralNet::count_nodes (int layer) { return layers[layer].count_nodes(); }

FeedForwardNeuralNet::FeedForwardNeuralNet () {}
