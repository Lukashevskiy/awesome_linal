#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <mdspan>

#include <algorithm>
#include <stdexcept>

template<typename T, size_t Rows, size_t Cols>
class Matrix {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    class RowIterator;
    class ColumnIterator;

    Matrix();
    explicit Matrix(const std::initializer_list<std::initializer_list<T>>& list);

    reference operator()(size_t row, size_t col);
    const_reference operator()(size_t row, size_t col) const;

    constexpr size_t rows() const noexcept;
    constexpr size_t cols() const noexcept;

    RowIterator begin_row(size_t row);
    RowIterator end_row(size_t row);
    ColumnIterator begin_col(size_t col);
    ColumnIterator end_col(size_t col);

private:
    std::vector<value_type> data_;
    std::mdspan<value_type, std::extents<size_t, Rows, Cols>> mdspan_;

    friend class RowIterator;
    friend class ColumnIterator;
};

template<typename T, size_t Rows, size_t Cols>
class Matrix<T, Rows, Cols>::RowIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = typename Matrix::value_type;
    using pointer = typename Matrix::pointer;
    using reference = typename Matrix::reference;

    RowIterator(Matrix& mat, size_t row, size_t col);

    reference operator*() const;
    RowIterator& operator++();
    RowIterator operator++(int);
    bool operator==(const RowIterator& other) const;
    bool operator!=(const RowIterator& other) const;

private:
    Matrix& mat_;
    size_t row_;
    size_t col_;
};

template<typename T, size_t Rows, size_t Cols>
class Matrix<T, Rows, Cols>::ColumnIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = typename Matrix::value_type;
    using pointer = typename Matrix::pointer;
    using reference = typename Matrix::reference;

    ColumnIterator(Matrix& mat, size_t row, size_t col);

    reference operator*() const;
    ColumnIterator& operator++();
    ColumnIterator operator++(int);
    bool operator==(const ColumnIterator& other) const;
    bool operator!=(const ColumnIterator& other) const;

private:
    Matrix& mat_;
    size_t row_;
    size_t col_;
};

#include "matrix.inl"

#endif // MATRIX_HPP