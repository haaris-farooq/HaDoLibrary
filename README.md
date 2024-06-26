# A library for implementing Neural Networks in C++
Lightweight, templated, highly vectorised, and optimised library for a variety of neural networks.

Supports models for:
 - Deep Neural Networks

Will support soon:
 - Convolutional Neural Networks
 - RNN Networks
 - LSTM Networks
 - Transformer Networks

Example usages are stored in src folder to run. See "XorModel.cpp", for example. 

Looking to properly integrate unit testing functionality for smoother scalability in future.

# Usage
You'll need the Eigen library inside of your project, as well as everything in the HaDo/ subdirectory. See the Makefile for a general idea of how to compile it all. Use "-fopenmp" for compilation with multithreading enabled, if you have OpenMP installed on your system. The MakeFile provided gives an example using 'make omp' as a target.

You could have for an example file structure:

```
project  
|   MakeFile
|   
├───src
|   |   main.cpp
|
├───Eigen
|   ...
|
├───HaDo
|   ...
|
└───res.png
```

Notably, you should include the Eigen and Hado files in your include flags when compiling.

To use in your main program, simply import the desired module set available in the top level of the HaDo folder, for example:

```cpp
#include <HaDo/ConvolutionalNeuralNetwork>

void TwoCategoryMNIST(){
    hado::Pipeline<double> pipeline;

    pipeline.pushLayer(
        hado::ConvolutionalLayer<double, hado::relu<double>, hado::relu_prime<double>>(1, 2, 28, 28, 3, 1, 0)
    );

    pipeline.pushLayer(
        hado::MaxPoolLayer<double>(2, 26, 26, 2, 2, 0)
    );

    ...
}
```


# TODO
  - [X] Image -> Bitmap formatting ??? Maybe use PPM for raw RGB
  - [x] Dense Layers
  - [x] Activation Layers (tanh, sigmoid, ReLU, softmax so far)
  - [X] Mean Squared Error implementation
  - [X] Cross-Entropy Loss implementation
  - [X] Method to pass through and verify layer setup
  - [X] Pipeline class
  - [ ] Convolutional Layers
  - [X] Pooling Layers
  - [ ] Saving a model (JSON or binary?)
  - [ ] Getting it running on a GPU
  - [ ] Getting it running on a cluster
