#ifndef PARSE_TWSE_DATA_SRC_TWSE_DATA_FORMAT_H
#define PARSE_TWSE_DATA_SRC_TWSE_DATA_FORMAT_H

// relative header file
// C sys files
// C++ sys files
#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class TWSEDataHeader {
 public:
  int64_t GetCurrentTimeAsInt64();

  void ParseHeader(const char* buffer);
  int GetFormatId() const { return format_id_; }

  //  private:
  int format_id_;          // 資料格式代號
  int64_t localtime_ = 0;  // 本地接收資料時間點
  uint32_t sequence_;  // 每日由 1 開始依序編傳輸流水號，各格式獨立編號
  int32_t length_;         // 資料長度
  int32_t socket_id_ = 0;  // symbol_id ??
};

class TWSEDataBody {
 public:
  virtual void ParseBody(const char* buffer) = 0;
};

class TWSEDataBody1 : public TWSEDataBody {
 public:
  void ParseBody(const char* buffer);
  // protected:
  // private:
  std::string symbol_ = " ";  // 股票代號
  inline static std::map<std::string, float> previous_close_map_;  // 昨收價
  inline static std::map<std::string, float> high_limit_map_;      // 漲停價
  inline static std::map<std::string, float> low_limit_map_;       // 跌停價
};

class TWSEDataBody6 : public TWSEDataBody {
 public:
  void ParseBody(const char* buffer);
  int64_t FmtTimetoTimePoint(const char* data);

  //  private:
  std::string symbol_ = " ";  // 股票代號
  int64_t exchtime_;  // 普通股競價交易末筆即時行情資料搓合時間
  uint32_t status_ = 0;  // 揭示項目、漲跌停、狀態註記 bit_map
  // float last_price_ = 0;  // 最後成交價
  inline static std::map<std::string, int> last_price_map_;  // 最後成交價們
  // float open_ = 0;                                           // 開盤價
  inline static std::map<std::string, int> open_map_;  // 開盤價們
  int total_trade_ = 0;                                // 累計成交量
  // inline static std::map<std::string, int> total_trade_map_;  // 累計成交量們
  int total_volume_ = 0;  // 總成交量
  int total_value_ = 0;
  int average_ask_price_ = 0;   // 平均委賣價
  int average_bid_price_ = 0;   // 平均委買價
  int total_ask_volume_ = 0;  // 平均委賣量
  int total_bid_volume_ = 0;  // 平均委買量
  float ask_price1_ = 0;        // 第一檔委賣價
  float ask_price2_ = 0;        // 第二檔委賣價
  float ask_price3_ = 0;        // 第三檔委賣價
  float ask_price4_ = 0;        // 第四檔委賣價
  float ask_price5_ = 0;        // 第五檔委賣價
  int ask_volume1_ = 0;         // 第一檔委賣量
  int ask_volume2_ = 0;         // 第二檔委賣量
  int ask_volume3_ = 0;         // 第三檔委賣量
  int ask_volume4_ = 0;         // 第四檔委賣量
  int ask_volume5_ = 0;         // 第五檔委賣量
  float bid_price1_ = 0;        // 第一檔委買價
  float bid_price2_ = 0;        // 第二檔委買價
  float bid_price3_ = 0;        // 第三檔委買價
  float bid_price4_ = 0;        // 第四檔委買價
  float bid_price5_ = 0;        // 第五檔委買價
  int bid_volume1_ = 0;         // 第一檔委買量
  int bid_volume2_ = 0;         // 第二檔委買量
  int bid_volume3_ = 0;         // 第三檔委買量
  int bid_volume4_ = 0;         // 第四檔委買量
  int bid_volume5_ = 0;         // 第五檔委買量
};

struct TWSEData {
  std::unique_ptr<TWSEDataHeader> header;
  std::unique_ptr<TWSEDataBody> body;
};

#endif  // PARSE_TWSE_DATA_SRC_TWSE_DATA_FORMAT_H