// relative header file
#include "src/twse_data_format.h"
// C sys files
#include <string.h>
// C++ sys files
#include <iostream>
#include <vector>

// other library header files
// project header files
#include "src/utilities.h"

using namespace std;

void TWSEDataHeader::ParseHeader(const char* data) {
  sequence_ = BCDToInt16(data, 4, 6);
  length_ = BCDToInt16(data, 2, 1);
  format_id_ = BCDToInt16(data, 1, 4);
}

void TWSEDataBody6::ParseBody(const char* data) {
  symbol = string(data + 10, 6);
  exchtime_ = BCDToInt64(data, 6, 16);
  status_ |= (data[22]<<16)& 0xFF0000; 
  status_ |= (data[23]<<8)& 0xFF00; 
  status_ |= data[24] & 0xFF;
  total_volume_ = BCDToInt16(data, 4, 25);

  char status_1 = data[22];
  char status_2 = data[23];
  char status_3 = data[24];
  int offset = 29;
  // 若「揭示項目註記」第 7 Bit＝1 時，表示有成交價及成交量
  if ((status_1>>7) & 0b1) {
    last_price_ = IntToFloat(BCDToInt16(data, 5, offset), 4);
    if ((status_3>>3) & 0b1) open_ = last_price_; // 開盤
    offset += 5;
    if (status_2& 0b11){// 揭示最近一筆成交價，成交量則以 0 揭示，買賣價量均不揭示
      total_trade_ += 0;
    }else{ // 一般揭示
      total_trade_ += BCDToInt16(data, 4, offset);
    }
    offset += 4;
  }
  // 非最後一個成交價量揭示時，則僅揭示成交價量但不揭示最佳五檔，Bit 0 = 1
  if ((status_1 & 0b1)) return; 
  vector<float*> bid_prices = {&bid_price1_, &bid_price2_, &bid_price3_,
                             &bid_price4_, &bid_price5_};
  vector<int*> bid_volumes = {&bid_volume1_, &bid_volume2_, &bid_volume3_,
                              &bid_volume4_, &bid_volume5_};
  for (int i = 0; i < ((status_1 >> 4) & 0b111); ++i) {
    *(bid_prices[i]) = IntToFloat(BCDToInt16(data, 5, offset), 4);
    offset += 5;
    *(bid_volumes[i]) = BCDToInt16(data, 4, offset);
    offset += 4;
  }

  vector<float*> ask_prices = {&ask_price1_, &ask_price2_, &ask_price3_,
                             &ask_price4_, &ask_price5_};
  vector<int*> ask_volumes = {&ask_volume1_, &ask_volume2_, &ask_volume3_,
                              &ask_volume4_, &ask_volume5_};
  for (int i = 0; i < ((status_1 >> 1) & 0b111); ++i) {
    *(ask_prices[i]) = IntToFloat(BCDToInt16(data, 5, offset), 4);
    offset += 5;
    *(ask_volumes[i]) = BCDToInt16(data, 4, offset);
    offset += 4;
  }


}