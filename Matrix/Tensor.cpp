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
    std::vector<size_t> stride;
    std::vector<T> data;

    void computeStride() {
        if (shape.empty()) 
            throw std::invalid_argument(") dimensional tensor or uninitialized tensor");

        stride.resize(shape.size());
        size_t str_idx_val = 1;

        for(int i = shape.size() - 1; i >= 0; --i) {
            stride[i] = str_idx_val;
            str_idx_val *= shape[i];
        }
    }

public:
    Tensor(const std::vector<size_t>& shapeInput, const std::vector<T>& dataInput)
        : shape(shapeInput), data(dataInput) {
            computeStride();
        }

        //Setters and getters.

    void setShape(const std::vector<size_t>& newShape) {
        shape = newShape;
        computeStride();
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

    void getStride() const {
        std::cout << "Stride: (";
        for(size_t i = 0; i < stride.size(); ++i) {
            std::cout << stride[i];
            if(i != stride.size() - 1) std::cout << ",";
        }
        std::cout << ")\n";
    }

public:
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

    Tensor<T> operator*(const Tensor<T>& other) const {
        if(shape != other.shape) {
            throw std::invalid_argument("Shapes do not match for matrix multiplication.");
        }
        std::vector<T> resultData(data.size());
        for(size_t i = 0; i < data.size(); ++i) {
            resultData[i] = data[i] * other.data[i];
        }
        return Tensor<T>(shape, resultData);
    }

    Tensor<T> operator/(const Tensor<T>& other) const {
        if(shape != other.shape) {
            throw std::invalid_argument("Shapes do not match for this operation.");
        }
        std::vector<T> resultData(data.size());
        for(size_t i = 0; i < data.size(); ++i) {
            resultData[i] = data[i] / other.data[i];
        }
        return Tensor<T>(shape, resultData);
    }

    // Determinent.
    Tensor<T> getMinor(size_t row, size_t col) const {
        std::vector<T> minorData;
        size_t n = shape[0];

        for (size_t i = 0; i < n; ++i) {
            if(i == row) continue;
            for(size_t j = 0; j < n; ++j) {
                if(j == col) continue;
                minorData.push_back(data[i * n + j]);
            }
        }

        return Tensor<T>({n-1, n-1}, minorData);
    }

    T& det() const {
        int n = shape[0];

        if(shape.size() != 2 || shape[0] != shape[1]) {
            throw std::invalid_argument("Determinant is only defined for 2D tensors.");
        }

        if(n == 1) return data[0];
        if(n == 2) return data[0] * data[3] - data[1] * data[2];

        T dett = 0;
        for(size_t col = 0; col < n; ++col) {
            Tensor<T> minor = getMinor(0, col);
            T sign = (col % 2 == 0) ? 1 : -1;
            dett += sign * data[col] * minor.det();
        }

        return dett;
    }

    Tensor<T> dot(const Tensor<T>& other) const {
        
        size_t rows1 = shape[0];
        size_t cols1 = shape[1];
        size_t rows2 = other.shape[0];
        size_t cols2 = other.shape[1];

        if(cols1 != rows2) {
            throw std::invalid_argument("Shape mismatch.\nCannot perform dot product.");
        }

        std::vector<T> resultData(rows1 * cols2, 0);
        
        // Dot
        for(int i = 0; i < rows1; ++i) {
            for(int j = 0; j < cols2; ++j) {
                for(int k = 0; k < cols1; ++k) {
                    resultData[i * cols2 + j] += data[i * cols1 + k] * other.data[k * cols2 + j];
                }
            }
        }
        return Tensor<T>({rows1, cols2}, resultData);
    }

public:
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
    T& at(size_t i, size_t j) {
        size_t idx = i * stride[0] + j * stride[1];
        std::cout << data[idx] << std::endl;
        return data[idx];
    }

    T& at(size_t i,size_t j, size_t k) {
        size_t idx = i * stride[0] + j * stride[1] + k * stride[2];
        std::cout << data[idx] << std::endl;
        return data[idx];
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
    std::cout << "\nTensor D (C - B):\n";
    D.info();
    D.getStride();

    std::cout << "Dot product of D and A:\n ";
    (D.dot(A)).info();

}
