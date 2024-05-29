// relative header file
#include "src/twse_data_parser.h"
// C sys files
// C++ sys files
#include <cstring>
#include <memory>
// other library header files
// project header files

using namespace std;

bool TWSEDataParser::IsEnd() { return is_end_; }

TWSEDataParser::TWSEDataParser(const string& filename) {
  ifs_.open(filename, std::ios::in | std::ios::binary);
  if (!ifs_.is_open()) {
    std::cerr << "Failed to open file." << std::endl;
    exit(1);
  }
}

TWSEDataParser::~TWSEDataParser() { 
  ifs_.close();
  cout << "TWSEDataParser is closed.\n"; 
  }

bool TWSEDataParser::GetTWSEData(TWSEData& twse_data) {
  if (ifs_.eof()) {
    is_end_ = true;
    return false;
  }

  bzero(len_buf_, sizeof(len_buf_));
  bzero(read_buf_, sizeof(read_buf_));

  ifs_.read(read_buf_, sizeof(read_buf_));
  if (read_buf_[0] != 0x1b) return false;

  esc_code_pos_ = ifs_.tellg();

  ifs_.read(len_buf_, sizeof(len_buf_));
  // ShowHex(len_buf_, 2);
  int len = BCDToInt16(len_buf_, 2);
  if (len < 13) {
    cout << "len is less than 13.\n";
    ShowHexPosition(esc_code_pos_);
    ifs_.seekg(esc_code_pos_);
    return false;
  }
  char data_buf[len - 3];
  bzero(data_buf, sizeof(data_buf));
  ifs_.read(data_buf, len - 3);
  if (ifs_.gcount() != len - 3) {
    cout << "EOF.\n";
    ShowHexPosition(esc_code_pos_);
    is_end_ = true;
    return false;
  }
  if (data_buf[len - 5] != 0x0D && data_buf[len - 4] != 0x0A) {
    cout << "termainal code not match \n";
    ShowHexPosition(esc_code_pos_);
    ifs_.seekg(esc_code_pos_);
    return false;
  }
  checksum_ = CalculateXOR(len_buf_, data_buf, len - 6);
  if (data_buf[len - 6] != checksum_) {
    cout << "checksum not match! data=" << (int)data_buf[len - 6]
         << " res=" << (int)checksum_ << "\n";
    ShowHexPosition(esc_code_pos_);
    ifs_.seekg(esc_code_pos_);
    return false;
  }
  char data_seq[len] = {0};
  data_seq[0] = 0x1b;
  memcpy(data_seq + 1, len_buf_, 2);
  memcpy(data_seq + 3, data_buf, len - 3);

  TWSEData data;

  auto header_ptr = make_unique<TWSEDataHeader>();
  // TWSEDataHeader header;
  header_ptr->ParseHeader(data_seq);
  twse_data.header = move(header_ptr);
  if (twse_data.header->GetFormatId() == 6) {
    // TWSEDataBody6 body;
    auto body_ptr = make_unique<TWSEDataBody6>();
    body_ptr->ParseBody(data_seq);
    twse_data.body = move(body_ptr);
  } else if (twse_data.header->GetFormatId() == 1) {
    // TWSEDataBody1 body;
    auto body_ptr = make_unique<TWSEDataBody1>();
    body_ptr->ParseBody(data_seq);
    twse_data.body = move(body_ptr);
  } else {
    return false;
  }
  ShowHexPosition(esc_code_pos_);
  cout << "len: " << len << endl;
  // ShowHex(data_buf, len - 3);
  cout << "======================" << endl;

  return true;
}