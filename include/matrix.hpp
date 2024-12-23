#include <array>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T>
concept numeric = std::integral<T> or std::floating_point<T>;

template<numeric T, int Rows, int Cols>
class Matrix {
private:
    std::array<std::array<T, Cols>, Rows> _data;
public:
    Matrix() {
        // zero all the values
        for (std::array<T, Cols>& row: _data) {
           row.fill(T());
        }
    }

    Matrix& operator=(std::initializer_list<T> values) {
        if(values.size() > Rows * Cols) {
            throw std::invalid_argument("error: number of values does not match matrix size.");
        }

        auto val = values.begin();
        for(int i = 0; i < Rows; ++i) {
            for(int j = 0; j < Cols; ++j) {
                _data[i][j] = *val++;
            }
        }
        return *this;
    }

    std::size_t size() {

    }

    const std::array<T, Cols> operator[](int row) const {
        if (row < 0 || row >= Rows) {
            throw std::out_of_range("index out of bounds");
        }
        return _data[row];
    }
    
    std::array<T, Cols>& operator[](int row) {
        if (row < 0 || row >= Rows) {
            throw std::out_of_range("index out of bounds");
        }
        return _data[row];
    }
    
    void print() const {
        for(const auto& row : _data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
    }

    bool operator==(const Matrix& rhs) const {
        for(int i = 0; i < Rows; ++i) {
            for(int j = 0; j < Cols; ++j) {
                if(_data[i][j] != rhs[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator !=(const Matrix& rhs) const {
        for(int i = 0; i < Rows; ++i) {
            for(int j = 0; j < Cols; ++j) {
                if(_data[i][j] != rhs[i][j]) {
                    return true;
                } 
            }
        }
        return false;
    }
};

