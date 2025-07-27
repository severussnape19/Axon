#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Example shape: 2 blocks, 3 rows, 4 columns
    vector<int> shape = {2, 3, 4};
    int size = shape[0] * shape[1] * shape[2];

    // Flattened data: size = 2 * 3 * 4 = 24
    vector<int> data(size);
    for (int i = 0; i < 24; ++i) {
        data[i] = i + 1;  // Fill with 1..24
    }

    
}