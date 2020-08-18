#include "Timer.hpp"
#include <iostream>

Timer::Timer( bool start ) :
    m_running(false) {
  m_totalRunningTime = 0.0;
  m_totalIterations = 0;
  m_lapTimes.clear();

  if( start )
  {
    m_running = true;
    m_startingTime = std::chrono::high_resolution_clock::now();
  }
}

Timer::~Timer()
{}
  
void
Timer::start() {
  if( m_running )
    std::cout << "Error: timer is already started\n";
  
  m_running = true;
  m_startingTime = std::chrono::high_resolution_clock::now();
}

void
Timer::stop( bool restart ) {
  stop( 1, restart );
}

void
Timer::stop( size_t iterations, bool restart ) {
  if( !m_running )
    std::cout << "Error: timer is not started\n";
  
  std::chrono::high_resolution_clock::time_point toc = std::chrono::high_resolution_clock::now();
  double runningTime = (double) std::chrono::duration_cast<std::chrono::microseconds>(toc-m_startingTime).count() / 1000000.0;
  
  m_totalIterations += iterations;
  m_totalRunningTime += runningTime;
  m_lapTimes.push_back(runningTime);
  
  if(restart)
    m_startingTime = toc;
  else
    m_running = false;
}

void
Timer::reset() {
  m_totalRunningTime = 0.0;
  m_totalIterations = 0;
  m_running = false;
}

double
Timer::averageTime() {
  return m_totalRunningTime / m_totalIterations;
}

std::list<double>::iterator
Timer::begin() {
  return m_lapTimes.begin();
}

std::list<double>::iterator
Timer::end() {
  return m_lapTimes.end();
}

void
Timer::sort() {
  m_lapTimes.sort();
}
