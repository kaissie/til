import numpy as np
from matplotlib import pyplot

def err_func(output, test):
    return np.linalg.norm(test - output)
    # return np.linalg.norm(np.square(test - output))

class NN():

    def __init__(self,n_i,n_o,lr,mu = 0):
        self.w = np.random.randn(n_o,n_i)
        #self.w = np.random.random_sample((n_o,n_i))
        self.o_m =  np.zeros((n_o, n_i))

        self.inputs  = None
        self.outputs = None
        self.lr = lr
        self.mu = mu

    def sigmoid(self, x):
        y = 1 / (1 + np.exp(-x))
        return y

    def sigmoid_derivative(self, x):
        y = 1 - self.sigmoid(x) * self.sigmoid(x)
        return y

    def train(self, target_inputs, target_output):

        hidden_outputs = np.dot(self.w,target_inputs.reshape(-1,1))
        final_output = self.sigmoid(hidden_outputs)

        output_error = target_output - final_output


        delta_w = self.lr * output_error * self.sigmoid_derivative(hidden_outputs)
        self.w = self.w + delta_w


    def forward(self, inputs):
        self.inputs = np.dot(self.w,inputs.reshape(-1,1))
        self.outputs = self.sigmoid(self.inputs)
        return self.outputs

    def backward(self, output_error):
        delta_w = self.lr * output_error * self.sigmoid_derivative(self.inputs)
        # print(self.lr *output_error, self.sigmoid_derivative(self.inputs))
        # delta_w = self.lr * np.dot(output_error, self.sigmoid_derivative(self.inputs))
        self.w = self.w + delta_w + self.mu * self.o_m
        self.o_m = delta_w
        return delta_w


    def predict(self, inputs):
        return self.forward(inputs)

def test1():
    nn = NN(4,1,0.5)

    target_inputs = np.array([0.2, -0.5, 0.1, 0.7])
    target_outputs = np.array(0.777)
    epoch  = 1000

    for iteration in range(epoch):
        #nn.train(target_inputs,target_outputs)
        nn.backward(err_func(nn.forward(target_inputs),target_outputs))

    print(nn.predict(np.array([0.2, -0.5, 0.1, 0.7])))

def test2():
    n1 = NN(4,4,0.1)
    n2 = NN(4,1,0.1)
    idata = np.array([[0.2, -0.5, 0.1, 0.7]])
    tdata = np.array([0.777])
    epoch = 1000
    error = np.zeros(epoch)
    for e in range(epoch):
        for (i, t) in zip(idata, tdata):
            out = n2.forward(n1.forward(i))
            err = err_func(out, t)
            error[e] = err
            if e % 100 == 0:
                print("err : {}".format(err))
            n1.backward(n2.backward(err))

    for (i, t) in zip(idata, tdata):
            out = n2.forward(n1.forward(i))
            print(out)
    pyplot.ylim(0.0, 2.0)
    pyplot.plot(np.arange(0, error.shape[0]), error)
    pyplot.show()

def test3():
    n1 = NN(3,2,0.1,0.9)
    n2 = NN(2,2,0.1,0.9)
    idata = np.array([[1,0, 0], [1,0, 1], [1,1, 0], [1,1, 1]])
    tdata = np.array([[1, 0], [0, 1], [0, 1], [1, 0]])
    epoch = 10000
    error = np.zeros(epoch)
    for e in range(epoch):
        err = -1
        for (i, t) in zip(idata, tdata):
            out = n2.forward(n1.forward(i))
            err += err_func(out, t)

            # if e % 100 == 0:
            #     print("err : {}".format(err))
        err /= len(idata)
        error[e] = err
        n1.backward(n2.backward(err))

    for (i, t) in zip(idata, tdata):
            out = n2.forward(n1.forward(i))
            print(out)
    pyplot.ylim(0.0, 2.0)
    pyplot.plot(np.arange(0, error.shape[0]), error)
    pyplot.show()
def test4():
    # トレーニングデータのロード
    training_data_file = open('mnist_dataset/mnist_train.csv', 'r')
    training_data_list = training_data_file.readlines()
    training_data_file.close()

    # テストデータのロード
    test_data_file = open('mnist_dataset/mnist_test.csv')
    test_data_list = test_data_file.readlines()
    test_data_file.close()

    n1 = NN(784,100,0.3)
    n2 = NN(100, 10, 0.3)


if __name__ == "__main__":
    test1()
    # test2()
