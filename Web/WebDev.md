# Web開発環境

## Node.js

サーバーサイドJavaScript環境

## nodist

Node.jsのバージョン管理ツール

## ECMAScript

JavaScriptの標準規格
独自拡張によって増えすぎたJavaScriptを標準化するために生まれた

## Babel

ECMAScriptコンパイラ
ECMAScriptに対応していないブラウザのために，旧仕様にコンパイルする

プロジェクトフォルダ直下で実行

~~~
npm install --save @babel/core @babel/cli @babel/preset-env
~~~

babelの設定ファイル`babel.config.js`を作成する
作成したファイルに以下のコード記述する

~~~javascript
const presets = [
  [
    "@babel/env",
  ],
];

module.exports = { presets };
~~~



ソースファイル用に`src`フォルダ，
コンパイルしたファイル用に`dist`フォルダを作成する

babelでコンパイルするコマンド

~~~
 .\\node_modules\\.bin\\babel src --out-dir dist
~~~

`package.json`にコンパイルコマンドを登録する

~~~javascript
  "scripts": {
    "build": ".\\node_modules\\.bin\\babel src --out-dir dist"
  },
~~~

登録したコマンドの実行

~~~javascript
npm run build
~~~

コンパイルしたスクリプトを実行

~~~
node dist/hogehoge.js
~~~



