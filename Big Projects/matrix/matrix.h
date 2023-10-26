#ifndef MATRIX
#define MATRIX

#include <stdexcept>
#include <iostream>

class MatrixIsDegenerateError : public std::runtime_error {
 public:
  MatrixIsDegenerateError() : std::runtime_error("MatrixIsDegenerateError") {
  }
};

class MatrixOutOfRange : public std::out_of_range {
 public:
  MatrixOutOfRange() : std::out_of_range("MatrixOutOfRange") {
  }
};

template <class T, size_t N, size_t M>
class Matrix {
 public:
  T array[N][M];
  size_t RowsNumber() const;
  size_t ColumnsNumber() const;
  T& operator()(size_t row, size_t column);
  const T& operator()(size_t row, size_t column) const;
  T& At(size_t row, size_t column);
  const T& At(size_t row, size_t column) const;
  Matrix<T, N, M>& operator*=(double);
  Matrix<T, N, M>& operator/=(double);
  Matrix<T, N, M>& operator+=(Matrix<T, N, M>);
  Matrix<T, N, M>& operator-=(Matrix<T, N, M>);
  Matrix<T, N, M>& operator*=(Matrix<T, M, M>);
};

template <class T, size_t N, size_t M>
size_t Matrix<T, N, M>::RowsNumber() const {
  return N;
}

template <class T, size_t N, size_t M>
size_t Matrix<T, N, M>::ColumnsNumber() const {
  return M;
}

template <class T, size_t N, size_t M>
T& Matrix<T, N, M>::operator()(size_t row, size_t column) {
  return array[row][column];
}

template <class T, size_t N, size_t M>
const T& Matrix<T, N, M>::operator()(size_t row, size_t column) const {
  return array[row][column];
}

template <class T, size_t N, size_t M>
T& Matrix<T, N, M>::At(size_t row, size_t column) {
  if (row >= N || column >= M) {
    throw MatrixOutOfRange();
  }
  return array[row][column];
}

template <class T, size_t N, size_t M>
const T& Matrix<T, N, M>::At(size_t row, size_t column) const {
  if (row >= N || column >= M) {
    throw MatrixOutOfRange();
  }
  return array[row][column];
}

template <class T, size_t N, size_t M>
Matrix<T, M, N> GetTransposed(Matrix<T, N, M> matrix) {
  Matrix<T, M, N> transposed;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      transposed.array[j][i] = matrix.array[i][j];
    }
  }
  return transposed;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator+(Matrix<T, N, M> matrix1, Matrix<T, N, M> matrix2) {
  Matrix<T, N, M> summary;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      summary.array[i][j] = matrix1.array[i][j] + matrix2.array[i][j];
    }
  }
  return summary;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator+=(Matrix<T, N, M> matrix_sum) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      array[i][j] += matrix_sum.array[i][j];
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator-(Matrix<T, N, M> matrix1, Matrix<T, N, M> matrix2) {
  Matrix<T, N, M> unsummary;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      unsummary.array[i][j] = matrix1.array[i][j] - matrix2.array[i][j];
    }
  }
  return unsummary;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator-=(Matrix<T, N, M> matrix1_unsum) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      array[i][j] -= matrix1_unsum.array[i][j];
    }
  }
  return *this;
}

template <class T, size_t N, size_t M, size_t K>
Matrix<T, N, M> operator*(Matrix<T, N, K> matrix1, Matrix<T, K, M> matrix2) {
  Matrix<T, N, M> times_matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] = 0;
    }
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      for (size_t k = 0; k < K; ++k) {
        times_matrix.array[i][j] += matrix1.array[i][k] * matrix2.array[k][j];
      }
    }
  }
  return times_matrix;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(Matrix<T, M, M> matrix1) {
  Matrix<T, N, M> times_matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] = 0;
    }
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      for (size_t k = 0; k < M; ++k) {
        times_matrix.array[i][j] += array[i][k] * matrix1.array[k][j];
      }
    }
  }
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      array[i][j] = times_matrix.array[i][j];
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator*=(double num) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      array[i][j] *= num;
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M>& Matrix<T, N, M>::operator/=(double num) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      array[i][j] /= num;
    }
  }
  return *this;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(double num, Matrix<T, N, M> matrix) {
  Matrix<T, N, M> times_matrix = matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] *= num;
    }
  }
  return times_matrix;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(double num, Matrix<T, N, M> matrix) {
  Matrix<T, N, M> times_matrix = matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] /= num;
    }
  }
  return times_matrix;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator*(Matrix<T, N, M> matrix, double num) {
  Matrix<T, N, M> times_matrix = matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] *= num;
    }
  }
  return times_matrix;
}

template <class T, size_t N, size_t M>
Matrix<T, N, M> operator/(Matrix<T, N, M> matrix, double num) {
  Matrix<T, N, M> times_matrix = matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      times_matrix.array[i][j] /= num;
    }
  }
  return times_matrix;
}

template <class T, size_t N, size_t M>
bool operator==(Matrix<T, N, M> matrix1, Matrix<T, N, M> matrix2) {
  bool flag = true;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix1.array[i][j] != matrix2.array[i][j]) {
        flag = false;
      }
    }
  }
  return flag;
}

template <class T, size_t N, size_t M>
bool operator!=(Matrix<T, N, M> matrix1, Matrix<T, N, M> matrix2) {
  bool flag = true;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      if (matrix1.array[i][j] != matrix2.array[i][j]) {
        flag = false;
      }
    }
  }
  return !flag;
}

template <class T, size_t N, size_t M>
std::istream& operator>>(std::istream& io, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M; ++j) {
      io >> matrix.array[i][j];
    }
  }
  return io;
}

template <class T, size_t N, size_t M>
std::ostream& operator<<(std::ostream& os, Matrix<T, N, M>& matrix) {
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < M - 1; ++j) {
      os << matrix.array[i][j] << ' ';
    }
    os << matrix.array[i][M - 1] << '\n';
  }
  return os;
}
#endif