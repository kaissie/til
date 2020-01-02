#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>

bool compare_by_second(std::pair<char, float> a, std::pair<char, float> b) {
    if(a.second != b.second)
        return a.second > b.second;
    else
        return a.first > b.first;
}

int main(int argc, char const *argv[]) {
  std::ifstream ifs("./resources/stage1");
  std::string str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
  if (ifs.fail())
  {
      std::cerr << "Failed" << std::endl;
      return -1;
  }else{
    std::cout << "<Cryptogram>" << '\n';
    std::cout << str << '\n';
  }

  std::cout << "Frequency analysis" << '\n';
  std::map<char, int> analysis_map;
  int count = 0;
  for (const auto c : str) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        analysis_map.insert_or_assign(c, analysis_map[c]+1);
        count++;
      }
  }

  std::cout << "----------frequency data---------" << '\n';
  std::vector<std::pair<char, float> > analysis_vec;
  auto begin = analysis_map.begin(), end = analysis_map.end();
  for (auto iter = begin; iter != end; iter++) {
    float value = (100.0*iter->second/(float)count);
    std::cout << iter->first << " "<< value << "\n";
    analysis_vec.push_back(std::make_pair(iter->first, value));
  }
  std::cout << "------sorted frequency data------" << '\n';
  std::sort(analysis_vec.begin(), analysis_vec.end(), compare_by_second);
  for (const auto data : analysis_vec) {
      std::cout << data.first << " "<< data.second << "\n";
  }
  return 0;
}
