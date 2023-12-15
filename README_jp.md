# UmaAssistant

## 文檔語言｜ドキュメント言語
### [繁體中文](./README.md)｜[日本語](./README_jp.md)

## はじめに
このソフトは自動で DMM 版と BlueStacks エミュレータのウィンドウからウマ娘のイベントを検出し、可能な選択肢効果を与え、効果中のスキル詳細を与えます。

## 機能紹介
### イベント選択肢効果  
![051248](https://github.com/kakuun333/UmaAssistant/assets/81919641/f1cd2ae4-9147-4920-9422-7cab1882cd00)

### スキルプレビュー

#### 白スキル  
![051326](https://github.com/kakuun333/UmaAssistant/assets/81919641/f0ac239f-74da-4d60-843a-94c62a933520)  
#### 金スキル  
![052103](https://github.com/kakuun333/UmaAssistant/assets/81919641/456ca2e3-fd03-4693-9ad8-3beff15914d7)  


## 稼働環境

### OSスペック
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
> [!NOTE]
> `UmaMisc/config.json`に設定ファイルが保存されます。

#### ソフトを日本語に変換する
まず、「設定」をクリックします。  
![044407](https://github.com/kakuun333/UmaAssistant/assets/81919641/505abc27-60bd-4ad4-8f39-cbb948ffff79)  
「ソフト言語」を日本語に変換します。  
![053013](https://github.com/kakuun333/UmaAssistant/assets/81919641/35fd057d-9b34-4383-acda-52f1d5707529)

#### 色んな設定
![045450](https://github.com/kakuun333/UmaAssistant/assets/81919641/ea5f43f1-cfb4-43b6-990a-8cab4af6bad5)

### 2. ゲームウィンドウを選ぶ  
「ウィンドウ選択」をクリックして、ゲームウィンドウと相応なものを選んだあと、赤い文字が緑の「ゲームウィンドウが見つけました」になるはずです。  
![053553](https://github.com/kakuun333/UmaAssistant/assets/81919641/f4ad616b-de1d-4041-8609-e3eedaadb07f)


### 3. スキャンする  
![053930](https://github.com/kakuun333/UmaAssistant/assets/81919641/0ea9cbbe-b424-4e47-99ad-684f86660702)

### 4. 今育成しているウマ娘を探す  
右下の![option_button](https://github.com/kakuun333/UmaAssistant/assets/81919641/05802803-bdbb-4693-a0fe-be969ef93c87)をクリックして「編成情報」を選びます。  
![2](https://github.com/kakuun333/UmaAssistant/assets/81919641/3fbd26b7-b934-4c1c-9cbd-a03689066d71)  
![3](https://github.com/kakuun333/UmaAssistant/assets/81919641/b9173e1d-24cb-42b8-9e2c-647e69c03de4)  

`1~2`秒を待った後、「育成しているウマ娘」はアップデートされるはずです。  
アップデートされていない場合、[よくある質問](https://github.com/kakuun333/UmaAssistant#%E5%B8%B8%E8%A6%8B%E5%95%8F%E9%A1%8C)をご参照ください。  
![055347](https://github.com/kakuun333/UmaAssistant/assets/81919641/02eb6b40-6ccd-4d2f-9439-6a0582559c50)



## よくある質問
Q. なぜ`UmaAssistant.exe`は実行できないでしょうか？  
A.
1. [OSスペック](https://github.com/kakuun333/UmaAssistant?tab=readme-ov-file#%E7%B3%BB%E7%B5%B1%E8%A6%8F%E6%A0%BC)が合っているかどうかを確認してください。
2. [ファイルパス](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%83%91%E3%82%B9)が合っているかどうかを確認してください。
3. [必要なパッケージ](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E5%BF%85%E8%A6%81%E3%81%AA%E3%83%91%E3%83%83%E3%82%B1%E3%83%BC%E3%82%B8)がインストールされているかどうかを確認してください。  
![145447](https://github.com/kakuun333/UmaAssistant/assets/81919641/0d36b572-a610-40d3-8a75-39e80eb31203)

Q. なぜ「育成しているウマ娘」或は「イベント」が検出できないでしょうか？  
A. 
1. 設定の正しさをチェックしてください。
2. ゲームウィンドウを選んだかどうかをチェックしてください。
3. ゲームウィンドウのサイズを拡大・縮小してみてください。
> [!NOTE]
> 上記の解決方法が効かなかった場合、十中八九`UmaData`のデータが不完全、あるいはプログラムに不具合が発生したのかもしれません。  
> もしバグを見つけた場合、このプロジェクトに貢ぎたいのだとしたら、[バグ報告](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%83%90%E3%82%B0%E5%A0%B1%E5%91%8A)をご参照していただけると幸いです。  

## バグ報告
イベントが検出できないバグ、育成しているウマ娘が検出できないバグ或はプログラムの不具合がありましたら  
[Issues](https://github.com/kakuun333/UmaAssistant/issues) に提出していただけると助かります。  

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
