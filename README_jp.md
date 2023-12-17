# UmaAssistant

## 文檔語言｜ドキュメント言語
### [繁體中文](./README.md)｜[日本語](./README_jp.md)

## はじめに
このソフトは自動で DMM 版と BlueStacks エミュレータのウィンドウからウマ娘のイベントを検出し、可能な選択肢効果を与え、効果中のスキル詳細を見えるようにします。

## 機能紹介
### イベント選択肢効果  
![051248](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/051248.png)

### スキルプレビュー

#### 白スキル  
![051326](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/051326.png)  
#### 金スキル  
![052103](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/052103.png)  


## 稼働環境

### OSスペック
`Windows 10 64bit 22H2`
> [!WARNING]
> 32bit は実行できません。

### ファイルパス
`ファイルパスは半角英字でなければなりません。`
> [!NOTE]
> 正解：  
> `D:\UmaAssistant\UmaAssistant.exe`  
> 不正解：  
> `D:\うまウマ\UmaAssistant.exe`（仮名があります）  
> `D:\馬娘\UmaAssistant.exe`（漢字があります）  
> `D:\ＵｍａＡｓｓｉｓｔａｎｔ\UmaAssistant.exe` （全角英字があります）

### 必要なパッケージ
`Microsoft Visual C++ Redistributable Package`  
https://learn.microsoft.com/ja-jp/cpp/windows/latest-supported-vc-redist  
> [!IMPORTANT]
> アーキテクチャは`X64`を選んでください、ダウンロードしたファイル名は`vc_redist.x64.exe`のはずです。

## 使い方
### 0. ソフトを起動させる  
フォルダー内の`UmaAssistant.exe`を実行してください。  
![171217](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/exe_img.png)  

### 1. 設定
> [!NOTE]
> `UmaMisc/config.json`に設定ファイルが保存されます。

#### ソフトを日本語に変換する
まず「設定」をクリックします。  
![044407](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/083155.png)  
「ソフト言語」を日本語に変換します。  
![053013](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/053013.png)

#### 色んな設定
![072601](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/072601.png)

- ゲームサーバー：基本的に`日本`でOKです、`台湾・香港`は KOMOE TECHNOLOGY 株式会社が代理運営しているウマ娘のサーバーです。

- ウィンドウタイプ：DMM版は`DMM`で、エミュレータは`BlueStacks`にしか対応していません、フルスクリーンで遊ばないでください、文字検出ができなくなりますので。

- 検出した選択肢効果の言語(日本サーバーのみ)：基本的に`日本語`でOKです、`中国語（台湾）`は一部の選択肢効果とスキル詳細を中国語（台湾）に翻訳されます。

- スキャン間隔：一回スキャンした作業が終わった時から、次の作業を実行するまでの時間です、自分の`CPU`の性能に合わせて調整してください。

- ローカルサーバーポート番号：`localhost`の`port`です、基本的にデフォルトでOKです、必要な方は自分で調整したあと、ソフトを再起動してください。

- マウス連打：指定した`マウスボタン`をホールドすると、プログラムは`10ms`一回のスピードでマウスの左ボタンをクリックします、指定した`マウスボタン`を手放したら連打が中止されます。  
> [!IMPORTANT]
> マウス連打は`UmaAssistant.exe`を「管理者として実行」でなければなりません。

- 最前面に表示する：このソフトのウィンドウを最前面に表示されるようにする。

- デバッグログを記録する：デバッグログを`UmaTemp/UmaLog.txt`に出力します。ソフトを再起動するとこの前の`UmaLog.txt`がリセットされます、もし良ければバグ報告の時に、`UmaLog.txt`を付けると助かります。

- デバッグモード：開発者向けのモードです。


### 2. ゲームウィンドウを選ぶ  
「ウィンドウ選択」をクリックして、ゲームウィンドウと相応なものを選んだあと、赤い文字が緑の「ゲームウィンドウが見つけました」になるはずです。  
![053553](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/053553.png)


### 3. スキャンする  
![053930](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/053930.png)

### 4. 育成しているウマ娘を検出する  
> [!WARNING]
> 育成しているウマ娘を変えた際、必ずこの前検出したウマ娘を削除してください。  
> ![082441](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/082441.png)



右下の![option_button](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/option_button.png)をクリックして「編成情報」を選びます。  
![2](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/2.png)  
![3](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/tw_doc/3.png)  

`1~2`秒を待った後、「育成しているウマ娘」はアップデートされるはずです。  
アップデートされていない場合、[よくある質問](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%82%88%E3%81%8F%E3%81%82%E3%82%8B%E8%B3%AA%E5%95%8F)をご参照ください。  
![055347](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/jp_doc/055347.png)



## よくある質問
Q. なぜ`UmaAssistant.exe`は実行できないでしょうか？  
A.
1. [OSスペック](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#os%E3%82%B9%E3%83%9A%E3%83%83%E3%82%AF)が合っているかどうかを確認してください。
2. [ファイルパス](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%83%95%E3%82%A1%E3%82%A4%E3%83%AB%E3%83%91%E3%82%B9)が合っているかどうかを確認してください。
3. [必要なパッケージ](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E5%BF%85%E8%A6%81%E3%81%AA%E3%83%91%E3%83%83%E3%82%B1%E3%83%BC%E3%82%B8)がインストールされているかどうかを確認してください。  
![145447](https://raw.githubusercontent.com/kakuun333/UmaAssistant/assets/image/vc_redist.png)

Q. なぜ「育成しているウマ娘」或は「イベント」が検出できないでしょうか？  
A. 
1. 設定が合っているかどうかを確認してください。
2. ゲームウィンドウを選んだかどうかを確認してください。
3. ゲームウィンドウのサイズを拡大・縮小してみてください。
> [!NOTE]
> 上記の解決方法が効かなかった場合、十中八九`UmaData`のデータが不完全、あるいはプログラムに不具合が発生したのかもしれません。  
> もしバグを見つけた場合、このプロジェクトに貢ぎたいのだとしたら、[バグ報告](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%83%90%E3%82%B0%E5%A0%B1%E5%91%8A)をご参照していただけると幸いです。  

## バグ報告
イベントが検出できないバグ、育成しているウマ娘が検出できないバグ或はプログラムの不具合がありましたら  
[Issues](https://github.com/kakuun333/UmaAssistant/issues) に又は[コミュニティー](https://github.com/kakuun333/UmaAssistant/blob/main/README_jp.md#%E3%82%B3%E3%83%9F%E3%83%A5%E3%83%8B%E3%83%86%E3%82%A3%E3%83%BC)に提出していただけると助かります。  

## コミュニティー
著作者が運営している Discord サーバーがあります、このサーバーにソフトの最新情報を通知し、バグ報告を楽にするためにつくりました。  
**[Discord サーバーに入る](https://discord.gg/VQpYkWXYw2)**  
![Discord Banner 2](https://discordapp.com/api/guilds/1180922259146281053/widget.png?style=banner2)  

## 免責
- このソフトは`スキャン`を押した時に、使用者が指定した画面からスクリーンショットを撮ってゲーム内の文字を検出するに関わる作業がおこなわれます。これらに関する作業は個人情報などをとりません、作業を終えた直後にスクリーンショットが壊滅されます。  
- このソフトで何かの損失がありましたら、全て自己責任でお願いします。
- 著作者は続きのアップデートの責任を負いません。

## 著作権
Copyright (C) 2023 kakuun333  

## ライセンス
著作者が書いたソースコードは[GPL-3.0 license](https://github.com/kakuun333/UmaAssistant?tab=GPL-3.0-1-ov-file#)とします。  
`UmaData`フォルダー中のデータは著作者が書いたものではないものも含まれていますので、個人的な目的以外で利用することを禁止します。

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
