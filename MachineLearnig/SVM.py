import pprint
import numpy as np

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def SVM(data):
    # データ数
    N = len(data)
    # 次元数
    d = 3
    # データセット
    X = data[:,0:3]
    # 分類サインの配列
    T = np.array([1 if l == 0 else - 1 for l in data[:,4]])
    
    alpha = np.zeros(N) # ラグランジュ未定乗数
    beta = 1.0          # 最急降下法のステップ幅
    
    eta_al = 0.0001 # alphaの更新レート
    eta_be = 0.1    # betaの更新レート

    # 繰り返し回数
    itr = 1000
    
    # 最急降下法でマージンを最大化
    for _itr in range(itr):
        for i in range(N):
            delta = 1 - (T[i] * X[i]).dot(alpha * T * X.T).sum() - beta * T[i] * alpha.dot(T)
            alpha[i] += eta_al * delta
        for i in range(N):
            beta += eta_be * alpha.dot(T) ** 2 / 2

    # 求まったラグランジュ未定乗数よりwとbを計算
    index = alpha > 0
    w = (alpha * T).T.dot(X)
    b = (T[index] - X[index].dot(w)).mean()

    # グラフに描画
    fig = plt.figure()
    ax = Axes3D(fig)    
    y = [-1 if (w.T*x).sum()+b < 0 else 1 for x in X]
    ax.scatter(X[:,0], X[:,1], X[:,2], s=4, c=y, cmap='jet')
    ax.set_xlabel("Sepal Length")
    ax.set_ylabel("Sepal Width")
    ax.set_zlabel("Petal Length")
    plt.show()

def load_iris():
    a = np.loadtxt('iris.csv', delimiter=',', skiprows=1)
    return a


def main():    
    data = load_iris()
    SVM(data)


if __name__ == "__main__":
    main()
