# Web開発環境

## Node.js

サーバーサイドJavaScript環境

## nodist

Node.jsのバージョン管理ツール

## ECMAScript

JavaScriptの標準規格<br>
独自拡張によって増えすぎたJavaScriptを標準化するために生まれた

## Babel

ECMAScriptコンパイラ<br>
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

## Sass
"Syntactically Awesome StyleSheet"<br>
CSSのメタ言語（CSSを拡張して書きやすくした言語）<br>
Sassで書かれたものをCSSにコンパイルして使う
### SASS記法
インデント構文で書かれたSass<br>
Sassと混乱しやすい，Sassがこちらを示している場合もある．
~~~sass
$blue: #3bbfce
$margin: 16px

.content-navigation
  border-color: $blue
  color: darken($blue, 10%)

.border
  padding: $margin/2
  margin:  $margin/2
  border-color: $blue
~~~
### SCSS記法
CSSのように波括弧とセミコロンで書かれたSass<br>
SASSよりも新しいがこちらのほうが主流？
~~~scss
$blue: #3bbfce;
$margin: 16px;

.content-navigation {
  border-color: $blue;
  color: darken($blue, 10%);
}

.border {
  padding: $margin / 2;
  margin: $margin / 2;
  border-color: $blue;
}
~~~
