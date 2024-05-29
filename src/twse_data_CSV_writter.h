#ifndef PARSE_TWSE_DATA_SRC_TWSE_DATA_CSV_WRITTER_H
#define PARSE_TWSE_DATA_SRC_TWSE_DATA_CSV_WRITTER_H
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
#include "src/twse_data_format.h"
#include "src/utilities.h"

class TWSEDataWritter {
 public:
  TWSEDataWritter(const std::string& filename);
  ~TWSEDataWritter();
  void WriteTWSEData(const TWSEData& twse_data);

 private:
  std::ofstream ofs_;
  TWSEDataHeader* header_;
  TWSEDataBody6* body_;
};

#endif  // PARSE_TWSE_DATA_SRC_TWSE_DATA_CSV_WRITTER_H