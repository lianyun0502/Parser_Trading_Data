// relative header file
// C sys files
#include <string.h>
// C++ sys files
#include <fstream>
#include <iostream>
// other library header files
// project header files
#include "src/twse_data_format.h"
#include "src/utilities.h"

using namespace std;

int main() {
  char buffer[1] = {0};

  ifstream ifs("twse_20230808.bin", ios::in | ios::binary);
  if (!ifs.is_open()) {
    cerr << "Failed to open file." << endl;
    return 1;  // EXIT_FAILURE
  }

  ofstream ofs("twse_20230808.csv");
  if (!ofs.is_open()) {
    cerr << "Unable to open file: twse_20230808.csv" << endl;
    return 1;
  }

  ofs << "symbol,symbol_id,exchtime,localtime,status,"
      << "last_price,previous_close,open,high_limit,low_limit,total_trade,"
         "total_volume,total_value,"
      << "average_ask_price,average_bid_price,total_ask_volume,total_bid_"
         "volume,"
      << "ask_price1,ask_volume1,bid_price1,bid_volume1,ask_price2,ask_volume2,"
         "bid_price2,bid_volume2,"
      << "ask_price3,ask_volume3,bid_price3,bid_volume3,ask_price4,ask_volume4,"
         "bid_price4,bid_volume4,"
      << "ask_price5,ask_volume5,bid_price5,bid_volume5,sequence\n";

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
      int len = BCDToInt16(len_buf, 2);
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
             << " res=" << (int)checksum << "\n";
        ShowHexPosition(esc_code_pos);
        ifs.seekg(esc_code_pos);
        continue;
      }
      char data_seq[len] = {0};
      data_seq[0] = 0x1b;
      memcpy(data_seq + 1, len_buf, 2);
      memcpy(data_seq + 3, data_buf, len - 3);
      TWSEDataHeader header;
      header.ParseHeader(data_seq);
      if (header.GetFormatId() == 6) {
        TWSEDataBody6 body;
        body.ParseBody(data_seq);
        ofs << body.symbol_ << "," << header.socket_id_ << "," << body.exchtime_
            << "," << header.localtime_ << "," << body.status_ << ","
            << body.last_price_map_[body.symbol_] << ","
            << TWSEDataBody1::previous_close_map_[body.symbol_] << ","
            << body.open_map_[body.symbol_] << ","
            << TWSEDataBody1::high_limit_map_[body.symbol_] << ","
            << TWSEDataBody1::low_limit_map_[body.symbol_] << ","
            << body.total_trade_ << "," << body.total_volume_ << ","
            << body.total_value_ << "," << body.average_ask_price_ << ","
            << body.average_bid_price_ << "," << body.average_ask_volume_ << ","
            << body.average_bid_volume_ << "," << body.ask_price1_ << ","
            << body.ask_volume1_ << "," << body.bid_price1_ << ","
            << body.bid_volume1_ << "," << body.ask_price2_ << ","
            << body.ask_volume2_ << "," << body.bid_price2_ << ","
            << body.bid_volume2_ << "," << body.ask_price3_ << ","
            << body.ask_volume3_ << "," << body.bid_price3_ << ","
            << body.bid_volume3_ << "," << body.ask_price4_ << ","
            << body.ask_volume4_ << "," << body.bid_price4_ << ","
            << body.bid_volume4_ << "," << body.ask_price5_ << ","
            << body.ask_volume5_ << "," << body.bid_price5_ << ","
            << body.bid_volume5_ << "," << header.sequence_ << "\n";
      } else if (header.GetFormatId() == 1) {
        TWSEDataBody1 body;
        body.ParseBody(data_seq);
      } else {
        continue;
      }
      ShowHexPosition(esc_code_pos);
      cout << "len: " << len << endl;
      // ShowHex(data_buf, len - 3);
      cout << "======================" << endl;
    }
  }
  ifs.close();
  ofs.close();
  return 0;
}
