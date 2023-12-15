# UmaAssistant

## 文檔語言｜ドキュメント言語
<p align="center">
  <a href="./README.md">繁體中文</a>｜<a href="./README_jp.md">日本語</a>
</p>

## はじめに
> [!IMPORTANT]
> # ※このソフトは現在、UIの言語が日本語に対応されていないのですが、主な内容は日本語です。

このソフトは自動で DMM 版と BlueStacks エミュレータのウィンドウからウマ娘のイベントを検出し、可能な選択肢効果を与え、効果中のスキル詳細を与えます。

## 機能紹介
### イベント選択肢効果
![052953](https://github.com/kakuun333/UmaAssistant/assets/81919641/27ca31f8-8f27-499e-ab3f-8a3b3b70c40a)  

### スキルプレビュー

#### 白スキル  
![053007](https://github.com/kakuun333/UmaAssistant/assets/81919641/33f1f0ad-58b8-42a3-9232-22a019686354)
#### 金スキル  
![065204](https://github.com/kakuun333/UmaAssistant/assets/81919641/7b5bec42-0325-4710-af0b-45e12b23c05d)


## 稼働環境
`Window 10 64bit 22H2`
> [!WARNING]
> 32bit は実行できません。

### ファイルパス
`ファイルパスは半角英字でなければなりません。`
> [!NOTE]
> 正解：  
> `D:\UmaAssistant\UmaAssistant.exe`  
> 不正解：  
> `D:\うまうま\UmaAssistant.exe`（仮名があります）  
> `D:\馬娘\UmaAssistant.exe`（漢字があります）  
> `D:\ＵｍａＡｓｓｉｓｔａｎｔ\UmaAssistant.exe` （全角英字があります）

### 必要なパッケージ
`Microsoft Visual C++ Redistributable Package`  
https://learn.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist  
> [!IMPORTANT]
> アーキテクチャは`X64`を選んでください、ダウンロードしたファイル名は`vc_redist.x64.exe`のはずです。

## 使い方
### 0. ソフトを起動させる  
フォルダー内の`UmaAssistant.exe`を開いてください。  
![171217](https://github.com/kakuun333/UmaAssistant/assets/81919641/35dad315-a214-4908-a57d-f6807c8f7c87)  

### 1. 設定

### 2. ゲームウィンドウを選ぶ  
「選取視窗」をクリックして、ゲームウィンドウと相応なものを選んだあと、赤い文字が緑の「已找到遊戲視窗」になるはずです。
![1](https://github.com/kakuun333/UmaAssistant/assets/81919641/39438b25-0ce2-4863-9bc1-72155a0704f6)

### 3. スキャンを開始する  
![0](https://github.com/kakuun333/UmaAssistant/assets/81919641/2a936e17-8f0c-4007-97b4-8b4c2614f28b)

### 4. 今育成しているウマ娘を探す  
……

> [!NOTE]
> 設定ファイルは`UmaMisc/config.json`に保存されます。


## 使用したライブラリ

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
