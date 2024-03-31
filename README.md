# A library for implementing Neural Networks in C++
Lightweight, templated, highly vectorised, and optimised library for a variety of neural networks. To use, all you need are the header files - import the neural network *.hpp file of your choice (i.e. "DeepNeuralNetwork.hpp") to get access to the relevant templates for use.

Since GPU support isn't yet available, we utilise multithreading instead.

Supports models for:
 - Deep Neural Networks

Will support soon:
 - Convolutional Neural Networks
 - LSTM Networks

Example usages are stored in src folder to run. See "XorModel.cpp", for example. 

# Usage
You'll need the Eigen library inside of your project, as well as everything in the include/ subdirectory. See the Makefile for a general idea of how to compile it all.

# TODO
  - [X] Image -> Bitmap formatting ??? Maybe use PPM for raw RGB
  - [x] Dense Layers
  - [x] Activation Layers (tanh, sigmoid, ReLu so far)
  - [X] Mean Squared Error implementation
  - [X] Method to pass through and verify layer setup
  - [X] Pipeline class
  - [ ] Convolutional Layers
  - [ ] Pooling Layers
  - [ ] Saving a model (JSON or binary?)
  - [ ] Getting it running on a GPU
  - [ ] Getting it running on a cluster
