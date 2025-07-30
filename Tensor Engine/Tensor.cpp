#include<iostream>
#include<stdexcept>
#include<cstring>

template<typename T>
class Tensor {
    private:
        size_t* shape{};
        size_t* stride{};
        T* data{};

        size_t shape_size{};
        size_t data_size{};

    public:
        Tensor(const size_t* inputShape, size_t shapeLen, const T* dataInput, size_t dataLen)
            : shape_size(shapeLen), data_size(dataLen) {

                shape = (size_t*)malloc(shape_size * sizeof(size_t));
                for (size_t i = 0; i < shape_size; ++i) {
                    shape[i] = inputShape[i];
                }

                data = (T*)malloc(data_shape * sizeof(T));
                for (size_t i = 0; i < data_shape; ++i) {
                    data[i] = dataInput[i];
                }

                stride = nullptr;
                computestride();
            }

        ~Tensor() {
            free(data);
            free(shape);
            free(stride);
        }
    
    void computeStride() {
        if(shape_size == 0 || shape_size == NULL) {
            throw std::invalid_argument("0D tensor or uninitialized tensor");
        }

        stride = (size_t*)realloc(stride, shape_size * sizeof(size_t));
        size_t stride_value = 1;

        for(int i = shape_size - 1; i >= 0; --i) {
            stride[i] = stride_value;
            stride_value *= shape[i];
        }
    }

    void setShape(const size_t* newShape, size_t newShapeLen) {
        free(shape);
        shape_size = newShapeLen;

        shape = (size_t*)malloc(shape_size * sizeof(size_t));
        for (size_t i = 0; i < shape_size; ++i) {
            shape[i] = newShape[i];
        }
        computeStride();
    }

    void setData(const T* newData, size_t newDataLen) {
        free(data);

        data_size = newDataLen;
        data = (T*)malloc(data_size * sizeof(T));
        for (size_t i = 0; i < data_size; ++i) {
            data[i] = newData[i];
        }
    }

    void getShape() const {
        std::cout << "(";
        for(size_t i = 0; i < shape_size; ++i) {
            std::cout << shape[i];
            if(i != shape_size - 1) std::cout << ",";
        }
        std::cout << ")" << std::endl;
    }

    void getData() const {
        std::cout << "[";
        for(size_t i = 0; i < data_size; ++i) {
            std::cout << data[i];
            if(i != data_size - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    void getStride() const {
        std::cout << "(";
        for (size_t i = 0; i < shape_size; ++i) {
            std::cout << stride[i];
            if(i != shape_size - 1) std::cout << ",";
        }
        std::cout << ")" << std::endl;
    }

    T* rawData() const {
        return data;
    }
};