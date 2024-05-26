// Description: utilities functions

// relative header file
#include "src/utilities.h"
// C sys files
// C++ sys files
#include <iomanip>
// other library header files
// project header files

using namespace std;

void ShowHex(char* c_buf, int len) {
  for (int i = 0; i < len; ++i) {
    cout << setfill('0') << setw(2) << hex << (0xff & (uint16_t)c_buf[i])
         << " ";
    if (i % 16 == 15) {
      cout << '\n';
    }
  }
  cout << setfill(' ') << setw(0) << dec << endl;
}

void ShowHexPosition(size_t pos) {
  cout << "position: " << setfill('0') << setw(8) << hex << pos << setfill(' ')
       << setw(0) << dec << endl;
}

// convert BCD to int
// input is 1 byte char
// retrun is 2 digit int
// ex, 0x89 to 89
int BCDToInt(const char& bcd) { return (bcd & 0xF) + ((bcd >> 4) & 0xF) * 10; }

int CharToInt16(const char* char_buf, int len) {
  int result = 0;
  for (int i = 0; i < len; ++i) {
    result += (BCDToInt(char_buf[i]) * pow(10, 2 * (len - i - 1)));
  }
  return result;
}

// Calculate XOR of an byte array
// input is byte array and length
// return is XOR result (char)
char CalculateXOR(const char* data_len, const char* payload, size_t check_len) {
  char xorResult = data_len[0] ^ data_len[1];
  for (size_t i = 0; i < check_len; ++i) {
    xorResult ^= payload[i];
  }
  return xorResult;
}