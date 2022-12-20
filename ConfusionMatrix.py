import numpy as np
from sklearn.metrics import confusion_matrix
from numpy import genfromtxt

raakaData = genfromtxt('putty.log', delimiter=',')

y_true = raakaData[:,0]
y_pred = raakaData[:,1]
print(confusion_matrix(y_true, y_pred))