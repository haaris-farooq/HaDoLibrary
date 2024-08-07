#ifndef LAYER_HPP
#define LAYER_HPP

#define _MAX_DEPTH_UNTIL_THREADING 1
#define _MAX_PROD_UNTIL_THREADING 2000

#include <Eigen/Dense>
#include <vector>
#include <memory>
#include <iostream>
#include <json/json.hpp>

using Eigen::Dynamic;
using Eigen::Matrix;
using nlohmann::json;
using std::cout;
using std::vector;
using std::endl;

namespace hado {

/**
 * @brief Base layer class. T will only work for float, double,
 * or long double. Can't construct this directly, must derive a
 * child class to use.
 *
 * @tparam T Data type (float for speed, double accuracy) (optional)
 */
template <typename T = float>
class Layer
{
private:
    // Layer dimensions
    int I, O, RI, CI, RO, CO;

    // Assert that T is either float, double, or long double at compiler time
    static_assert(
        std::is_same_v<T, float>
        || std::is_same_v<T, double>
        || std::is_same_v<T, long double>,
        "T must be either float, double, or long double."
    );

protected:

    // Convenience typedef
    typedef Matrix<T, Dynamic, Dynamic> MatrixD;

    /**
     * @brief Layer constructor to instantiate input and output vectors
     *
     * @param I Depth of input tensor
     * @param O Depth of output tensor
     * @param RI Rows in input tensor
     * @param CI Columns in input tensor
     * @param RO Rows in output tensor
     * @param CO Columns in output tensor
     */
    Layer(int I, int O, int RI, int CI, int RO, int CO) : inp(I), out(O)
    {
        // Assert positivity of dimensions
        assert(I > 0 && "Input tensor depth must be positive and nonzero.");
        assert(O > 0 && "Output tensor depth must be positive and nonzero.");
        assert(RI > 0 && "Input tensor rows must be positive and nonzero.");
        assert(CI > 0 && "Input tensor columns must be positive and nonzero.");
        assert(RO > 0 && "Output tensor rows must be positive and nonzero.");
        assert(CO > 0 && "Output tensor columns must be positive and nonzero.");

        this->I = I;
        this->O = O;
        this->RI = RI;
        this->CI = CI;
        this->RO = RO;
        this->CO = CO;
    }

    // Copy constructor
    Layer(const Layer &other) : inp(other.inp), out(other.out)
    {
        I = other.getInputDepth();
        O = other.getOutputDepth();
        RI = other.getInputRows();
        CI = other.getInputCols();
        RO = other.getOutputRows();
        CO = other.getOutputCols();
    }

public:
    // Input tensor
    vector<MatrixD> inp;

    // Output tensor
    vector<MatrixD> out;

    // Virtual clone
    virtual std::unique_ptr<Layer<T>> clone() const = 0;

    // Virtual Destructor
    virtual ~Layer() {}

    // Assert input tensor dimensions
    void constexpr assertInputDimensions(const vector<MatrixD> &input_tensor) const {
        if (input_tensor.size() != static_cast<size_t>(this->I)
            || input_tensor[0].rows() != this->RI
            || input_tensor[0].cols() != this->CI){
            std::cerr << "Expected depth " << this->I << " but got depth " << input_tensor.size() << endl;
            std::cerr << "Expected rows " << this->RI << " but got rows " << input_tensor[0].rows() << endl;
            std::cerr << "Expected cols " << this->CI << " but got cols " << input_tensor[0].cols() << endl;
            throw std::invalid_argument("Input tensor match dimensions of layer.");
        }
    }

    // Assert output tensor dimensions
    void constexpr assertOutputDimensions(const vector<MatrixD> &output_tensor) const {
        if (output_tensor.size() != static_cast<size_t>(this->O)
            || output_tensor[0].rows() != this->RO
            || output_tensor[0].cols() != this->CO){
            std::cerr << "Expected depth " << this->O << " but got depth " << output_tensor.size() << endl;
            std::cerr << "Expected rows " << this->RO << " but got rows " << output_tensor[0].rows() << endl;
            std::cerr << "Expected cols " << this->CO << " but got cols " << output_tensor[0].cols() << endl;
            throw std::invalid_argument("Output tensor match dimensions of layer.");
        }
    }

    // Trivial getters
    constexpr int getInputDepth() const { return I; }
    constexpr int getOutputDepth() const { return O; }
    constexpr int getInputRows() const { return RI; }
    constexpr int getInputCols() const { return CI; }
    constexpr int getOutputRows() const { return RO; }
    constexpr int getOutputCols() const { return CO; }

    // Forward propagation
    virtual vector<MatrixD> forward(
        vector<MatrixD> &input_tensor) = 0;

    // Backward propagation
    virtual vector<MatrixD> backward(
        vector<MatrixD> &output_gradient, const T learning_rate) = 0;
};

}
#endif // LAYER_HPP

