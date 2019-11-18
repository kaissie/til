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

train = pd.read_csv("titanic/train.csv")
test = pd.read_csv("titanic/test.csv")

train["Age"] = train["Age"].fillna(train["Age"].median())
train["Embarked"] = train["Embarked"].fillna("S")

test["Age"] = test["Age"].fillna(test["Age"].median())
test["Fare"] = test["Fare"].fillna(test["Fare"].median())

train['Sex'] = train['Sex'].apply(lambda x: 1 if x == 'male' else 0)
train['Embarked'] = train['Embarked'].map( {'S': 0 , 'C':1 , 'Q':2}).astype(int)

test['Sex'] = test['Sex'].apply(lambda x: 1 if x == 'male' else 0)
test['Embarked'] = test['Embarked'].map( {'S': 0 , 'C':1 , 'Q':2}).astype(int)
# -

train_y = train.Survived
train_X = train.drop(['Survived','PassengerId','Name','Ticket','Cabin'],axis = 1)
(train_X, test_X ,train_y, test_y) = train_test_split(train_X, train_y, test_size = 0.3, random_state = 666)

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
X_train = train_X.as_matrix()
y_train  = train_y.as_matrix()

X_test = test_X.as_matrix()
y_test  = test_y.as_matrix()
# -

mgc_forest.fit(X_train , y_train)

# +
y_pred = mgc_forest.predict(X_test)

print('Prediction shape:', y_pred.shape)
print(
    'Accuracy:', accuracy_score(y_test, y_pred),
    'F1 score:', f1_score(y_test, y_pred, average='weighted')
)
# -


