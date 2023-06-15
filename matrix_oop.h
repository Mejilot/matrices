#ifndef CPP1__MATRIXPLUS_0__MATRIX_OOP_H
#define CPP1__MATRIXPLUS_0__MATRIX_OOP_H
#include <math.h>

#include <iostream>
#define EPS 1E-7

class Matrix {
 public:
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  Matrix(int rows, int cols, std::initializer_list<double>& m);
  ~Matrix();

  bool EqMatrix(const Matrix& other) const;
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose() const;
  Matrix CalcComplements() const;
  double Determinant() const;
  Matrix InverseMatrix() const;

  Matrix& operator=(const Matrix& other);
  Matrix& operator=(Matrix&& other);
  double& operator()(int row, int col) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);
  Matrix& operator*=(const double other);
  bool operator==(const Matrix& A) const;
  Matrix operator+(const Matrix& A) const;
  Matrix operator-(const Matrix& A) const;
  Matrix operator*(const Matrix& A) const;
  friend Matrix operator*(const Matrix& A, const double B);
  friend Matrix operator*(const double B, const Matrix& A);
  friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
  int GetCols() const;
  int GetRows() const;
  void SetCols(int x);
  void SetRows(int x);

 private:
  void CopyMatrixVals(const Matrix& other);
  void CreateMatrix();
  double CalcMinor(const int x, const int y) const;
  double** matrix_{nullptr};
  int rows_{}, cols_{};
};

#endif  // CPP1__MATRIXPLUS_0__MATRIX_OOP_H
