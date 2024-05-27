#ifndef PARSER_TRADING_DATA_SRC_UTILITIES_H
#define PARSER_TRADING_DATA_SRC_UTILITIES_H
// relative header file
// C sys files

// C++ sys files
#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
// other library header files
// project header files

void ShowHex(char* c_buf, int len);
int BCDToInt(const char& bcd);
int BCDToInt16(const char* char_buf, int len, int offset=0);
int64_t BCDToInt64(const char* char_buf, int len, int offset);
char CalculateXOR(const char* data_len, const char* payload, size_t check_len);
void ShowHexPosition(size_t pos);
float IntToFloat(int value, int decimal);
double IntToDouble(int value, int decimal);

#endif // PARSER_TRADING_DATA_SRC_UTILITIES_H