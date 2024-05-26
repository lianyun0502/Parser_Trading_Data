// relative header file
// C sys files
// C++ sys files
#include <fstream>
#include <iostream>
#include <string>
// other library header files
// project header files
#include "src/utilities.h"

using namespace std;

class TWSEParser {};

int main() {
  char buffer[1] = {0};

  std::ifstream ifs("twse_20230808.bin", std::ios::in | std::ios::binary);
  if (!ifs.is_open()) {
    cout << "Failed to open file.\n";
    return 1;  // EXIT_FAILURE
  }
  while (!ifs.eof()) {
    ifs.read(buffer, sizeof(buffer));
    if (buffer[0] == 0x1b) {
      char len_buf[2] = {0};
      ifs.read(len_buf, sizeof(len_buf));
      ShowHex(len_buf, 2);
      int len = CharToInt16(len_buf, 2);
      if (len < 3) {
        cout << "len is less than 3.\n";
        continue;
      }
      cout << "len: " << len << endl;
      char data_buf[len - 3] = {0};
      ifs.read(data_buf, len - 3);
      ShowHex(data_buf, len - 3);
      cout<< "======================" << endl;
    }
    size_t pos = ifs.tellg();
    cout << "position: " << pos << "\n";
  }
  size_t pos = ifs.tellg();
  cout << "position: " << pos << "\n";
  ifs.close();
  return 0;
}
