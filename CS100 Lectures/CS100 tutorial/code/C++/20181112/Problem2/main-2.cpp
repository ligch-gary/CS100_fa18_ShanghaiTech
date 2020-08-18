#include <stdlib.h>
#include <vector>
#include <iostream>

template<typename T>
class Matrix2 {
public:
  Matrix2() {
    T zeroElement = 0;
    m_elements.resize(4,zeroElement);
  };
  virtual ~Matrix2() {};

  T& at( int row, int col ) {
    return m_elements[col*2+row];
  };

  void transpose() {
    T element = this->at(0,1);
    this->at(0,1) = this->at(1,0);
    this->at(1,0) = element;
  };

  void add( Matrix2<T> & matrix ) {
    this->at(0,0) += matrix.at(0,0);
    this->at(1,0) += matrix.at(1,0);
    this->at(0,1) += matrix.at(0,1);
    this->at(1,1) += matrix.at(1,1);
  };

  void remove( Matrix2<T> & matrix ) {
    this->at(0,0) -= matrix.at(0,0);
    this->at(1,0) -= matrix.at(1,0);
    this->at(0,1) -= matrix.at(0,1);
    this->at(1,1) -= matrix.at(1,1);
  };

  T determinant() {
    return this->at(0,0) * this->at(1,1) - this->at(1,0) * this->at(0,1);
  };

  void print() {
    std::cout << this->at(0,0) << " " << this->at(0,1) << "\n";
    std::cout << this->at(1,0) << " " << this->at(1,1) << "\n";
    std::cout << "\n";
  };

private:
  std::vector<T> m_elements;
};

int main() {
  Matrix2<float> matrix;
  matrix.at(0,0) = 0.1f;
  matrix.at(1,0) = 1.2f;
  matrix.at(0,1) = 2.3f;
  matrix.at(1,1) = 3.4f;

  std::cout << "The original matrix is:\n";
  matrix.print();

  std::cout << "Transposing the matrix returns:\n";
  matrix.transpose();
  matrix.print();

  std::cout << "The determinant is: " << matrix.determinant() << "\n";

  std::cout << "The matrix times 2 is:\n";
  matrix.add(matrix);
  matrix.print();

  std::cout << "Subtracting the matrix from itself returns:\n";
  matrix.remove(matrix);
  matrix.print();

  return 0;
}