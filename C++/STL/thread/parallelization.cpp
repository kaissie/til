#include <thread>

#include <chrono>
#include <iostream>

template <typename T>
void exec_time(T func) {
  std::chrono::system_clock::time_point  start, end; // 型は auto で可
  start = std::chrono::system_clock::now(); // 計測開始時間
  // 処理
  func();
  end = std::chrono::system_clock::now();  // 計測終了時間
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count(); //処理に要した時間をミリ秒に変換
  std::cout << "calculation time : "<< elapsed << "ms" << '\n';

}

void ThreadA()
{
  std::cout << __FUNCTION__ << '\n';
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ThreadB()
{
  std::cout << __FUNCTION__ << '\n';
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void multi_thread() {
  std::thread th_a(ThreadA);
  std::thread th_b(ThreadB);

  th_a.join();
  th_b.join();
}

void single_thread() {
  ThreadA();
  ThreadB();
}

int main()
{
  std::cout << "-----<Multi thread>-----" << '\n';
  exec_time(multi_thread);
  std::cout << "-----<Single thread>-----" << '\n';
  exec_time(single_thread);
  return 0;
}
