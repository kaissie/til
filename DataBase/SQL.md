# SQL

RDBMSにおいて，データの操作や定義を行うためのデータベース言語

## 文法

### データ定義言語

- CREATE（データベースオブジェクトの定義）
- DROP（データベースオブジェクトの削除）
- ALTER（データベースオブジェクトの定義変更）

### データ操作言語

- INSERT INTO（行・表データの挿入）

  ~~~sql
  INSERT INTO 表名(列名1,列名2) VALUES(値1,値2)
  ~~~

- UPDATE ~ SET（表を更新）

  ~~~sql
  UPDATE 表名
   SET 列名2=値2, 列名3=値3
   WHERE 列名1=値1
  ~~~

- DELETE FROM（表から特定の行を削除）

  ~~~sql
  DELETE FROM 表名
   WHERE 列名1=値1
  ~~~

- SELECT ~ FROM ~ WHERE（表データの検索，結果集合の取り出し）

  ~~~sql
  SELECT *
   FROM 表名
   WHERE 列名1 BETWEEN 値1 AND 値2
   ORDER BY 列名1
  ~~~

  

  ### データ制御言語

  - GRANT（特定のデータベース利用者に特定の作業を行う権限を与える）
  - REVOKE（特定のデータベース利用者からすでに与えた権限を剥奪する）
  - LOCK（表などの資源を占有する）

