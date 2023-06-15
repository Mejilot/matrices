#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(default_constructor_test, test1) {
  Matrix arr;

  ASSERT_DOUBLE_EQ(arr.GetRows(), 0);
  ASSERT_DOUBLE_EQ(arr.GetCols(), 0);
}

TEST(parameter_constructor_test, test1) {
  Matrix m1(1, 1), m3(3, 3);

  ASSERT_DOUBLE_EQ(m1.GetRows(), 1);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 1);
  ASSERT_DOUBLE_EQ(m3.GetRows(), 3);
  ASSERT_DOUBLE_EQ(m3.GetCols(), 3);
}

TEST(parameter_constructor_test, test2) {
  EXPECT_THROW(Matrix m2(0, 0), std::invalid_argument);
}

TEST(initializer_list_constructor, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data);
  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(copy_constructor, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data);
  Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.GetRows(), m1.GetRows());
  ASSERT_DOUBLE_EQ(m2.GetCols(), m1.GetCols());

  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(copy_constructor, test2) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data);
  Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.GetRows(), m1.GetRows());
  ASSERT_DOUBLE_EQ(m2.GetCols(), m1.GetCols());

  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(move_constructor, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data);
  Matrix m2(std::move(m1));

  ASSERT_DOUBLE_EQ(m2.GetRows(), 3);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 3);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(destructor, test1) {
  Matrix m1(3, 3);
  m1.~Matrix();
  ASSERT_DOUBLE_EQ(m1.GetRows(), 0);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 0);
}

TEST(EqMatrix, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data), m2(3, 3, data);

  ASSERT_EQ(m1.EqMatrix(m2), 1);
}

TEST(SumMatrix, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::initializer_list<double> data2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data1), m2(3, 3, data2);

  m1.SumMatrix(m2);
  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), 2 * m2(i, j));
}

TEST(SubMatrix, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::initializer_list<double> data2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data1), m2(3, 3, data2);

  m1.SubMatrix(m2);
  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) ASSERT_DOUBLE_EQ(0, m1(i, j));
}

TEST(MulNumber, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data);
  m1.MulNumber(3.);
  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 3.);
}

TEST(MulNumber, test2) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data);
  EXPECT_THROW(m1.MulNumber(NAN), std::invalid_argument);
}

TEST(MulNumber, test3) {
  std::initializer_list<double> data = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data);
  EXPECT_THROW(m1.MulNumber(INFINITY), std::invalid_argument);
}

TEST(MulMatrix, test1) {
  std::initializer_list<double> data = {10, 16, 9, 16};
  std::initializer_list<double> data1 = {1, 2, 3, 4, 1, 2};
  std::initializer_list<double> data2 = {1, 2, 3, 4, 1, 2};
  Matrix m1(2, 3, data1), m2(3, 2, data2);

  m1.MulMatrix(m2);
  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(MulMatrix, test2) {
  std::initializer_list<double> data = {18, 16, 7, 14, 17, 14, 19, 10, 17};
  std::initializer_list<double> data1 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  std::initializer_list<double> data2 = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  Matrix m1(3, 3, data1), m2(3, 3, data2);

  m1.MulMatrix(m2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), m2.GetCols());
  ASSERT_DOUBLE_EQ(m1.GetRows(), 3);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(Transpose, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  std::initializer_list<double> data = {1, 3, 2, 4};
  Matrix m1(2, 2, data1), m2;

  m2 = m1.Transpose();

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(CalcComplements, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  std::initializer_list<double> data = {4, -3, -2, 1};
  Matrix m1(2, 2, data1), m2;

  m2 = m1.CalcComplements();
  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(InverseMatrix, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  std::initializer_list<double> data = {-2, 1, 1.5, -0.5};
  Matrix m1(2, 2, data1), m2;

  m2 = m1.InverseMatrix();
  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(Determinant, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  Matrix m1(2, 2, data1), m2;

  ASSERT_DOUBLE_EQ(m1.Determinant(), -2);
}

TEST(CopyOperator, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = m1;

  ASSERT_DOUBLE_EQ(m2.GetRows(), m1.GetRows());
  ASSERT_DOUBLE_EQ(m2.GetCols(), m1.GetCols());

  for (int i = 0; i < m2.GetRows(); i++)
    for (int j = 0; j < m2.GetCols(); j++) ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}

TEST(MoveOperator, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = std::move(m1);

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);
  ASSERT_DOUBLE_EQ(m1.GetRows(), 0);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 0);
  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(plusequalop, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data);
  m1 += m1;

  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 2);
}

TEST(minequalop, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data);
  m1 -= m1;

  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), 0);
}

TEST(mulequalop, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  std::initializer_list<double> data = {7, 10, 15, 22};
  Matrix m1(2, 2, data1);
  m1 *= m1;

  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k);
}

TEST(mulequalop, test2) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data);
  m1 *= 2;

  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m1.GetCols() ? (i + 1) : i,
            j = (j + 1) == m1.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m1(i, j), *k * 2);
}

TEST(isequalop, test3) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  Matrix m1(2, 2, data1), m2(2, 2, data1);

  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);
  ASSERT_EQ(m1 == m2, 1);
}

TEST(plusop, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = m1 + m1;

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k * 2);
}

TEST(minop, test1) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = m1 - m1;

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), 0);
}

TEST(mulop, test1) {
  std::initializer_list<double> data1 = {1, 2, 3, 4};
  std::initializer_list<double> data = {7, 10, 15, 22};
  Matrix m1(2, 2, data1), m2;
  m2 = m1 * m1;

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k);
}

TEST(mulop, test2) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = m1 * 3;

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k * 3);
}

TEST(mulop, test3) {
  std::initializer_list<double> data = {1, 2, 3, 4};
  Matrix m1(2, 2, data), m2;
  m2 = 3 * m1;

  ASSERT_DOUBLE_EQ(m2.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 2);

  int i = 0, j = 0;
  for (auto k = data.begin(); k != data.end(); k++,
            i = (j + 1) == m2.GetCols() ? (i + 1) : i,
            j = (j + 1) == m2.GetCols() ? 0 : (j + 1))
    ASSERT_DOUBLE_EQ(m2(i, j), *k * 3);
}

TEST(Getters, test1) {
  Matrix m1(2, 2), m2(3, 1);

  ASSERT_DOUBLE_EQ(m2.GetRows(), 3);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 1);
  ASSERT_DOUBLE_EQ(m1.GetRows(), 2);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 2);
}

TEST(Setters, test1) {
  Matrix m1(1, 1), m2(1, 1);
  m1.SetCols(3);
  ASSERT_DOUBLE_EQ(m1.GetRows(), 1);
  ASSERT_DOUBLE_EQ(m1.GetCols(), 3);
  m2.SetRows(4);
  m2.SetCols(4);
  ASSERT_DOUBLE_EQ(m2.GetRows(), 4);
  ASSERT_DOUBLE_EQ(m2.GetCols(), 4);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}