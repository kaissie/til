# -*- coding: utf-8 -*-
# ---
# jupyter:
#   jupytext:
#     formats: ipynb,py
#     text_representation:
#       extension: .py
#       format_name: light
#       format_version: '1.4'
#       jupytext_version: 1.2.4
#   kernelspec:
#     display_name: Python 3
#     language: python
#     name: python3
# ---

# +
import pandas as pd
import numpy as np

from sklearn.datasets import fetch_mldata
from sklearn.ensemble import ExtraTreesClassifier, RandomForestClassifier
from sklearn.metrics import accuracy_score, f1_score
from sklearn.model_selection import train_test_split

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
# -

train = pd.read_csv('mnist/train.csv',header=None)
test = pd.read_csv('mnist/test.csv',header=None)

# +
train_y = train[0]
train_X = train.drop(0,axis = 1)
test_y = test[0]
test_X = test.drop(0,axis = 1)

train_X = train_X[:1000]
train_y = train_y[:1000]
test_X = test_X
test_y = test_y
# -

# ## Decision Tree Classifier

from sklearn.tree import DecisionTreeClassifier
dec_tree = DecisionTreeClassifier()
dec_tree = dec_tree.fit(train_X , train_y)

# +
y_pred = dec_tree.predict(test_X)

print(
    'Accuracy:', accuracy_score(test_y, y_pred),
    'F1 score:', f1_score(test_y, y_pred, average='weighted')
)
# -

# ## Random Forest

from sklearn.ensemble import RandomForestClassifier
rnd_forest = RandomForestClassifier()
rnd_forest = rnd_forest.fit(train_X , train_y)

# +
y_pred = rnd_forest.predict(test_X)

print(
    'Accuracy:', accuracy_score(test_y, y_pred),
    'F1 score:', f1_score(test_y, y_pred, average='weighted')
)
# -

# ## Deep Forest

# +
from deep_forest.deep_forest import MGCForest
import random
import uuid

from sklearn.datasets import fetch_mldata
from sklearn.ensemble import ExtraTreesClassifier, RandomForestClassifier
from sklearn.metrics import accuracy_score, f1_score
from sklearn.model_selection import train_test_split
mgc_forest = MGCForest(
    estimators_config={
        'mgs': [{
            'estimator_class': ExtraTreesClassifier,
            'estimator_params': {
                'n_estimators': 30,
                'min_samples_split': 21,
                'n_jobs': -1,
            }
        }, {
            'estimator_class': RandomForestClassifier,
            'estimator_params': {
                'n_estimators': 30,
                'min_samples_split': 21,
                'n_jobs': -1,
            }
        }],
        'cascade': [{
            'estimator_class': ExtraTreesClassifier,
            'estimator_params': {
                'n_estimators': 1000,
                'min_samples_split': 11,
                'max_features': 1,
                'n_jobs': -1,
            }
        }, {
            'estimator_class': ExtraTreesClassifier,
            'estimator_params': {
                'n_estimators': 1000,
                'min_samples_split': 11,
                'max_features': 'sqrt',
                'n_jobs': -1,
            }
        }, {
            'estimator_class': RandomForestClassifier,
            'estimator_params': {
                'n_estimators': 1000,
                'min_samples_split': 11,
                'max_features': 1,
                'n_jobs': -1,
            }
        }, {
            'estimator_class': RandomForestClassifier,
            'estimator_params': {
                'n_estimators': 1000,
                'min_samples_split': 11,
                'max_features': 'sqrt',
                'n_jobs': -1,
            }
        }]
    },
    stride_ratios=[1.0 / 4, 1.0 / 9, 1.0 / 16],
)

# +
X_train, y_train = train_X.as_matrix(), train_y.as_matrix()
X_test, y_test = test_X.as_matrix(), test_y.as_matrix()


X_train = X_train.reshape((len(X_train), 28, 28))
X_test = X_test.reshape((len(X_test), 28, 28))


print('X_train:', X_train.shape, X_train.dtype)
print('y_train:', y_train.shape, y_train.dtype)
print('X_test:', X_test.shape)
print('y_test:', y_test.shape)
# -

# ### 学習

# + {"jupyter": {"outputs_hidden": true}}
mgc_forest.fit(X_train, y_train)
# -

# ### 予測

# +
y_pred = mgc_forest.predict(X_test)

print('Prediction shape:', y_pred.shape)
print(
    'Accuracy:', accuracy_score(y_test, y_pred),
    'F1 score:', f1_score(y_test, y_pred, average='weighted')
)
# -


