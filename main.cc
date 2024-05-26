// relative header file
// C sys files
#include <string.h>
// C++ sys files
#include <fstream>
#include <iostream>
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

  size_t esc_code_pos = 0;
  char len_buf[2] = {0};
  char checksum = 0;

  while (!ifs.eof()) {
    ifs.read(buffer, sizeof(buffer));
    if (buffer[0] == 0x1b) {
      esc_code_pos = ifs.tellg();
      bzero(len_buf, sizeof(len_buf));
      ifs.read(len_buf, sizeof(len_buf));
      // ShowHex(len_buf, 2);
      int len = CharToInt16(len_buf, 2);
      if (len < 13) {
        cout << "len is less than 13.\n";
        ShowHexPosition(esc_code_pos);
        ifs.seekg(esc_code_pos);
        continue;
      }
      char data_buf[len - 3];
      bzero(data_buf, sizeof(data_buf));
      ifs.read(data_buf, len - 3);
      if (ifs.gcount() != len - 3) {
        cout << "EOF.\n";
        ShowHexPosition(esc_code_pos);
        break;
      }
      if (data_buf[len - 5] != 0x0D && data_buf[len - 4] != 0x0A) {
        cout << "termainal code not match \n";
        ShowHexPosition(esc_code_pos);
        ifs.seekg(esc_code_pos);
        continue;
      }
      checksum = CalculateXOR(len_buf, data_buf, len - 6);
      if (data_buf[len - 6] != checksum) {
        cout << "checksum not match! data=" << (int)data_buf[len - 6] 
        << " res="<< (int)checksum <<"\n";
        ShowHexPosition(esc_code_pos);
        ifs.seekg(esc_code_pos);
        continue;
      }
      ShowHexPosition(esc_code_pos);
      cout << "len: " << len << endl;
      // ShowHex(data_buf, len - 3);
      cout<< "======================" << endl;
    }
  }
  ifs.close();
  return 0;
}
