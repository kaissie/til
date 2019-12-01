#include <iostream>
#include <fstream>
#include <memory>
// write binaru file
template<typename T>
std::ostream& write_as_binary(std::ostream& os, const T& val)
{
    os.write((char*)std::addressof(val), sizeof(T));
    return os;
}

// read binary file
template<typename T>
T read_binary_as(std::istream& is)
{
    T val;
    is.read((char*)std::addressof(val),sizeof(T));
    return val;
}

int main(int argc, char const *argv[]) {
  std::cout << "/* ------ Write binary file ------ */" << '\n';
  std::ofstream ofs("example.bin", std::ios::out | std::ios::binary);
  const std::int32_t i = 9999;
  const std::int32_t j = 1234;

  std::cout << std::dec << i << " >> ";
  std::cout << std::hex << i << '\n';
  std::cout << std::dec << j << " >> ";
  std::cout << std::hex << j << '\n';

  write_as_binary(ofs,i);
  write_as_binary(ofs,j);
  ofs.close();



  std::cout << "/* ------ Read binary file ------ */" << '\n';
  std::ifstream ifs("example.bin", std::ios::in | std::ios::binary);
  const auto ri =  read_binary_as<std::int32_t>(ifs);

  // seek pointer
  ifs.seekg(sizeof(ri));
  const auto rj =  read_binary_as<std::int32_t>(ifs);

  std::cout << std::hex << ri << " >> ";
  std::cout << std::dec << ri << '\n';
  std::cout << std::hex << rj << " >> ";
  std::cout << std::dec << rj << '\n';
  ifs.close();
  return 0;
}
