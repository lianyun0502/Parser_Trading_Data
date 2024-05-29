// relative header file
// C sys files
#include <string.h>
// C++ sys files
#include <fstream>
#include <iostream>
// other library header files
// project header files
#include "include/twse_data_format.h"
#include "include/twse_data_parser.h"
#include "include/twse_data_CSV_writter.h"
#include "include/utilities.h"

using namespace std;

int main() {
  TWSEDataParser parser("twse_20230808.bin");
  TWSEDataWritter writter("twse_20230808.csv");

  while (!parser.IsEnd()) {
    TWSEData twse_data;
    bzero(&twse_data, sizeof(twse_data));
    if (parser.GetTWSEData(twse_data)) {
        writter.WriteTWSEData(twse_data);
      }
    }
  return 0;
}
