# Electron

## Electronの仕組み
## 実行の仕組み
プロセスが**メインプロセス**と**レンダラープロセス**に分かれている．

##### console.logについて
console.logの出力はメインプロセスとレンダラープロセスで違う．
- メインプロセスはターミナル側
- レンダラプロセスはブラウザ側

### メインプロセス
package.json内のmainに指定されているjsファイル
~~~javascript
  "main" : "index.js",
~~~
上記の例では"index.jp"でメインプロセスが実行される．

Electronは1つのメインプロセスを持つ．\
メインプロセスが終了すると，アプリケーションも終了する．


### レンダラプロセス
名前の通り描画に関するプロセス．\
メインプロセスからいくつでも生成することができる．\
メインプロセスからhtmlファイルを読み込むと，レンダラプロセスが動作する．

### IPC
メインプロセスとレンダラプロセスはIPC(プロセス間通信)を使ってやり取りする．\
IPCはメインプロセスとレンダラプロセス間でしかできない．\
レンダラプロセス同士で通信したい場合，メインプロセスを経由する．

#### 非同期通信
main.js
~~~javascript
const {ipcMain} = require('electron')

ipcMain.on('asynchronous-message', (event, arg) => {
  console.log(arg)  // ping
  event.sender.send('asynchronous-reply', 'pong')
})
~~~
renderer.js
~~~javascript
const {ipcRenderer} = require('electron')

ipcRenderer.on('asynchronous-reply', (event, arg) => {
  console.log(arg) // pong
})
ipcRenderer.send('asynchronous-message', 'ping')
~~~

#### 同期通信

main.js
~~~javascript
const {ipcMain} = require('electron')

ipcMain.on('synchronous-message', (event, arg) => {
  console.log(arg)  // ping
  event.returnValue = 'pong'
})
~~~
renderer.js
~~~javascript
const {ipcRenderer} = require('electron')

console.log(ipcRenderer.sendSync('synchronous-message', 'ping')) // pong
~~~
---
参考文献\
[Electron APIデモから学ぶ実装テクニック ― ウィンドウ管理とメニュー - Build Insider](https://www.buildinsider.net/enterprise/electron/02)\
[Essential Electron : Electronの簡潔・平易な概要 | POSTD](https://postd.cc/essential-electron/#renderer-process)\
[Electronで最初に躓くメインプロセスとレンダラープロセスについて - Electron｜OAR STYLE](https://oar.st40.xyz/article/502)
