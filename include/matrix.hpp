#include "tuple.hpp"
#include <array>
#include <concepts>
#include <cstddef>
#include <format>
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

    constexpr std::size_t size() const {
        return Rows * Cols;
    }

    constexpr int rows() const {
        return Rows;
    }

    constexpr int cols() const {
        return Cols;
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

    Matrix<T, Rows, Cols> identity() {
        if (Rows != Cols) {
             throw std::domain_error(
                std::format("identity can only be called on nxn matrices."
                            "The dimensions here are {} {}", Rows, Cols));
        }
        Matrix<T, Rows, Cols> _identity;
        for (int i = 0; i < Rows; ++i) {
            _identity[i][i] = 1;
        }
        return _identity;
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

    // This ensures that the number of columns in the first matrix is equal to the number of rows in the second matrix
    // and the number of columns in the second matrix can be different but can be known at compile time
    template<int N>
    Matrix<T, Rows, N> operator*(const Matrix<T, Cols, N>& rhs) {
        Matrix<T, Rows, N> m;

        for(int i {0}; i < Rows; ++i) {
            for(int j {0}; j < N; ++j) {
                for(int k {0}; k < Cols; ++k) {
                    m[i][j] += _data[i][k]* rhs[k][j];
                }
            }
        } 
        return m;
    }
    
    Tuple operator*(const Tuple& t) {
        if(Cols != 4) {
            throw std::invalid_argument("error: matrix must have 4 columns to multiply with the 4 element tuple");
        }
        return Tuple(_data[0][0]*t.x() + _data[0][1]*t.y() + _data[0][2]*t.z() + _data[0][3]*t.w(),
                     _data[1][0]*t.x() + _data[1][1]*t.y() + _data[1][2]*t.z() + _data[1][3]*t.w(),
                     _data[2][0]*t.x() + _data[2][1]*t.y() + _data[2][2]*t.z() + _data[2][3]*t.w(),
                     _data[3][0]*t.x() + _data[3][1]*t.y() + _data[3][2]*t.z() + _data[3][3]*t.w());
    }
};

