# Parser_Trading_Data
解析台灣證券交易所行情資料

撰寫一個轉檔程式,能將從交易所獲得的逐筆資料(binary)轉成明文的文字檔(csv),提供的資料如下:
* 臺灣證券交易所資訊傳輸作業手冊(IP 行情網路)
* 逐筆資料壓縮檔: twse_20230808.tar.gz
* 範例文字檔: twse_20230808.csv (輸出的欄位需跟此範例一模一樣)

主要解析的是手冊中的格式六,但輸出格式中有些數據也會使用到其他格
式(格式一)。

## 專案環境

* 編譯器版本: GCC 11.4.0 86_64-linux-gnu
* CMake版本: 3.16.3
* 操作系統: Ubuntu 20.04.3 LTS
* 語言: C++17

## 專案架構
``` 
PARSER_TRADING_DATA/
├── src/
│   ├── main.cc
│   ├── utilities.cc
│   ├── utilities.h
│   └── ...
├── CMakeLists.txt
└── README.md
```

## 使用CMake構建專案
```bash
mkdir build
cd build
cmake ..
make
```
## 編譯方式

## 執行方式

