#include "../../deps/eigen-3.3.9/Eigen/Core"
#include <vector>

using namespace Eigen;
using namespace std;

class Layer {
public:
    Matrix<float, Dynamic, Dynamic> weights;
    Matrix<float, Dynamic, 1> biases;
};

class FeedForwardNeuralNet {
private:
    Matrix<float, Dynamic, 1> inputData;
    vector<Layer> layers;
public:
    void input (float *);
    float * compute (int);
    float cost (float *);

    void initialise (int, int *);
    void randomise (int);

    float * getWeights (int, int);
    float getBias (int, int);
};