
template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::Matrix()
    : data_(Rows * Cols), mdspan_(data_.data(), Rows, Cols) {}

template<typename T, size_t Rows, size_t Cols>
Matrix<T, Rows, Cols>::Matrix(const std::initializer_list<std::initializer_list<T>>& list)
{
    if (list.size() != Rows || std::any_of(list.begin(), list.end(),
        [](const auto& innerList) { return innerList.size() != Cols; }))
    {
        throw std::invalid_argument("Invalid initializer list for matrix");
    }

    size_t i = 0;
    for (const auto& row : list) {
        std::copy(row.begin(), row.end(), data_.begin() + i * Cols);
        ++i;
    }
}

template<typename T, size_t Rows, size_t Cols>
typename Matrix<T, Rows, Cols>::reference
Matrix<T, Rows, Cols>::operator()(size_t row, size_t col)
{
    return mdspan_(row, col);
}

template<typename T, size_t Rows, size_t Cols>
typename Matrix<T, Rows, Cols>::const_reference
Matrix<T, Rows, Cols>::operator()(size_t row, size_t col) const
{
    return mdspan_(row, col);
}

template<typename T, size_t Rows, size_t Cols>
constexpr size_t Matrix<T, Rows, Cols>::rows() const noexcept
{
    return Rows;
}

template<typename T, size_t Rows, size_t Cols>
constexpr size_t Matrix<T, Rows, Cols>::cols() const noexcept
{
    return Cols;
}

template<typename T, size_t Rows, size_t Cols>
auto Matrix<T, Rows, Cols>::begin_row(size_t row)
{
    return RowIterator(*this, row, 0);
}

template<typename T, size_t Rows, size_t Cols>
auto Matrix<T, Rows, Cols>::end_row(size_t row)
{
    return RowIterator(*this, row, Cols);
}

template<typename T, size_t Rows, size_t Cols>
auto Matrix<T, Rows, Cols>::begin_col(size_t col)
{
    return ColumnIterator(*this, 0, col);
}

template<typename T, size_t Rows, size_t Cols>
auto Matrix<T, Rows, Cols>::end_col(size_t col)
{
    return ColumnIterator(*this, Rows, col);
}