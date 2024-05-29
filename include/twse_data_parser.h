#ifndef PARSE_TWSE_DATA_SRC_TWSE_DATA_PARSER_H
#define PARSE_TWSE_DATA_SRC_TWSE_DATA_PARSER_H
// relative header file
// C sys files
// C++ sys files
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
// other library header files
// project header files
#include "../include/twse_data_format.h"
#include "../include/utilities.h"

class TWSEDataParser {
 public:
  TWSEDataParser(const std::string& filename);
  ~TWSEDataParser();
  bool IsEnd();
  bool GetTWSEData(TWSEData& twse_data);

 private:
  std::ifstream ifs_;
  char read_buf_[1] = {0};
  size_t esc_code_pos_ = 0;
  char len_buf_[2] = {0};
  char checksum_ = 0;
  bool is_end_ = false;
};

#endif  // PARSE_TWSE_DATA_SRC_TWSE_DATA_PARSER_H