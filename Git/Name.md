# 名付け方

## コミットメッセージ

### 何かを追加
- Add file
- Add function()

### 何かに対応した
- Add support

### 何かを削除
- Remove file

### 何かを使うようにした
- Use library

### 何かを～ないようにした
- Don't ~ ~

### コードを移動した
- Move source file to src

### 切り替えた
- Use A instead B
- Change A to C

### 改良した
- Improve calculation speed

### バグ関連
 - Fix typo
 - Fix memory leak
 - Fix wrong algorithm "hoge"

## ブランチ名
### 中央リポジトリ
#### master
完成品用．\
develop，hotfix へ分岐，\
release，hotfix からマージ．
#### develop
開発用．\
master から分岐，\
feature，release へ分岐，\
release へマージ．
### 開発リポジトリ
#### feature-*
新規機能開発用．\
developから分岐，\
developへマージ．
#### release-*
リリース用．\
developから分岐，\
masterへマージ．
#### hotfix-*
致命的バグ修正用．\
masterから分岐，\
masterへマージ．

---
*References*\
[gitにおけるコミットログ/メッセージ例文集100](https://anond.hatelabo.jp/20160725092419)\
[gitのブランチの名前の付け方 | Ninton](https://www.ninton.co.jp/archives/1287)\
[Git/GitHub branching standards & conventions](https://gist.github.com/digitaljhelms/4287848)
