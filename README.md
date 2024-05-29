# Parser_Trading_Data
解析台灣證券交易所行情資料

撰寫一個轉檔程式,能將從交易所獲得的逐筆資料(binary)轉成明文的文字檔(csv),提供的資料如下:
* 臺灣證券交易所資訊傳輸作業手冊(IP 行情網路)
* 逐筆資料壓縮檔: twse_20230808.tar.gz
* 範例文字檔: twse_20230808.csv (輸出的欄位需跟此範例一模一樣)

主要解析的是手冊中的格式六,但輸出格式中有些數據也會使用到其他格式(格式一)。

## 專案環境

* 編譯器版本: GCC 11.4.0 86_64-linux-gnu
* CMake版本: 3.16.3
* 操作系統: Ubuntu 20.04.3 LTS
* 語言: C++20

## 專案目錄架構
``` 
PARSER_TRADING_DATA/
├── include/ # header files
│   ├── twse_data_format.h
│   ├── utilities.h
│   └── ...
├── src/ # source files
│   ├── twse_data_format.cc
│   ├── utilities.cc
│   └── ...
├── main.cc
├── CMakeLists.txt
└── README.md
```

## 使用CMake構建專案

本專案使用環境為Ubuntu 20.04.3 LTS,並使用CMake v3.16.3構建專案，請確保您的環境中已安裝CMake，以下為構建專案的步驟

1. clone專案
    ```bash
    git clone https://github.com/lianyun0502/Parser_Trading_Data.git
    ```
2. 進入專案資料夾創建build目錄並進入

    ```bash
    mkdir build
    cd build
    ```

3. 使用CMake構建專案
    ```bash
    cmake ..
    ```


## 編譯方式

CMake專案構建完畢後,在```build```目錄下執行以下指令進行編譯

```bash
make
```

成功會看到以下訊息
```bash
[main] 正在建置資料夾: Parser_Trading_Data 
[build] 正在啟動建置
[proc] 正在執行命令: /usr/bin/cmake --build /home/lianyun/桌面/Parser_Trading_Data/build --config Debug --target all -j 6 --
[build] Consolidate compiler generated dependencies of target main
[build] [ 16%] Building CXX object CMakeFiles/main.dir/src/twse_data_parser.cc.o
[build] [ 33%] Building CXX object CMakeFiles/main.dir/main.cc.o
[build] [ 50%] Linking CXX executable ../bin/main
[build] [100%] Built target main
[driver] 建置已完成: 00:00:01.660
[build] 建置已完成。結束代碼: 0
```

## 執行方式

1. 編譯完成後會將執行檔放在 ```bin```目錄下
2. 將要解析的行情資料BIN檔 ```twse_20230808.bin``` 放在 ```bin```目錄下
3. 執行以下指令即可執行程式，執行檔可以輸入參數，**不想使用預設的檔案則兩個參數都要輸入**
    * 參數一 [輸入文件] 預設為 ```twse_20230808.bin```
    * 參數二 [輸入文件] 預設為 ```twse_20230808.csv```

   ```bash
    ./bin/main [輸入文件] [輸出文件]
    ```
4. 生成的csv檔案同樣會在 ```bin```目錄下

 
## 其他

1. 需求裡提到sequence number的型別是int16_t，但是我使用了uint16_t避免流水號大於32767會變成負數的問題
2. 需求裡的header的localtime不知道要用什麼，所以就用了解析行情時當下的時間點寫入
3. 證交所說明文件裡格式一與行情資料解析出來的格式有點不符合，解析資料如下
    ```bash
    // 某筆台積電解析的格式一資料
    1b 01 14 01 01 09 00 02 70 51 32 33 33 30 20 20 
    a5 78 bf 6e b9 71 20 20 20 20 20 20 20 20 20 20 
    32 34 20 20 20 20 00 30 00 05 58 00 00 00 06 13 
    00 00 00 05 03 00 00 20 20 20 41 59 59 00 00 00 
    20 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
    00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
    00 00 00 00 00 00 00 20 00 10 00 20 20 20 01 d1 
    0d 0a 
    ```
    * 說明文件上指出格式一的總長度為 113 bytes，但是解析出來的總長度為 114 bytes
    * 說明文件上指出在位置[39-39]的資料為"股票異常代碼 "，是 PACK BCD 的資料且應為 "00"~"07"，但是解析出來的資料為 "30"，懷疑這裡就是多的那個byte
    * 同上，會發現為置[40]以後的資料都必須後移一個byte，才能符合格式一的規範

        
