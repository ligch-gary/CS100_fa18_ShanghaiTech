#include <stdlib.h>
#include <iostream>

class Number {
public:
  static Number * make_number(int type);

  Number( int type ) : m_type(type) {};

  virtual Number * plus( Number * nbr ) = 0;
  virtual void print() = 0;
  int type() { return m_type; };

private:
  int m_type;
};

class RandomRealNumber : public Number {
public:
  RandomRealNumber() : Number(1) {
    m_nbr = (((double) rand())/ ((double) RAND_MAX)-0.5)*2.0;
  }

  Number * plus( Number * nbr ) {
    if( this->type() != nbr->type() ) {
      std::cout << "Error: you are aiming at adding two incompatible numbers\n";
      return make_number(this->type());
    }

    RandomRealNumber * op = (RandomRealNumber*) nbr;
    RandomRealNumber * result = new RandomRealNumber();
    result->m_nbr = this->m_nbr + op->m_nbr;
    return (Number*) result;
  }

  void print() {
    std::cout << "I am a real number and my value is " << m_nbr << "\n";
  }

private:
  double m_nbr;
};

class RandomRationalNumber: public Number {
public:
  RandomRationalNumber() : Number (2) {
    m_numerator = rand() % 100;
    m_denominator = rand() % 100;
  }

  Number * plus( Number * nbr ) {
    if( this->type() != nbr->type() ) {
      std::cout << "Error: you are aiming at adding two incompatible numbers\n";
      return make_number(this->type());
    }

    RandomRationalNumber * op = (RandomRationalNumber*) nbr;
    RandomRationalNumber * result = new RandomRationalNumber();
    result->m_numerator = this->m_numerator * op->m_denominator + op->m_numerator * this->m_denominator;
    result->m_denominator = this->m_denominator * op->m_denominator;
    return (Number*) result;
  }

  void print() {
    std::cout << "I am a rational number and my value is " << m_numerator << "/" << m_denominator << "\n";
  }

private:
  int m_numerator;
  int m_denominator;
};

Number *
Number::make_number(int choice) {
  if(choice == 1)
    return new RandomRealNumber();
  else
    return new RandomRationalNumber();
}

int main() {
  Number * nbr1 = Number::make_number(1);
  Number * nbr2 = Number::make_number(1);
  Number * nbr3 = Number::make_number(2);
  Number * nbr4 = Number::make_number(2);

  nbr1->print();
  nbr2->print();
  nbr3->print();
  nbr4->print();

  Number * res1 = nbr1->plus(nbr2);
  Number * res2 = nbr3->plus(nbr4);

  res1->print();
  res2->print();

  return 0;
}