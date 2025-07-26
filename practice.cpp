#include<iostream>
#include<vector>
int one() {
    std::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.pop_back();

    for(int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << std::endl;

    for(int i : vec) {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2(5, 100);

    for(int i : vec1) {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    for(int i : vec2) {
        std::cout << i << " ";
    }

    std::vector<std::vector<int>> matrix(3, std::vector<int>(3, 0));
}

int matrix(int rows, int cols) {

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0)); 
    //You're creating a matrix with 'rows' number of rows, and each row has 'cols' number of integers, all set to 0.

    int val = 1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            matrix[i][j] = val++;
        }
    }

    std::cout << "Matrix:" << std::endl;
    for(const std::vector<int>& row : matrix) { //With &, we are accessing the row directly. This is faster and more memory efficient.
        // const make sures the values arent altered.
        for(int x : row) {
            std::cout << x << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}

int main() {
    matrix(3, 3);
    return 0;
}