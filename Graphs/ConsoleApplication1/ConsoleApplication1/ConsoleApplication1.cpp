#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

class AutoTestLong {
public:
    static long long int* generateArrayLong(int size) {
        long long int* arr = new long long int[size];
        for (int i = 0; i < size; ++i) {
            long long int high = static_cast<long long int>(rand()) << 32;
            long long int low = static_cast<unsigned int>(rand());
            arr[i] = high | low;

            if (rand() % 2 == 0) {
                arr[i] = -arr[i] - 1;
            }
        }
        return arr;
    }
};

class AutoTestFloat {
public:
    static float* generateArrayFloat(int size) {
        float* arr = new float[size];
        for (int i = 0; i < size; ++i) {
            int sign = (rand() % 2 == 0) ? 1 : -1;
            float mantissa = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
            int exp = (rand() % 256) - 128;
            arr[i] = sign * mantissa * std::pow(2.0f, static_cast<float>(exp));
        }
        return arr;
    }
};

void printLongArray(long long* arr, int size) {
    std::cout << "Generated long long array:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << "\n";
    }
}

void printFloatArray(float* arr, int size) {
    std::cout << "Generated float array:\n";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << "\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int size = 10;

    long long* longArr = AutoTestLong::generateArrayLong(size);
    float* floatArr = AutoTestFloat::generateArrayFloat(size);

    printLongArray(longArr, size);
    std::cout << "\n";
    printFloatArray(floatArr, size);

    // Clean up
    delete[] longArr;
    delete[] floatArr;

    return 0;
}
