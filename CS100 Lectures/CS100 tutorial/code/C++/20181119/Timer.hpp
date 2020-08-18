#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <stdlib.h>
#include <list>
#include <chrono>


class Timer {
public:
  Timer( bool start = false );
  virtual ~Timer();
  
  void start();
  void stop( bool restart = false );
  void stop( size_t iterations, bool restart = false );
  void reset();
  
  double averageTime();
  std::list<double>::iterator begin();
  std::list<double>::iterator end();
  void sort();

  
private:
  std::chrono::high_resolution_clock::time_point m_startingTime;
  bool m_running;

  double m_totalRunningTime;
  int m_totalIterations;
  std::list<double> m_lapTimes;
};

#endif