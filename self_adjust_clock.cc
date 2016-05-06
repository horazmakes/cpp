#include <sys/time.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>

/*
 * This programs should be compiled in c++0x mode (C++11)
 * g++ -std=c++0x self_adjust_clock.cc
 */

int main(void) {
  // 1. Get full current time
  timeval curTime;
  gettimeofday(&curTime, NULL);
  int milli = curTime.tv_usec / 1000;
  tm *the_time = localtime(&curTime.tv_sec);

  // 2. Find out the number of milliseconds until the next complete second
  int sleep_ms = 1000 - milli;

  // 3. Sleep for the number of milliseconds until the next complete second
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));

  // 4. Again, get full current time
  gettimeofday(&curTime, NULL);
  the_time = localtime(&curTime.tv_sec);

  std::cout << std::setfill('0') << std::setw(2) << the_time -> tm_hour;
  std::cout << ":" << std::setfill('0') << std::setw(2) << the_time -> tm_min;
  std::cout << ":" << std::setfill('0') << std::setw(2) << the_time -> tm_sec << std::endl;

  // 5. Find out the number of milliseconds until the next complete minute
  int sec = the_time->tm_sec;
  int sleep_s = 60000 - (1000 * sec);

  // 6. Sleep for the number of milliseconds until the next complete minute
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_s));

  // At this point milliseconds and seconds should be adjusted to zero
  gettimeofday(&curTime, NULL);
  the_time = localtime(&curTime.tv_sec);

  std::cout << std::setfill('0') << std::setw(2) << the_time -> tm_hour;
  std::cout << ":" << std::setfill('0') << std::setw(2) << the_time -> tm_min;
  std::cout << ":" << std::setfill('0') << std::setw(2) << the_time -> tm_sec << std::endl;

  return 0;
}
