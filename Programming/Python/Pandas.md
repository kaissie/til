# Pandas
### モジュールの読み込み

~~~python
import pandas as pd
~~~
## 基本

### シリーズ

> Series is a one-dimensional labeled array capable of holding any data  type (integers, strings, floating point numbers, Python objects, etc.).  The axis labels are collectively referred to as the index. 

１次元のデータ構造

~~~python
series = pd.Series([1.0, 1.2, 3.4, 4.1, 8.2], index = ['d1', 'd2', 'd3', 'd4', 'd5'])
~~~

### データフレーム

>DataFrame is a 2-dimensional labeled data structure with columns of  potentially different types. You can think of it like a spreadsheet or  SQL table, or a dict of Series objects. It is generally the most  commonly used pandas object. 

2次元のデータ構造

~~~python
df = pd.DataFrame({'A': [1.0, 1.2, 3.4, 4.1, 8.2],
                   'B': [0.8, 1.4, 3.2, 4.3, 7.9],
                   'C': [1.3, 1.4, 2.9, 3.8, 9.4]},
                   index = ['d1', 'd2', 'd3', 'd4', 'd5'])
~~~

`index`オプションは省略可（0番から添え字が割り当てられる）

~~~python
s1 = pd.Series([80, 50, 60, 70, 90], index=['Japanese', 'math', 'science', 'society', 'English'])
s2 = pd.Series({'Japanese': 80, 'math': 50, 'science': 60, 'society': 70, 'English': 90})
df1 = pd.DataFrame([s1, s2], index=['Taro', 'Jiro'])
df1
#       English  Japanese  math  science  society
# Taro       90        80    50       60       70
# Jiro       90        80    50       60       70

df2 = pd.DataFrame({'Taro': s1, 'Jiro': s2})
df2
#           Jiro  Taro
# English     90    90
# Japanese    80    80
# math        50    50
# science     60    60
# society     70    70
~~~



## ファイルの入出力
### CSVファイルの読み込み

CSVファイルをデータフレームとして読み込む

~~~python
df = pd.read_csv("data.csv", sep=',', comment='#')
~~~

- `sep`：区切り文字を指定
- `comment`：コメント文字を指定

## データの確認

### 行項目

~~~python
df.index
~~~

### 列項目

~~~python
df.columns
~~~

### 行数・列数

~~~python
df.shape
~~~

### 各列のデータ型

~~~python
df.dtypes
~~~

### 先頭

~~~python
df.head()
~~~

### 最後尾

~~~python
df.tail()
~~~

### 任意の列

~~~python
df[['A','B']].head()
~~~

### 任意の行

~~~python
# 100行目から106行目まで
df[100:106]
~~~

~~~python
# 100行目のみ
df.loc[100]
~~~

`loc`はインデックスでアクセスする

### 任意の行と列

~~~python
# 1,2,4行目と0,2列目を取得
df.iloc[[1,2,4],[0,2]]
~~~

`iloc`メソッドは添え字でアクセスできる

### 条件を満たすデータ

~~~python
df[df['A'] > 1.0]
~~~

### 複数の条件を満たすデータ

~~~python
df[['name', 'kcal']].query('kcal > 450 and name == "豚肉の生姜焼"')
~~~

### ユニークな要素の値のリスト

~~~python
df['name'].unique()
~~~

### 要約統計量の表示

~~~python
df.describe()
~~~

## データの整形

### ある列をインデックスにする

~~~python
df.set_index('date',inplace=True)
~~~

### カラム名を変更する

~~~python
# yをsalesに変更
df.rename(columns={'y':'sales'}, inplace=True)
~~~

### ある列の値でソートする

~~~python
df.sort_values(by="sales", ascending=True) # ascending=Trueで昇順
~~~

~~~python
# 複数の列も指定できる
df.sort_values(by=["sales", 'temperature'], ascending=False) # ascending=Falseで降順
~~~

### 値のデータ型を変換する

~~~python
# indexであるdatetimeのdtype='object' を dtype='datetime64[ns]' に変更
df.index = pd.to_datetime(df.index, format='%Y-%m-%d')
~~~

## データの欠損状態の確認

~~~python
# 列単位で 欠損値NaN(not a number)が入っている個数をカウントする
#（正確には、isnull()でtrueが返ってくる個数をカウントしている）
df.isnull().sum()
~~~

~~~python
# 1つでもNaNが含まれる行だけを抽出（最初の5行のみ表示）
df[df.isnull().any(axis=1)].head()
~~~

## 欠損の修正

~~~python
df.fillna(value={'payday': 0.0}, inplace=True)
~~~

~~~python
# 'kcal'列にNaNがある行を削除する
df.dropna(subset=['kcal'], axis=0, inplace=True)
~~~

~~~python
# 'precipitation' 列の '--' を 0に置き換える
df['precipitation'] = df['precipitation'].str.replace('--', 0).astype(float)
~~~

~~~python
# maskメソッドを使う例。'sales'列が80よりも大きければ、その値を100に置換する
pd.DataFrame(df['sales'].mask(df['sales'] > 80, 100)).head()
~~~

~~~python
# 'remarks(備考)'はデータとして不要な気がするので、データから列ごと削除
df.drop(['remarks'], axis=1, inplace=True)
~~~

## 集計

~~~python
# weather列の集計
df['weather'].value_counts()
~~~

~~~python
# groupbyメソッドで、'week'列ごとに'soldout'の数をカウントする
df.groupby(['week'])['soldout'].count()
~~~

~~~python
# groupbyメソッドで、'month', 'period'列ごとに'sales'の数を合計する
df.groupby(['month', 'period'])['sales'].sum()
~~~

~~~python
# wetherごとにtemperatureの平均値を出す
df.groupby(['weather'])['temperature'].mean()
~~~

~~~python
# 前行との差分が欲しい時は .diff() を使う
df['temperature_diff'] = df['temperature'].diff(periods=1)
~~~

~~~python
# 'temperature'列について、頭からwindowサイズ3で移動平均を計算する
df['temperature_rolling_mean'] = df['temperature'].rolling(window=3).mean()
~~~

## ダミー変数

`pandas.get_dummies`でダミー化したデータフレームを取得できる．

~~~python
import pandas as pd
name = pd.Series(['Alice','Bob', 'Carol', 'Dave'])
sex =  pd.Series(['female','male', 'female', 'male'])
df = pd.DataFrame({ 'Name':name, 'Sex':sex})
~~~

~~~python
pd.get_dummies(df.Sex)
~~~

|      | femle | male |
| ---- | :---- | ---- |
| 0    | 1     | 0    |
| 1    | 0     | 1    |
| 2    | 1     | 0    |
| 3    | 0     | 1    |

**参考文献**  
[データ分析で頻出のPandas基本操作](https://qiita.com/ysdyt/items/9ccca82fc5b504e7913a)  
[pandasに関する情報 | note.nkmk.me](https://note.nkmk.me/pandas/)

## マルチインデックス

~~~
学習日         正誤
2020-02-06  1     0.550
            0     0.450
2020-02-08  1     0.575
            0     0.425
2020-02-11  1     0.575
            0     0.425
2020-02-13  1     0.600
            0     0.400
2020-02-14  1     0.650
            0     0.350
~~~

このような形になっているデータのことを**マルチインデックス**と呼ぶ．

ここで，正誤が "1" のときの値だけ取り出したいとき，このデータが`df`というデータフレームに入っていたとすると

~~~python
df.loc[:,1]
~~~

で取り出すことが出来る．

### 任意の行・列を選択，抽出

`loc[]`を使うことで任意の行・列を選択，抽出することができる．

上の階層から順にカンマ区切りで指定していく．

- 1列目のインデックスが`x`である行を指定したい場合，`loc[x]`
- 2列目のインデックスが`x`である行を指定したい場合，`loc[:,x]`
- 1列目が`x`，2列目が`y`である行を指定したい場合，`loc[x,y]`
- スライスも使うことが出来る，`loc[0:5,x]`

**参考文献**   
[pandasのMultiIndexから任意の行・列を選択、抽出 | note.nkmk.me](https://note.nkmk.me/python-pandas-multiindex-indexing/)