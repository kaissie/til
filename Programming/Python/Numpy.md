# NumPy

~~~python
import numpy as np
~~~

## 配列

`np.ndarray`

### 生成

`np.array()`関数によって`np.ndarray`を生成する．

~~~python
a = np.array([1, 2, 3])
b = np.array((10, 20, 30))
c = np.array([[1.5, 0], [0, 3.0]])
d = np.array([a, b])
~~~

`np.empty()`関数によって空の`np.darray`を生成する．

~~~python
np.empty(5)
~~~

`np.zeros()`関数によって0埋めされた`np.ndarray`を生成する．

```python
np.zeros(3)
```

`np.ones()`関数によって0埋めされた`np.ndarray`を生成する．

~~~python
np.ones((3, 4))
~~~

`np.identity()`関数によって単位行列を生成する．

~~~python
np.identity(4)
~~~



**参考文献**  
[機械学習の Python との出会い](http://www.kamishima.net/mlmpyja/)

