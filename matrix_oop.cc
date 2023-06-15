#include "matrix_oop.h"

void Matrix::CreateMatrix() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

void Matrix::CopyMatrixVals(const Matrix& other) {
  for (int i = 0; i < std::min(other.rows_, rows_); i++)
    for (int j = 0; j < std::min(other.cols_, cols_); j++)
      matrix_[i][j] = other.matrix_[i][j];
}

Matrix::Matrix() {}

Matrix::Matrix(int rows, int cols) : cols_(cols), rows_(rows) {
  if (rows <= 0 || cols <= 0)
    throw std::invalid_argument("Matrix dimensions aren't positive!");
  CreateMatrix();
}

Matrix::Matrix(int rows, int cols, std::initializer_list<double>& m)
    : cols_(cols), rows_(rows) {
  if (rows * cols != (m.size()))
    throw std::invalid_argument("Incorrect sizes, or initializer list");
  CreateMatrix();
  int i = 0, j = 0;
  for (auto k = m.begin(); k != m.end(); k++,
            i = (j + 1) == GetCols() ? (i + 1) : i,
            j = (j + 1) == GetCols() ? 0 : (j + 1)) {
    matrix_[i][j] = *k;
  }
}

Matrix::Matrix(const Matrix& other) { *this = other; }

Matrix::Matrix(Matrix&& other) { *this = std::move(other); }

Matrix::~Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;
    cols_ = 0;
    rows_ = 0;
    matrix_ = nullptr;
  }
}

bool Matrix::EqMatrix(const Matrix& other) const {
  if (other.cols_ != cols_ || other.rows_ != rows_) return false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) return false;
  return true;
}

void Matrix::SumMatrix(const Matrix& other) {
  if (other.cols_ != cols_ || other.rows_ != rows_)
    throw std::invalid_argument("Matrix dimensions aren't equal!");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void Matrix::SubMatrix(const Matrix& other) {
  if (other.cols_ != cols_ || other.rows_ != rows_)
    throw std::invalid_argument("Matrix dimensions aren't equal!");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void Matrix::MulNumber(const double num) {
  if (isnan(num) || isinf(num))
    throw std::invalid_argument("Invalid number, inf or nan!");
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void Matrix::MulMatrix(const Matrix& other) {
  if (cols_ != other.rows_)
    throw std::invalid_argument(
        "First matrix columns number isn't equal to second matrix rows number, "
        "mathematically incorrect!");
  Matrix other_trans(other.Transpose());
  Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < other_trans.rows_; j++)
      for (int k = 0; k < other_trans.cols_; k++)
        result.matrix_[i][j] += matrix_[i][k] * other_trans.matrix_[j][k];
  *this = std::move(result);
}

Matrix Matrix::Transpose() const {
  Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) result.matrix_[j][i] = matrix_[i][j];
  return result;
}

double Matrix::CalcMinor(const int x, const int y) const {
  if (cols_ == 1) return matrix_[0][0];
  Matrix temp(rows_ - 1, cols_ - 1);
  for (int i = 0, k = 0; i < rows_; i++) {
    for (int j = 0, n = 0; j < cols_; j++) {
      if (i == x || j == y) continue;
      temp.matrix_[k][n] = matrix_[i][j];
      n++;
    }
    if (i == x) continue;
    k++;
  }
  return temp.Determinant();
}

Matrix Matrix::CalcComplements() const {
  if (cols_ != rows_)
    throw std::invalid_argument(
        "Only square matrices have complements matrix!");
  Matrix result(rows_, cols_);
  if (cols_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result.matrix_[i][j] = CalcMinor(i, j) * ((i + j) % 2 == 0 ? 1 : -1);
  }
  return result;
}

double Matrix::Determinant() const {
  if (cols_ != rows_)
    throw std::invalid_argument("Only square matrices have determinant!");
  double result = 0;
  if (cols_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else if (cols_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int j = 0; j < cols_; j++)
      result += matrix_[0][j] * CalcMinor(0, j) * ((j % 2) == 0 ? 1 : -1);
  }
  return result;
}

Matrix Matrix::InverseMatrix() const {
  double det = Determinant();
  if (cols_ != rows_ || fabs(det) < EPS)
    throw std::invalid_argument("This matrix has no inverse matrix!");
  Matrix temp = CalcComplements().Transpose();
  temp.MulNumber(1 / det);
  return temp;
}

Matrix& Matrix::operator=(const Matrix& other) {
  if (this != &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      this->~Matrix();
      rows_ = other.rows_, cols_ = other.cols_;
      CreateMatrix();
    }
    CopyMatrixVals(other);
  }
  return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
  if (this != &other) {
    this->~Matrix();
    matrix_ = other.matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    other.matrix_ = nullptr;
    other.cols_ = 0;
    other.rows_ = 0;
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& A) const {
  Matrix result(*this);
  result.SumMatrix(A);
  return result;
}

Matrix Matrix::operator-(const Matrix& A) const {
  Matrix result(*this);
  result.SubMatrix(A);
  return result;
}

Matrix Matrix::operator*(const Matrix& A) const {
  Matrix result(*this);
  result.MulMatrix(A);
  return result;
}

double& Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  return matrix_[row][col];
}

Matrix& Matrix::operator+=(const Matrix& other) {
  SumMatrix(other);
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  SubMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  MulMatrix(other);
  return *this;
}

Matrix& Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

bool Matrix::operator==(const Matrix& A) const { return EqMatrix(A); }

Matrix operator*(const Matrix& A, const double B) {
  Matrix result(A);
  result.MulNumber(B);
  return result;
}

Matrix operator*(const double B, const Matrix& A) {
  Matrix result(A);
  result.MulNumber(B);
  return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& A) {
  for (int i = 0; i < A.rows_; i++) {
    for (int j = 0; j < A.cols_; j++) os << A.matrix_[i][j] << " ";
    os << std::endl;
  }
  os << std::endl;
  return os;
}

int Matrix::GetCols() const { return cols_; }

int Matrix::GetRows() const { return rows_; }

void Matrix::SetCols(int cols) {
  if (cols <= 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  Matrix temp(rows_, cols);
  temp.CopyMatrixVals(*this);
  *this = std::move(temp);
}

void Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range("Incorrect input, index is out of range");
  Matrix temp(rows, cols_);
  temp.CopyMatrixVals(*this);
  *this = std::move(temp);
}
