/*******************************************************
 *
 * Problem 2 consists of implementing a template Matrix class.
 * The class should heavily rely on operators to enable convenient
 * encoding of arithmetic operations (see main function below for examples).
 * The exact interface is indicated below, and please also consider
 * the homework instructions for detailed background information.
 *
 * You are to modify lines
 *
 * -19 to 59: Add your implementation of the template Matrix class
 * 
 *******************************************************/

#include <stdlib.h>
#include <vector>
#include <iostream>
template <class T>
class Matrix
{
  public:
    Matrix( int rs, int cs, T val = 0 ){
      m_rs = rs;
      m_cs = cs;
      vec1.resize(m_rs);
      for(int i = 0 ;i < m_rs;i++)
      {
        for(int j= 0 ;j < m_cs;j++)
        {
          vec1[i].push_back(val);
        }
      }
    }
    virtual ~Matrix(){
        for(int i = 0 ;i < m_rs;i++)
       {
         for(int j= 0 ;j < m_cs;j++)
         {
            vec1[i].clear();
         }
       }
    }
    Matrix<T> & resize( int rs, int cs, T val = 0 ){
      m_rs = rs;
      m_cs = cs;
      vec1.resize(rs);
      for (int i = 0;i<rs;i++)
        vec1[i].resize(cs,val);
      return *this;
    }
    T         & operator()( int r, int c ){
       return (*this).vec1[r][c];
    }
    const T   & operator()( int r, int c ) const{
       return (*this).vec1[r][c];
    }
    size_t      rows() const{
      return m_rs;
    }
    size_t      cols() const{
      return m_cs;
    }
    Matrix<T>   block( int r, int c, int h, int w ) const{
         Matrix<T> temp(h,w);
         for(int i=r;i<r+h;i++){
           for(int j=c;j<c+w;j++){
             temp.vec1[i-r][j-c]=vec1[i][j];
           }
         }  
         return temp;            
    }
    Matrix<T> & setBlock( int r, int c, int h, int w, T & val ){
      for (int i=r;i<r+h;i++){
        for (int j=c;j<c+w;j++){
          vec1[i][j]=val;
        }
      }
      return *this;
    }
    Matrix<T> & setBlock( int r, int c, const Matrix<T> & val ){
      for (int i=r;i<r+val.m_rs;i++){
        for (int j=c;j<c+val.m_cs;j++){
           vec1[i][j]=val.vec1[i-r][j-c];
        }
      }
      return *this;
    }
    Matrix<T> & setIdentity(){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        {
          if(i==j){
            vec1[i][j]=1;
          }
          else{
            vec1[i][j]=0;
          }
        }
      }
      return *this;
    }
    Matrix<T> & setConstant( const T & val ){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] = val;
      }
      return *this;
    }
    Matrix<T> & setZero(){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] = 0;
      }
      return *this;
    }
    Matrix<T>   transpose() const{
      Matrix<T> temp(m_cs,m_rs);
      for(int i=0;i<m_cs;i++)
      {
        for(int j=0;j<m_rs;j++)
        temp.vec1[i][j] = (*this).vec1[j][i];
      }
      return temp;
    }
    Matrix<T> & transposeInPlace(){
      Matrix<T> temp(m_cs,m_rs);
      for(int i=0;i<m_cs;i++)
      {
        for(int j=0;j<m_rs;j++)
        temp.vec1[i][j] = (*this).vec1[j][i];
      }
      (*this).resize(m_cs,m_rs);
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] = temp.vec1[i][j];
      }
      return *this;
    }
    Matrix<T>   operator+ ( const Matrix<T> & op ) const{
      Matrix<T> temp(m_rs,m_cs);
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] = (*this).vec1[i][j];
      }
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] += op.vec1[i][j];
      }
      return temp;
    }
    Matrix<T> & operator+=( const Matrix<T> & op ){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] += op.vec1[i][j];
      }
      return *this;
    }
    Matrix<T>   operator- ( const Matrix<T> & op ) const{
      Matrix<T> temp(m_rs,m_cs);
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] = (*this).vec1[i][j];
      }
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] -= op.vec1[i][j];
      }
      return temp;
    }
    Matrix<T> & operator-=( const Matrix<T> & op ){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] -= op.vec1[i][j];
      }
      return *this;
    }
    Matrix<T>   operator* ( const T & op ) const{
      Matrix<T> temp(m_rs,m_cs);
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] = (*this).vec1[i][j];
      }
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        temp.vec1[i][j] *= op;
      }
      return temp;
    }
    Matrix<T>   operator* ( const Matrix<T> & op ) const{
      Matrix<T> temp(m_rs,op.m_cs,0);
      int m;
      for (int i=0;i<m_rs;i++){
        for (m=0;m<op.m_cs;m++){
          for(int j=0;j<m_cs;j++){
            temp.vec1[i][m] += vec1[i][j]*op.vec1[j][m];
          }
        }
      }
      return temp;
    }
    Matrix<T> & operator*=( const T & op ){
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        (*this).vec1[i][j] *= op;
      }
      return *this;
    }
    Matrix<T>   hadamard  ( const Matrix<T> & op ) const{
      Matrix<T> temp(m_rs,m_cs);
      for (int i=0;i<m_rs;i++){
        for (int j=0;j<m_cs;j++){
          temp.vec1[i][j]=vec1[i][j]*op.vec1[i][j];
        }
      }
      return temp;
    }
    T           sum() const{
      T m_sum = 0;
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        m_sum += vec1[i][j];
      }
      return m_sum;
    }
  protected:
  int m_cs,m_rs;
  std::vector<std::vector<T> >vec1;
};




void printMatrix( const Matrix<float> & A ) {
  for( int r = 0; r < A.rows(); r++ ) {
    for( int c = 0; c < A.cols(); c++ ) {
      std::cout << A(r,c) << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  //get the rows and cols
  int rows, cols;
  std::cin >> rows >> cols;

  //initialize the matrix
  Matrix<float> A(rows,cols);
  for( int r = 0; r < rows; r++ ) {
    for( int c = 0; c < cols; c++ ) {
      std::cin >> A(r,c);  

    }
  }

  //do the operations
  Matrix<float> A1 = A.block(0,0,rows,rows);
  Matrix<float> A2 = A.block(0,cols-rows,rows,rows);
  Matrix<float> A3 = A1 + A2.transpose();
  Matrix<float> A4 = A1 - A2.transpose();
  Matrix<float> A5 = A1 * A2 * 2.0f; A5 *= 3.33f;
  Matrix<float> A6 = A1.hadamard(A2);
  A3 += A5;
  A4 -= A6;
  A1.setIdentity();
  A2.setConstant(4.44f);
  A.setBlock(0,0,A1);  
  A.setBlock(0,cols-rows,A2);
  A.transposeInPlace();
  //print the result to the console
  printMatrix(A3);
  printMatrix(A4);
  printMatrix(A5);
  printMatrix(A6);
  printMatrix(A);

  return 0;
}
