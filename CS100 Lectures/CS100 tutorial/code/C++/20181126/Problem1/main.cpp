#include <stdlib.h>
#include <map>
#include <unordered_map>
#include "Timer.hpp"
#include <string>
#include <iostream>


int main() {
  std::map<int,std::string>           myMap;
  std::unordered_map<int,std::string> myUnorderedMap;
  Timer mapTimer;
  Timer unorderedMapTimer;

  for( int initSize = 10000; initSize < 9999999; initSize *= 10 ) {
    std::cout << "trying out addition after initial size of " << initSize << "\n";
    mapTimer.reset();
    unorderedMapTimer.reset();
    myMap.clear();
    myUnorderedMap.clear();

    for( int i = 0; i < initSize; i++ ) {
      myMap[i] = std::string("Dummy string");
      myUnorderedMap[i] = std::string("Dummy string");
    }

    mapTimer.start();
    for( int i = 0; i < 100; i++ ) {
      myMap[initSize+i] = std::string("Dummy string");
    }
    mapTimer.stop();

    unorderedMapTimer.start();
    for( int i = 0; i < 100; i++ ) {
      myUnorderedMap[initSize+i] = std::string("Dummy string");
    }
    unorderedMapTimer.stop();

    //report comparison
    std::cout << "adding 100 elements to a map takes " << mapTimer.averageTime() << " s\n";
    std::cout << "adding 100 elements to an unordered map takes " << unorderedMapTimer.averageTime() << " s\n";
  }

  return 0;
}