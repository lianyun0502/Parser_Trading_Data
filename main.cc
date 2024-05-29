// relative header file
// C sys files
#include <string.h>
// C++ sys files
#include <fstream>
#include <iostream>
// other library header files
// project header files
#include "include/twse_data_CSV_writter.h"
#include "include/twse_data_format.h"
#include "include/twse_data_parser.h"
#include "include/utilities.h"

using namespace std;

int main(int argc, char *argv[]) {
  string input_filename = "twse_20230808.bin";
  string output_filename = "twse_20230808.csv";
  if (argc == 3) {
    string input_filename = argv[1];
    string output_filename = argv[2];
  }

  cout << "input_filename: " << input_filename << endl;
  cout << "output_filename: " << output_filename << endl;

  TWSEDataParser parser(input_filename);
  TWSEDataWritter writter(output_filename);

  while (!parser.IsEnd()) {
    TWSEData twse_data;
    bzero(&twse_data, sizeof(twse_data));
    if (parser.GetTWSEData(twse_data)) {
      writter.WriteTWSEData(twse_data);
    }
  }
  return 0;
}
