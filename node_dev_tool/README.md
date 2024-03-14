

# 開発時に使用するツールなど

## node version
`20.11.0`

## install
`npm install`

### Windows は sharp が動作しなかったので @img/sharp-win32-x64 を入れた。
`npm install --force @img/sharp-win32-x64`

### スクリプト

#### ヘッダーのマクロの命名規則チェック、デストラクタの virtual 抜けチェック
`npm run checkfile`


#### ビットマップ画像のコード化
`npm run img`
画像のヘッダーソース化に sharp を使用。


#### Arduino 用に書き出し
`npm run arduino`

