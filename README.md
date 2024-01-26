<p align="center">
  <img src="https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/uma_icon_64px.png">
  <h1 align="center">UmaAssistant</h1>
</p>

## 文檔語言｜ドキュメント言語
### [繁體中文](./README.md)｜[日本語](./README_jp.md)

## 社群
### 作者有為這個專案運營一個 Discord 伺服器，在這個伺服器裡會第一時間通知本軟體的最新資訊、也可以在這個伺服器裡輕鬆地提交問題回報。  
### **[加入 Discord 伺服器](https://discord.gg/JzT5fpjarM)**  
![Discord Banner 2](https://discordapp.com/api/guilds/1180922259146281053/widget.png?style=banner2)  

## 簡介
**本軟體會自動辨識 DMM 版、各大模擬器視窗中賽馬娘的事件，並給予可能的選項效果、提供選項效果中技能的詳細資訊。**

## 功能介紹
### 事件選項效果
![1](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1.png)
![1009](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1009.png)
![1010](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1010.png)

### 技能預覽
#### 白技能  
![2](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/2.png)
![998](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/998.png)
![1002](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1002.png)
![1005](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1005.png)
![1006](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1006.png)

#### 金技能  
![3](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/3.png)
![1003](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1003.png)
![1004](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1004.png)

### 劇本數值＋圖示  
![17](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/17.png)

## 運作環境

### 系統規格
`Windows 10 64位元 22H2`  
`Windows 11 64位元 23H2`  
其他 Windows 版本沒有測試過，說不定可以使用。
> [!WARNING]
> 32 位元無法運行。

### 檔案路徑
`檔案路徑只能是半形英文`
> [!NOTE]
> 正確示範：  
> `D:\UmaAssistant\UmaAssistant.exe`  
> 錯誤示範：  
> `D:\うまうま\UmaAssistant.exe`（不可以有日文假名）  
> `D:\馬娘\UmaAssistant.exe`（不可以有中文字）  
> `D:\ＵｍａＡｓｓｉｓｔａｎｔ\UmaAssistant.exe` （不可以有全形英文）

### 必須安裝的套件  
`Microsoft Visual C++ Redistributable Package`  
https://learn.microsoft.com/zh-tw/cpp/windows/latest-supported-vc-redist
> [!IMPORTANT]
> 架構請選擇`X64`，下載到的安裝檔名稱應該要是`vc_redist.x64.exe`。

## 使用方法
### 0. 開啟程式  
開啟資料夾中的`UmaAssistant.exe`  
![exe_img](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/exe_img.png)  

### 1. 設定  
![4](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/4.png)  
![5](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/5.png)  


> [!NOTE]
> 設定檔將保存在`UmaMisc/config.json`。

- 軟體語言：本軟體`UI`的語言。

- 遊戲伺服器：請選擇適當的遊戲伺服器，選錯遊戲伺服器將無法辨識事件。

- 視窗類型：DMM版請選`DMM`，模擬器目前支援`BlueStacks`、`夜神模擬器`、`雷電模擬器`，模擬器請不要使用全螢幕遊玩，解析度比例必須為`16:9`，否則將無法辨識事件。

- 日服文本語言（只有在伺服器是`日服`的時候有效果）：決定了辨識到事件後給予的事件效果的語言，想看全日文選`日文`，想看繁體中文選`繁體中文`，繁體中文不會全部內容都是繁體中文，因為那樣會造成混亂。

- 辨識事件間隔時間：辨識完一次事件以後，要辨識下一次事件前所需等待的時間，請根據自己電腦`CPU`性能做調整。

- 本地伺服器埠口：`localhost`的`port`，如果你不知道這是什麼的話則不須改動，如果你有需要請自行改動後重開程式。

- 滑鼠連點：按住指定的`滑鼠按鍵`會以`10毫秒`一次的速度點擊滑鼠左鍵，鬆開後停止連點。  
> [!IMPORTANT]
> 滑鼠連點需要以系統管理員身分執行`UmaAssistant.exe`才會有效果。

- 顯示在最上層：讓程式的視窗一直保持在最上層。

- Discord RPC：更新`Discord`的遊戲狀態為`賽馬娘 Pretty Derby`或`ウマ娘 プリティーダービー`  
> [!NOTE]
> **Discord RPC**
> `遊戲名稱`和`馬娘的名字`會根據所選的`遊戲伺服器`發生變化  
> `馬娘的名字`會根據`目前培育的馬娘`發生變化  
> 其他文字會根據`軟體語言`發生變化
> Discord RPC 只會在`已找到遊戲視窗`時更新
> ![1008](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1008.png)  
> ![1011](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/1011.png)  

- Debug模式：基本上只給開發者做使用。

- 輸出偵錯日誌：開啟後會把日誌輸出到`UmaTemp/UmaLog.txt`，每一次啟動程式都會刪除上一個`UmaLog.txt`，如果你願意的話可以勾選此選項，遇到問題要回報時可以附上`UmaLog.txt`，這樣可以更好地判斷問題出在哪裡。

### 2. 選取遊戲視窗  
按下「選取視窗」，選擇對應的遊戲視窗名稱，之後應該要看到「已找到遊戲視窗」。
![6](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/6.png)

### 3. 啟動事件辨識  
![7](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/7.png)

### 4. 尋找目前培育的馬娘  
> [!NOTE]
> 如果方法一和方法二皆無效的話請使用[方法三：直接選擇角色](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E6%96%B9%E6%B3%95%E4%B8%89)來尋找`目前培育的馬娘`。

> [!WARNING]
> 更換培育的馬娘時，請務必先清除先前的馬娘。  
> 如果使用[方法三：直接選擇角色](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E6%96%B9%E6%B3%95%E4%B8%89)則不需要清除先前的馬娘。  
> ![8](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/8.png)


#### 方法一：適用於還沒開始培育的情況

在配置支援卡的畫面按下「育成開始！」等待`1~2`秒後「目前培育的馬娘」應該要更新為「最終確認」所顯示的馬娘名稱，如果沒有更新的話，請參考[常見問題](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E5%B8%B8%E8%A6%8B%E5%95%8F%E9%A1%8C)  
![9](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/9.png)  
![10](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/10.png)  

#### 方法二：適用於已經開始培育的情況

按右下角的![option_button](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/option_button.png)後，選擇「編成情報」，等待`1~2`秒後「目前培育的馬娘」應該要更新為「編成情報」所顯示的馬娘名稱，如果沒有更新的話，請參考[常見問題](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E5%B8%B8%E8%A6%8B%E5%95%8F%E9%A1%8C)  
![11](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/11.png)  
![12](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/12.png)  
![13](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/13.png)  

#### 方法三：直接選擇角色
> [!NOTE]
> 1. 不需要先清除角色。  
> 2. 點選角色圖示後角色名稱會依照選擇的遊戲伺服器發生變化。  
> 3. 遊戲伺服器選擇繁中服並且點選繁中服沒有的角色「目前培育的馬娘」會直接變空白。  

**開啟選擇角色**  
![14](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/14.png)  

**點選正在培育的馬娘**  
如果成功匹配的話「目前培育的馬娘」將會更新成對應的角色名稱。
![15](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/15.png)  

**查詢**  
查詢功能支援`繁體中文`、`平假名`、`片假名`。  
如果角色的別名有`英文`、`數字`、`標點符號`的話也可以用來查詢。  
![16](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/16.png)  




## 常見問題
Q. 為什麼我的`UmaAssistant.exe`無法啟動？  
A.
1. 請確定[系統規格](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E7%B3%BB%E7%B5%B1%E8%A6%8F%E6%A0%BC)符合上述標準。
2. 請確定[檔案路徑](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E6%AA%94%E6%A1%88%E8%B7%AF%E5%BE%91)符合上述標準。
3. 請確定電腦上已經安裝了[必須安裝的套件](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E5%BF%85%E9%A0%88%E5%AE%89%E8%A3%9D%E7%9A%84%E5%A5%97%E4%BB%B6)  
![vc_redist](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/vc_redist.png)

Q. 為什麼我無法辨識「目前培育的馬娘」或「事件」？  
A. 
1. 請檢查設定是否正確。
2. 請檢查是否選取了對應的視窗名稱。
3. 請檢查「目前培育的馬娘」是否為現在培育的馬娘。
4. 應用程式縮放的百分比必須為`100%`，`滑鼠右鍵 -> 顯示設定 -> 縮放與版面配置`  
  ![10000](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/10000.png)

> [!NOTE]
> 如果上述的方法皆無效果，有大概率是`UmaData`中的資料不完整或程式的邏輯有疏失，請參考[問題回報](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E5%95%8F%E9%A1%8C%E5%9B%9E%E5%A0%B1)。  

Q. 為什麼我的程式資料夾無法刪除？（資料夾中的檔案已在其他程式開啟）  
A. 可能是因為程式崩潰導致字型沒有被程式正確卸載，只要重新啟動電腦就可以刪除了。  

## 問題回報
有任何問題請到 **[Issues](https://github.com/kakuun333/UmaAssistant/issues)** 或者 **[社群](https://github.com/kakuun333/UmaAssistant/blob/main/README.md#%E7%A4%BE%E7%BE%A4)** 中回報，非常感謝！  

## 免責聲明
- 本軟體只在按下`啟動`時對使用者指定的視窗做截圖和遊戲事件、遊戲角色相關的辨識操作之後立即銷毀指定視窗的截圖，並且此類操作不會收集任何個人資訊。  
- 因使用本軟體而造成任何類型的損失全部歸於個人責任，作者不負任何責任。
- 作者不負任何本軟體後續更新的責任。


## 版權聲明
Copyright (C) 2023 kakuun333  

## 授權
作者編寫的原始碼全部屬於[GPL-3.0 license](https://github.com/kakuun333/UmaAssistant?tab=GPL-3.0-1-ov-file#)  
`UmaData`資料夾中的資料只允許用於個人用途，不允許用於商業或其他性質的用途。  

## 使用的函式庫

### C++
- Tesseract OCR  
https://github.com/tesseract-ocr/tesseract

- OpenCV  
https://opencv.org/

- nlohmann - JSON for Modern C++  
https://github.com/nlohmann/json

- curl    
https://curl.se


- The Programming Language Lua  
https://www.lua.org

### Lua
- dkjson - JSON Module for Lua  
http://dkolf.de/src/dkjson-lua.fsl/home

### Python
- Selenium  
https://www.selenium.dev
