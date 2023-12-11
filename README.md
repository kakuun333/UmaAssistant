# UmaAssistant

## 文檔語言｜ドキュメント言語
<p align="center">
  <a href="./README.md">繁體中文</a> |
  <a href="./README_jp.md">日本語</a>
</p>

## 簡介
本軟體會自動辨識 DMM 版、BlueStacks 模擬器視窗中賽馬娘的事件，並給予可能的選項效果、提供選項效果中技能的詳細資訊。

## 功能介紹
### 事件選項效果
![052953](https://github.com/kakuun333/UmaAssistant/assets/81919641/27ca31f8-8f27-499e-ab3f-8a3b3b70c40a)
### 技能預覽
- 白技能  
![053007](https://github.com/kakuun333/UmaAssistant/assets/81919641/33f1f0ad-58b8-42a3-9232-22a019686354)
- 金技能  
![065204](https://github.com/kakuun333/UmaAssistant/assets/81919641/7b5bec42-0325-4710-af0b-45e12b23c05d)

## 運作環境

### 系統規格
`Windows 10 64位元 22H2`
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

## 常見問題
Q. 為什麼我的`UmaAssistant.exe`無法啟動？  
A.
1. 請確定[系統規格](https://github.com/kakuun333/UmaAssistant?tab=readme-ov-file#%E7%B3%BB%E7%B5%B1%E8%A6%8F%E6%A0%BC)符合上述標準。
2. 請確定[檔案路徑](https://github.com/kakuun333/UmaAssistant#%E6%AA%94%E6%A1%88%E8%B7%AF%E5%BE%91)符合上述標準。
3. 請確定電腦上已經安裝了[必須安裝的套件](https://github.com/kakuun333/UmaAssistant#%E5%BF%85%E9%A0%88%E5%AE%89%E8%A3%9D%E7%9A%84%E5%A5%97%E4%BB%B6)  
![145447](https://github.com/kakuun333/UmaAssistant/assets/81919641/0d36b572-a610-40d3-8a75-39e80eb31203)

Q. 為什麼我無法辨識「目前培育的馬娘」？  
A. 請檢查設定是否正確、嘗試縮放遊戲視窗。  

Q. 為什麼我無法辨識事件？  
A. 請檢查設定是否正確、嘗試縮放遊戲視窗。  

## 使用方法
### 1. 設定  
![040744](https://github.com/kakuun333/UmaAssistant/assets/81919641/3bf289f9-b097-4270-a922-4b28d9d7e295)
> [!NOTE]
> 設定檔將保存在`UmaMisc\config.json`。

![044407](https://github.com/kakuun333/UmaAssistant/assets/81919641/505abc27-60bd-4ad4-8f39-cbb948ffff79)

#### 伺服器
請選擇適當的伺服器，選錯伺服器將無法辨識事件。

- 視窗類型：DMM版請選`DMM`，模擬器目前只支援`BlueStacks`，模擬器請不要使用全螢幕遊玩，否則將無法辨識事件。
- 日服文本語言（只有在伺服器是`日服`的時候有效果）：決定了辨識到事件後給予的事件效果的語言，想看全日文選`日文`，想看繁體中文選`繁體中文`，繁體中文不會全部內容都是繁體中文，因為那樣會造成混亂。
- 辨識事件間隔時間：辨識完一次事件以後，要辨識下一次事件前所需等待的時間，請根據自己電腦`CPU`性能做調整。  
- 本地伺服器埠口：`localhost`的`port`，如果你不知道這是什麼的話則不須改動，如果你有需要請自行改動後重開程式。
- 滑鼠連點：按住指定的`滑鼠按鍵`會高速連點滑鼠左鍵，鬆開後停止連點。  
> [!IMPORTANT]
> 滑鼠連點需要以系統管理員身分執行`UmaAssistant.exe`才會有效果。

- 顯示在最上層：讓程式的視窗一直保持在最上層。  

### 2. 選取遊戲視窗  
按下「選取視窗」，選擇對應的遊戲視窗名稱，之後應該要看到「已找到遊戲視窗」。
![1](https://github.com/kakuun333/UmaAssistant/assets/81919641/39438b25-0ce2-4863-9bc1-72155a0704f6)

### 3. 啟動事件辨識  
![0](https://github.com/kakuun333/UmaAssistant/assets/81919641/2a936e17-8f0c-4007-97b4-8b4c2614f28b)

### 4. 尋找目前培育的馬娘  
> [!WARNING]
> 更換培育的馬娘時，請務必先清除先前的馬娘。  
> ![065617](https://github.com/kakuun333/UmaAssistant/assets/81919641/5dd14128-ff69-449e-af8a-4592bae91de1)

按右下角的![option_button](https://github.com/kakuun333/UmaAssistant/assets/81919641/05802803-bdbb-4693-a0fe-be969ef93c87)後，選擇「編成情報」，等待`1~2`秒後「目前培育的馬娘」應該要更新為「編成情報」所顯示的馬娘名稱，如果沒有更新的話，請嘗試縮放遊戲視窗。  
![2](https://github.com/kakuun333/UmaAssistant/assets/81919641/3fbd26b7-b934-4c1c-9cbd-a03689066d71)  
![3](https://github.com/kakuun333/UmaAssistant/assets/81919641/b9173e1d-24cb-42b8-9e2c-647e69c03de4)  
![4](https://github.com/kakuun333/UmaAssistant/assets/81919641/47bd9b44-7d26-46fb-bdda-75e0ebbab2c7)  


## 免責聲明
- 本軟體只在按下`啟動`時進行特定視窗的截圖操作和遊戲事件、遊戲角色相關的辨識操作之後立即銷毀特定視窗的截圖，並且此類操作不會收集任何個人資訊。  
- 因使用本軟體而造成任何類型的損失全部歸於個人責任，作者不負任何責任。
- 作者不負任何本軟體後續更新的責任。

## 問題回報
有任何問題請到`Issue`或是下方`Discord`伺服器中提出。  
![Discord Banner 4](https://discordapp.com/api/guilds/1180922259146281053/widget.png?style=banner4)


## 使用的函式庫

### C++
- Tesseract OCR  
https://github.com/tesseract-ocr/tesseract

- OpenCV  
https://opencv.org/

- JSON for Modern C++  
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
