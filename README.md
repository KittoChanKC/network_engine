# Network Engine (Base)

## 概要
自分のゲームでネットワークが使いたいので、ネットワークを書き始めました。
最終的な目標はネットワークエンジンになりたいと思います。  

TCPというプロトコルを使ってます

Visual Studio 2019とC++17で作っています。

プロジェクトはGit、cmake、vcpkgで管理しています。

## ビルド
`@fullBuiild.bat` を実行するとvcpkgで必要なライブラリをインストールします。  
`@open.bat`を実行するとプロジェクトを生成します。自動的にVisual Studio 2019で開きます。（お勧め）  
`@make.bat`を実行するとプロジェクトを生成します  

始めては先に`@fullBuiild.bat` を実行して必要なライブラリをインストール  
後は`@open.bat`を実行してプロジェクトを生成します。

## 開発概要 / 機能
 - TCP 
 - Socket
 - Client
 - Server
 - Package

## 使い方
 - `NetworkLib/include`のファイルをインクルード
    - BaseClient  
    - BaseServer  
    - BaseConnection   
  それぞれ対応のGameCliect, GameServerクラス（たとえ）を作ってベースクラス継承して、簡単に使えます。
  
  - `NetworkLib/GameApp/` は 簡単なサンプルです。

## 開発/勉強予定
 - Gateway