from sklearn import linear_model
from sklearn import datasets
import matplotlib.pyplot as plt
import numpy as np

# Load Data
iris = datasets.load_iris()
X = iris.data[:, :2]  # we only take the first two features.
y = iris.target

print(X)
print(y)

x_min, x_max = X[:, 0].min() - 0.5, X[:, 0].max() + 0.5
y_min, y_max = X[:, 1].min() - 0.5, X[:, 1].max() + 0.5

plt.figure(2, figsize=(8, 6))
plt.clf()

# Plot the training points
plt.xlabel("Sepal length")
plt.ylabel("Sepal width")

_X = [[], [], []]
_y = [[], [], []]
i = 0
for group in y:
    _X[group].append(X[i, 0])
    _y[group].append(X[i, 1])
    i += 1

for i in range(3):
    _X[i] = np.array(_X[i]).reshape(-1, 1)
    plt.scatter(_X[i][:-10], _y[i][:-10])
    reg = linear_model.LinearRegression()
    reg.fit(_X[i][:-10], _y[i][:-10])

    y_pred = reg.predict(_X[i])
    plt.plot(_X[i], y_pred)

plt.xlim(x_min, x_max)
plt.ylim(y_min, y_max)
plt.xticks(())
plt.yticks(())




plt.show()