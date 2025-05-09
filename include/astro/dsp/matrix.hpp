#pragma once

#include <cstddef>
#include <cstdint>

#include <array>

namespace astro::dsp {
   /**
    * @brief A class representing a matrix of floating-point numbers.
    * 
    * @tparam T The type of the elements in the matrix (e.g., float, double).
    */
    template <typename T, std::size_t Rows, std::size_t Cols>
    class matrix {
        public:
            using value_type = T;

            // Constructors, destructors, and assignment operators
            matrix() = default;
            matrix(const matrix& other) = default;
            matrix(matrix&& other) noexcept = default;
            matrix& operator=(const matrix& other) = default;
            matrix& operator=(matrix&& other) noexcept = default;

            value_type& operator()(std::size_t row, std::size_t col) { return _data[row * Cols + col]; }
            const value_type& operator()(std::size_t row, std::size_t col) const { return _data[row * Cols + col]; }

            std::size_t rows() const noexcept { return Rows; }
            std::size_t cols() const noexcept { return Cols; }
            std::size_t size() const noexcept { return Rows * Cols; }

            // Arithmetic operations
            matrix operator+(const matrix& other) const {
                matrix result;
                for (std::size_t i = 0; i < size(); ++i) {
                    result._data[i] = _data[i] + other._data[i];
                }
                return result;
            }
            matrix operator-(const matrix& other) const {
                matrix result;
                for (std::size_t i = 0; i < size(); ++i) {
                    result._data[i] = _data[i] - other._data[i];
                }
                return result;
            }
            matrix operator*(const matrix& other) const {
                matrix result;
                for (std::size_t i = 0; i < Rows; ++i) {
                    for (std::size_t j = 0; j < Cols; ++j) {
                        result(i, j) = 0;
                        for (std::size_t k = 0; k < Cols; ++k) {
                            result(i, j) += (*this)(i, k) * other(k, j);
                        }
                    }
                }
                return result;
            }
            matrix operator*(value_type scalar) const {
                matrix result;
                for (std::size_t i = 0; i < size(); ++i) {
                    result._data[i] = _data[i] * scalar;
                }
                return result;
            }

            // Comparison operators
            bool operator==(const matrix& other) const;
            bool operator!=(const matrix& other) const;

            // Other member functions
            void fill(value_type value);
            void transpose();
            void print() const;

        private:
            std::array<value_type, Rows * Cols> _data; ///< The underlying data storage for the matrix.
   };
} // namespace astro::dsp