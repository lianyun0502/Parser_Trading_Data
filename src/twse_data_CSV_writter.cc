// relative header file
#include "src/twse_data_CSV_writter.h"
// C sys files
// C++ sys files
#include <cstring>
#include <memory>
// other library header files
// project header files

using namespace std;

TWSEDataWritter::TWSEDataWritter(const string& filename) {
  ofs_.open(filename);
  if (!ofs_.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    exit(1);
  }
  ofs_
      << "symbol,symbol_id,exchtime,localtime,status,"
      << "last_price,previous_close,open,high_limit,low_limit,total_trade,"
         "total_volume,total_value,"
      << "average_ask_price,average_bid_price,total_ask_volume,total_bid_"
         "volume,"
      << "ask_price1,ask_volume1,bid_price1,bid_volume1,ask_price2,ask_volume2,"
         "bid_price2,bid_volume2,"
      << "ask_price3,ask_volume3,bid_price3,bid_volume3,ask_price4,ask_volume4,"
         "bid_price4,bid_volume4,"
      << "ask_price5,ask_volume5,bid_price5,bid_volume5,sequence\n";
}

TWSEDataWritter::~TWSEDataWritter() {
  ofs_.close();
  cout << "TWSEDataWritter is closed.\n";
}

void TWSEDataWritter::WriteTWSEData(const TWSEData& twse_data) {
  if (twse_data.header->GetFormatId() == 6) {
    header_ = twse_data.header.get();
    body_ = dynamic_cast<TWSEDataBody6*>(twse_data.body.get());
    if (body_ == nullptr) {
      cerr << "Failed to cast TWSEDataBody6." << endl;
      return;
    }
    ofs_ << body_->symbol_ << "," << header_->socket_id_ << ","
         << body_->exchtime_ << "," << header_->localtime_ << ","
         << body_->status_ << "," << body_->last_price_map_[body_->symbol_]
         << "," << TWSEDataBody1::previous_close_map_[body_->symbol_] << ","
         << body_->open_map_[body_->symbol_] << ","
         << TWSEDataBody1::high_limit_map_[body_->symbol_] << ","
         << TWSEDataBody1::low_limit_map_[body_->symbol_] << ","
         << body_->total_trade_ << "," << body_->total_volume_ << ","
         << body_->total_value_ << "," << body_->average_ask_price_ << ","
         << body_->average_bid_price_ << "," << body_->ask_price1_ << ","
         << body_->ask_volume1_ << "," << body_->bid_price1_ << ","
         << body_->bid_volume1_ << "," << body_->ask_price2_ << ","
         << body_->ask_volume2_ << "," << body_->bid_price2_ << ","
         << body_->bid_volume2_ << "," << body_->ask_price3_ << ","
         << body_->ask_volume3_ << "," << body_->bid_price3_ << ","
         << body_->bid_volume3_ << "," << body_->ask_price4_ << ","
         << body_->ask_volume4_ << "," << body_->bid_price4_ << ","
         << body_->bid_volume4_ << "," << body_->ask_price5_ << ","
         << body_->ask_volume5_ << "," << body_->bid_price5_ << ","
         << body_->bid_volume5_ << "," << header_->sequence_ << "\n";
  }
}