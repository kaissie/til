
# Docker
コンテナ型の仮想環境を提供するソフトウェア<br>
Dockerイメージを使用することで，毎回同じ環境を作り出すことが可能<br>
VMと比較して軽い

## コマンド
### イメージ関連
#### ダウンロード
~~~
docker pull [オプション] イメージ名[:タグ]
~~~
#### 一覧表示
~~~
docker images
~~~
#### 削除
~~~
docker rmi イメージ名
~~~
### コンテナ関連
#### 生成・起動
~~~
docker run [オプション] イメージ名[:タグ] [引数]
~~~
コンテナを使い終わったら自動で削除
~~~
docker run --rm
~~~
コンテナとホスト間でファイルを共有
~~~
docker run -v [ホスト側のディレクトリパス]:[コンテナ内のディレクトリパス]
~~~
コンテナとホストの標準入出力をつなげる
~~~
docker run -it
~~~
#### 一覧表示
~~~
docker ps [オプション]
~~~
全てのコンテナの一覧表示
~~~
docker ps -a
~~~
#### 削除
~~~
docker rm コンテナID
~~~
