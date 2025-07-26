#include<iostream>
#include<vector>
#include<initializer_list>

// size_t is used instead of int so that the input shape of the tensor is never a negative.
// size_t only has a positive value.(size_t is a data type).

// <T> stores the actual tensor values
template<typename T>
class Tensor 
{
    private:
        std::vector<size_t> shape; //dim
        std::vector<T> data;
    
    public:
        Tensor(std::vector<size_t> shapeInput, std::vector<T> dataInput) : shape(shapeInput), data(dataInput) {}

        void setShape(const std::vector<size_t>& newShape) {
            shape = newShape;
        }

        void setData(const std::vector<T>& newData) {
            data = newData;
        }

        std::vector<size_t> getShape() const {return shape;}
        std::vector<T> getData() const {return data;}

        void print() const {
            std::cout << "Shape: ";
            for(int i : shape) std::cout << i << " ";

            std::cout << "\nData: ";
            if(shape.size() == 2) {
                size_t rows = shape[0];
                size_t cols = shape[1];
                for(int i = 0; i < data.size(); i++) {
                    std::cout << data[i] << " ";
                    if((i + 1) % cols == 0) std::cout << std::endl;
                }

            } else if(shape.size() == 3){
                size_t layers = shape[0];
                size_t rows = shape[1];
                size_t cols = shape[2];
                for(int i = 0; i < data.size(); i++) {
                    if((i + 1) % cols == 0) std::cout << std::endl;
                    std::cout << data[i] << " ";
            }

        } else {
            for(const auto& i : data) std::cout << i << " ";
        }
    }
};

int main() 
{
    std::vector<int> vec;
    int val = 0;
    for(int i = 0; i < 9; i++) {
        vec[i] = val++;
    }
    Tensor<int> tensor2D({3, 3}, vec)

    tensor2D.print();

}