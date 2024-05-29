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
3. 執行以下指令即可執行程式
   ```bash
    ./bin/main
    ```
4. 生成的csv檔案同樣會在 ```bin```目錄下

 

