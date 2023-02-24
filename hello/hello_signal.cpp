#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

volatile std::atomic_bool running = true;
volatile std::atomic_int signal_status;
void signal_handler(int signal) {
  running = false;
  signal_status = signal;
}

int main(int argc, char *argv[]) {
  std::signal(SIGINT, signal_handler);

  int cnt{};
  while (running) {
    std::cout << "cnt: " << ++cnt << std::endl;
    std::this_thread::sleep_for(1s);
  }

  std::cout << "quit with signal_status: " << signal_status << std::endl;
  return 0;
}
