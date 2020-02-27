# Unity Script

## 動作

### 移動

- transform.Translate(0f, 0f, 0.1f)
  - 引数の値ずつ移動
- transform.position
  - 現在地を取得（代入できる） => ワープに使える

### 生成

- Instantiate(hogeObject, Vector3.zero, Quaternion.identity)
  - クローンを中心に無回転で配置する
- 

## 測定

### 距離

- Vector3.Distance(Hoge,Foo);



## 操作

### キー入力

- Input.GetKey(KeyCode.Hoge)
  - キーが押されている時
- Input.GetKeyDown(KeyCode.Hoge)
  - キーが押された瞬間
- KeyCode
  - KeyCode.(Up|Down|Right|Left)Arrow
  - KeyCode.[A-Z]

## 衝突

### 関数

- void OnCollisionEnter(Collision collision)
  - 衝突時に呼び出される
- void OnCollisionExit(Collision collision)
  - 離れた時に呼び出される
- void OnCollisionStay(Collision collision)
  - 触れている間呼び出される
- void OnTriggerEnter(Collider other)
  - 重なった瞬間呼び出される
- void OnTriggerExit(Collider other)
  - 重ならなくなった瞬間呼び出される
- void OnTriggerEnter(Collider other)
  - 重なっている間呼び出される

## 検索

- GameObject.Find("hogehoge")
  - アクティブなオブジェクトを検索
  - 重い
- <parenthoge>.transform.Find("childhoge")
  - 自身の子オブジェクト（非アクティブオブジェクト含む）を検索
- gameObject.GetComponent<T> ()
  - オブジェクトの持っているコンポーネント（スクリプト）にアクセスできる。（Tはコンポーネント名）
## シーン
  using UnityEngine.SceneManagement
 - SceneManager.LoadScene("hogeScene")
   - シーンを読み込む
