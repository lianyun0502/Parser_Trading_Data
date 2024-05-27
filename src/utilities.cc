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
int BCDToInt16(const char& bcd) {
  return (bcd & 0xF) + ((bcd >> 4) & 0xF) * 10;
}

int BCDToInt16(const char* char_buf, int len, int offset) {
  int result = 0;
  for (int i = offset; i < offset + len; ++i) {
    result += (BCDToInt16(char_buf[i]) * pow(10, 2 * (len + offset - i - 1)));
  }
  return result;
}

int64_t BCDToInt64(const char* char_buf, int len, int offset) {
  int64_t result = 0;
  for (int i = offset; i < offset + len; ++i) {
    result += (BCDToInt16(char_buf[i]) * pow(10, 2 * (len + offset - i - 1)));
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
float IntToFloat(int value, int decimal) {
  return static_cast<float>(value) / pow(10, decimal);
}

double IntToDouble(int value, int decimal) {
  return static_cast<double>(value) / pow(10, decimal);
}