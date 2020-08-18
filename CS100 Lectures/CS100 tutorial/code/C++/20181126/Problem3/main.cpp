#include "stdlib.h"
#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>

bool onRightSide;
std::mutex mut;
std::condition_variable data_cond;

void player( bool isRightSidePlayer, std::string message ) {
  while(1) {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk,[&isRightSidePlayer]{return isRightSidePlayer == onRightSide;});
    std::cout << message << "\n";
    usleep(1000000);
    onRightSide = !onRightSide;
    lk.unlock();
    data_cond.notify_one();
  }
}

int main() {
  onRightSide = true;

  std::thread leftPlayer( player, false, std::string("Pong") );
  std::thread rightPlayer( player, true, std::string("Ping") );
  leftPlayer.join();
  rightPlayer.join();

  return 0;
}