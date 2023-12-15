# UmaAssistant

## 文檔語言｜ドキュメント言語
<p align="center">
  <a href="./README.md">繁體中文</a>｜<a href="./README_jp.md">日本語</a>
</p>

## はじめに
このソフトは自動で DMM 版と BlueStacks エミュレータのウィンドウからウマ娘のイベントを検出し、可能な選択肢効果を与え、効果中のスキル詳細を与えます。

## 機能紹介
### イベント選択肢効果

### スキルプレビュー

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

### 使い方
### 0. プログラムを開く  
フォルダー内の`UmaAssistant.exe`を開いてください。  
![171217](https://github.com/kakuun333/UmaAssistant/assets/81919641/35dad315-a214-4908-a57d-f6807c8f7c87)  

### 1. 設定

> [!NOTE]
> 設定ファイルは`UmaMisc/config.json`に保存されます。


## 使用ライブラリ

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
