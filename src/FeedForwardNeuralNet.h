#ifndef FFNN_h
#define FFNN_h

#include "../deps/eigen-3.3.9/Eigen/Core"
#include <vector>

class Layer {
public:
    Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> weights;
    Eigen::Matrix<float, Eigen::Dynamic, 1> biases;
    inline int count_nodes () {return biases.rows();}
};

class FeedForwardNeuralNet {
private:
    Eigen::Matrix<float, Eigen::Dynamic, 1> inputData;
    std::vector<Layer> layers;
    bool lastCalculationIsUpdated = false;

    int inputs;
public:
    void input (float *);
    float * compute (int);
    float cost (float *);

    void initialise (int, int *);
    void randomise (int, unsigned int);

    float * getWeights (int, int);
    float getBias (int, int);

    float * lastCalculation;

    int count_layers ();
    int count_nodes (int);
    inline int count_inputs () { return inputs; }

    FeedForwardNeuralNet ();
};

#endif