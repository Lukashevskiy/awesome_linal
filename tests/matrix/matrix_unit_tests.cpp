#include "matrix.hpp"

using namespace std;

TEST(MatrixTest, DefaultConstructor) {
    Matrix<int, 3, 3> m;
    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.cols(), 3);
    EXPECT_EQ(m.data().size(), 9);
}

TEST(MatrixTest, InitializerListConstructor) {
    Matrix<int, 3, 3> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(1, 1), 5);
    EXPECT_EQ(m(2, 2), 9);
}

TEST(MatrixTest, InvalidInitializerListThrowsException) {
    EXPECT_THROW({
        Matrix<int, 3, 3> m({{1, 2}, {4, 5, 6}, {7, 8, 9}});
    }, std::invalid_argument);
}

TEST(MatrixTest, RowIterator) {
    Matrix<int, 3, 3> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    int expected[] = {1, 2, 3};
    int index = 0;
    for (auto it = m.begin_row(0); it != m.end_row(0); ++it) {
        EXPECT_EQ(*it, expected[index]);
        ++index;
    }
}

TEST(MatrixTest, ColumnIterator) {
    Matrix<int, 3, 3> m({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    int expected[] = {2, 5, 8};
    int index = 0;
    for (auto it = m.begin_col(1); it != m.end_col(1); ++it) {
        EXPECT_EQ(*it, expected[index]);
        ++index;
    }
}
