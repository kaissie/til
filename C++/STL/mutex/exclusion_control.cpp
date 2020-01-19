#include <mutex>

#include <thread>
#include <iostream>

std::mutex mtx_; // 排他制御用ミューテックス
uint32_t count_;
bool use_mutex_ = true;

void mutex_countup() {
  std::lock_guard<std::mutex> lock(mtx_);
  ++count_;
}

void normal_countup() {
    ++count_;
}
void ThreadA() {
  for(int i=0; i<100000; ++i){
    if(use_mutex_)
      mutex_countup();
    else
      normal_countup();
  }
}

void ThreadB() {
  for (int i = 0; i<100000; ++i){
    if(use_mutex_)
      mutex_countup();
    else
      normal_countup();
  }
}

void mutex_thread() {
  use_mutex_ = true;
  count_ = 0;
  std::thread th_a(ThreadA);
  std::thread th_b(ThreadB);

  th_a.join();
  th_b.join();
  std::cout << "Global var : count_ = "<< count_ << '\n';
}

void non_mutex_thread() {
  use_mutex_ = false;
  count_ = 0;
  std::thread th_a(ThreadA);
  std::thread th_b(ThreadB);

  th_a.join();
  th_b.join();
  std::cout << "Global var : count_ = "<< count_ << '\n';
}

int main()
{
  std::cout << "-----<Multi thread using mutex >-----" << '\n';
  mutex_thread();
  std::cout << "-----<Multi thread>-----" << '\n';
  non_mutex_thread();
  return 0;
}
