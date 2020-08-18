#include <stdlib.h>
#include <vector>
#ifndef ONLINE_JUDGE
#include <thread>
#endif
#include <iostream>

/*******************************************************
 *
 * Problem 3 consists of implementing a hyper-threaded kernel
 * convolution over a large matrix. For those interested in the background,
 * a short introduction to kernel convolutions is provided in the homework instruction,
 * along with further pointers to references on the internet. Please refer to the homework
 * instructions for a detailed description of Problem 3.
 *
 * Your task is to implement the actual kernel application thread, which will be executed in
 * four thread in parallel operating over different parts of the input matrix. You are supposed to
 * modify the code lines (further details provided below):
 *
 * -lines 23 to 36: Please add a generic matrix class implementation here (you may reuse the one from problem 2)
 * -lines 49 to 61: Implement the kernel application thread
 *
 ****************************/

/****************************
 * 
 * Add a template implementation of a matrix class
 * It should support the operations of accessing an element of the matrix,
 * taking a sub-block, element-wise multiplication, and summation over all elements
 * of the matrix.
 *
 * NOTE: you may reuse the matrix implementation from Problem 2!! It has all you need
 *
 *
 * template<class T>
 * class Matrix
 *
 ****************************/
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
      T m_sum=0;
      for(int i=0;i<m_rs;i++)
      {
        for(int j=0;j<m_cs;j++)
        m_sum += vec1[i][j];
      }
      return m_sum;
    }

  int m_cs,m_rs;
  std::vector<std::vector<T> >vec1;
};
// Use this struct to pass the required information to each thread
// (this includes the input matrix, the output matrix, the kernel,
// the number of threads, and the thread-index)

struct KernelApplicationJob {
  Matrix<float> * src;
  Matrix<float> * K;
  Matrix<float> * dst;
  size_t threadIndex;
  size_t numberThreads;
};

/****************************
 * 
 * Implement the following function which will run in a thread.
 * The function is supposed to run the kernel convolution over
 * a sub-part of the image. If employing 4 threads (as we do),
 * the function should process 25% of the output matrix. The
 * threadIndex variable is used to decide which one of sub-parts
 * this thread is working on
 *
 *
 * void kernelApplicationThread( KernelApplicationJob & my_job );
 *
 ****************************/
void kernelApplicationThread( KernelApplicationJob & my_job ){
  int h=(((my_job.K)->rows())-1) * 0.5;
  int w=(((my_job.K)->cols())-1) * 0.5;
  for (int i=0;i< (my_job.src)->rows();i++){
    for (int j=0;j< (my_job.src)->cols();j++){
      if ( i-h>=0 && j-w>=0 && (i+h+1)<=(my_job.src)->rows() && (j+w+1) <=(my_job.src)->cols())
         (*(my_job.dst)).vec1[i][j]= ((*(my_job.K)).hadamard((*(my_job.src)).block(i-h,j-w,2*h+1,2*w+1))).sum();
      else
         (*(my_job.dst)).vec1[i][j]=0;
    }
  }
}
/*************** Do not change any code below this line!! *************/

int main() {
  size_t numberThreads = 4;

  //read in some matrix
  size_t rows;
  size_t cols;
  size_t kernelType;
  std::cin >> rows >> cols >> kernelType;
  Matrix<float> input(rows,cols);
  for( size_t r = 0; r < rows; r++ ) {
    for( size_t c = 0; c < cols; c++ ) {
      std::cin >> input(r,c);
    }
  }

  //define the kernel
  Matrix<float> * Kptr;
  if( kernelType == 0 ) { //gaussian blur kernel 3x3
    Kptr = new Matrix<float>(3,3);
    Matrix<float> & K = *Kptr;
    K(0,0) = (1.0f/16.0f); K(0,1) = (2.0f/16.0f); K(0,2) = (1.0f/16.0f);
    K(1,0) = (2.0f/16.0f); K(1,1) = (4.0f/16.0f); K(1,2) = (2.0f/16.0f);
    K(2,0) = (1.0f/16.0f); K(2,1) = (2.0f/16.0f); K(2,2) = (1.0f/16.0f);
  }
  if( kernelType == 1) { //gaussian blur kernel 5x5
    Kptr = new Matrix<float>(5,5);
    Matrix<float> & K = *Kptr;
    K(0,0) = (2.0f/159.0f); K(0,1) = ( 4.0f/159.0f); K(0,2) = ( 5.0f/159.0f); K(0,3) = ( 4.0f/159.0f); K(0,4) = (2.0f/159.0f);
    K(1,0) = (4.0f/159.0f); K(1,1) = ( 9.0f/159.0f); K(1,2) = (12.0f/159.0f); K(1,3) = ( 9.0f/159.0f); K(1,4) = (4.0f/159.0f);
    K(2,0) = (5.0f/159.0f); K(2,1) = (12.0f/159.0f); K(2,2) = (15.0f/159.0f); K(2,3) = (12.0f/159.0f); K(2,4) = (5.0f/159.0f);
    K(3,0) = (4.0f/159.0f); K(3,1) = ( 9.0f/159.0f); K(3,2) = (12.0f/159.0f); K(3,3) = ( 9.0f/159.0f); K(3,4) = (4.0f/159.0f);
    K(4,0) = (2.0f/159.0f); K(4,1) = ( 4.0f/159.0f); K(4,2) = ( 5.0f/159.0f); K(4,3) = ( 4.0f/159.0f); K(4,4) = (2.0f/159.0f);
  }
  if( kernelType == 2 ) { //average kernel 3x3
    Kptr = new Matrix<float>(3,3,1.0f/9.0f);
  }
  if( kernelType == 3 ) { //average kernel 5x5
    Kptr = new Matrix<float>(5,5,1.0f/25.0f);
  }
  if( kernelType == 4 ) { //horizontal sobel kernel
    Kptr = new Matrix<float>(1,3);
    Matrix<float> & K = *Kptr;
    K(0,0) = -1.0f;
    K(0,2) =  1.0f;
  }
  if( kernelType == 5 ) { //vertical sobel kernel
    Kptr = new Matrix<float>(3,1);
    Matrix<float> & K = *Kptr;
    K(0,0) = -1.0f;
    K(2,0) =  1.0f;
  }
  
  //define the output
  Matrix<float> output(rows,cols);
  
  std::vector<KernelApplicationJob> jobs(numberThreads);
  for( size_t i = 0; i < numberThreads; i++ ) {
    jobs[i].src = &input;
    jobs[i].K = Kptr;
    jobs[i].dst = &output;
    jobs[i].threadIndex = i;
    jobs[i].numberThreads = numberThreads;
  }

#ifndef ONLINE_JUDGE
  //start the threads that apply the kernel
  std::vector<std::thread> kernelApplicators;
  kernelApplicators.reserve(numberThreads);
  for( size_t i = 0; i < numberThreads; i++ )
    kernelApplicators.push_back( std::thread(kernelApplicationThread,std::ref(jobs[i]) ) );

  for( auto& thread : kernelApplicators ) {
    if( thread.joinable() )
      thread.join();
  }
#else
  for( size_t i = 0; i < numberThreads; i++ )
    kernelApplicationThread(jobs[i]);
#endif

  //output the result
  for( size_t r = 0; r < rows; r++ ) {
    for( size_t c = 0; c < cols; c++ ) {
      std::cout << output(r,c) << " ";
    }
    std::cout << "\n";
  }

  return 0;
}
