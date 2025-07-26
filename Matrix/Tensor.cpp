#include<iostream>
#include<vector>
#include<initializer_list>
#include<tuple>
#include<stdexcept>

template<typename T>
class Tensor 
{
private:
    std::vector<size_t> shape;
    std::vector<T> data;

public:
    Tensor(const std::vector<size_t>& shapeInput, const std::vector<T>& dataInput)
        : shape(shapeInput), data(dataInput) {}

    // Tensor<T> is the return type of the function
    Tensor<T> operator+(const Tensor<T>& other) const {
        if (shape != other.shape) {
            throw std::invalid_argument("Shapes do not match for addition.");
        }
        std::vector<T> resultData(data.size());
        for (size_t i = 0; i < data.size(); ++i) {
            resultData[i] = data[i] + other.data[i];
        }
        return Tensor<T>(shape, resultData);
    }

    Tensor<T> operator-(const Tensor<T>& other) const {
        if(shape != other.shape) {
            throw std::invalid_argument("Shapes do not match for subtraction.");
        }
        std::vector<T> resultData(data.size());
        for(size_t i = 0; i < data.size(); ++i) {
            resultData[i] = data[i] - other.data[i];
        }
        return Tensor<T>(shape, resultData);
    }

    void setShape(const std::vector<size_t>& newShape) {
        shape = newShape;
    }

    void setData(const std::vector<T>& newData) {
        data = newData;
    }

    std::vector<size_t> getShape() const {
        return shape;
    }

    std::vector<T> getData() const {
        return data;
    }

    void info() const {
        std::cout << "Shape: (";
        for (size_t i = 0; i < shape.size(); ++i) {
            std::cout << shape[i];
            if (i != shape.size() - 1) std::cout << ", ";
        }
        std::cout << ")\n";

        if (shape.size() == 1) {
            std::cout << "[";
            for (size_t i = 0; i < data.size(); ++i) {
                std::cout << data[i];
                if (i != data.size() - 1) std::cout << ", ";
            }
            std::cout << "]\n";
        } 
        else if (shape.size() == 2) {
            size_t rows = shape[0];
            size_t cols = shape[1];
            for (size_t i = 0; i < rows; ++i) {
                std::cout << "[";
                for (size_t j = 0; j < cols; ++j) {
                    std::cout << data[i * cols + j];
                    if (j != cols - 1) std::cout << ", ";
                }
                std::cout << "]\n";
            }
        } 
        else if (shape.size() == 3) {
            size_t layers = shape[0];
            size_t rows = shape[1];
            size_t cols = shape[2];
            for (size_t l = 0; l < layers; ++l) {
                std::cout << "Layer " << l << ":\n";
                for (size_t r = 0; r < rows; ++r) {
                    std::cout << "[";
                    for (size_t c = 0; c < cols; ++c) {
                        size_t index = l * rows * cols + r * cols + c;
                        std::cout << data[index];
                        if (c != cols - 1) std::cout << ", ";
                    }
                    std::cout << "]\n";
                }
                std::cout << std::endl;
            }
        } 
        else {
            std::cout << "Tensor printing not implemented for " << shape.size() << "D yet.\n";
        }
    }
};

int main() 
{
    std::vector<int> vec1, vec2;
    int val = 0;

    for (int i = 0; i < 9; i++) vec1.push_back(val++);
    for (int i = 0; i < 9; i++) vec2.push_back(val += 2);

    Tensor<int> A({3, 3}, vec1);
    Tensor<int> B({3, 3}, vec2);

    std::cout << "Tensor A:\n";
    A.info();
    std::cout << "\nTensor B:\n";
    B.info();

    Tensor<int> C = A + B;
    std::cout << "\nTensor C (A + B):\n";
    C.info();

    Tensor<int> D = C - B;
    std::cout << "\nTensor D (C - B):\n"
    D.info();

    std::cin.get();
}
