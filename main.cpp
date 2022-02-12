#include <iostream>
#include <fstream>

int computeMaximumValueToFitInKnapsack(const int values[], const int sizes[],
                                       const int capacity, const int n) {
    int M = capacity+1;
    int* A = new int[(n+1)*(M)];
    // A[i][j] = A[i*M + j]

    for (int c = 0; c <= capacity; c++) {
        A[c] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int c = 0; c <= capacity; c++) {
            if (sizes[i-1] > c) {
                A[i*M + c] = A[(i - 1)*M + c];
            } else {
                A[i*M + c] = std::max(A[(i - 1) * M + c], A[(i - 1)*M + c - sizes[i-1]] + values[i-1]);
            }
        }
    }

    return A[n*M + capacity];
}

struct Data {
    int capacity;
    int n;
    int* values;
    int* sizes;
};

Data* readData() {
    std::ifstream input("input.txt");

    int n;
    int capacity;

    input >> capacity >> n;

    int* values = new int[n];
    int* sizes = new int[n];


    for (int i = 0; i < n; i++) {
        input >> values[i] >> sizes[i];
    }

    Data* data = new Data;
    data->n = n;
    data->capacity = capacity;
    data->values = values;
    data->sizes = sizes;

    return data;
}

int main() {
    Data* data = readData();

    std::cout << computeMaximumValueToFitInKnapsack(data->values,
                                                    data->sizes, data->capacity, data->n) << std::endl;
    return 0;
}