#include <iostream>

class DoubleSubscriptedArray {
    friend std::ostream &operator<<(std::ostream &, const DoubleSubscriptedArray &);
    friend std::istream &operator>>(std::istream &, DoubleSubscriptedArray &);

public:
    explicit DoubleSubscriptedArray(int rows = 1, int columns = 1) : rows(rows), columns(columns) {
        arrayPtr = new int[rows * columns]();
    }

    DoubleSubscriptedArray(const DoubleSubscriptedArray &other) : rows(other.rows), columns(other.columns) {
        arrayPtr = new int[rows * columns];
        for (int i = 0; i < rows * columns; ++i) {
            arrayPtr[i] = other.arrayPtr[i];
        }
    }

    ~DoubleSubscriptedArray() {
        delete[] arrayPtr;
    }

    int &operator()(int row, int column) {
        return arrayPtr[row * columns + column];
    }

    int operator()(int row, int column) const {
        return arrayPtr[row * columns + column];
    }

    const DoubleSubscriptedArray &operator=(const DoubleSubscriptedArray &other) {
        if (this != &other) {
            if (rows * columns != other.rows * other.columns) {
                delete[] arrayPtr;
                rows = other.rows;
                columns = other.columns;
                arrayPtr = new int[rows * columns];
            }
            for (int i = 0; i < rows * columns; ++i) {
                arrayPtr[i] = other.arrayPtr[i];
            }
        }
        return *this;
    }

    bool operator==(const DoubleSubscriptedArray &other) const {
        if (rows != other.rows || columns != other.columns) {
            return false;
        }
        for (int i = 0; i < rows * columns; ++i) {
            if (arrayPtr[i] != other.arrayPtr[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DoubleSubscriptedArray &other) const {
        return !(*this == other);
    }

private:
    int rows;
    int columns;
    int *arrayPtr;
};

std::ostream &operator<<(std::ostream &output, const DoubleSubscriptedArray &array) {
    for (int i = 0; i < array.rows; ++i) {
        for (int j = 0; j < array.columns; ++j) {
            output << array.arrayPtr[i * array.columns + j] << ' ';
        }
        output << std::endl;
    }
    return output;
}

std::istream &operator>>(std::istream &input, DoubleSubscriptedArray &array) {
    for (int i = 0; i < array.rows; ++i) {
        for (int j = 0; j < array.columns; ++j) {
            input >> array.arrayPtr[i * array.columns + j];
        }
    }
    return input;
}

int main() {
    // Create a DoubleSubscriptedArray object
    DoubleSubscriptedArray array(2, 3);

    // Assign values to the array elements
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            array(i, j) = i * 3 + j;
        }
    }

    // Output the array
    std::cout << "Array elements:" << std::endl;
    std::cout << array;

    return 0;
}