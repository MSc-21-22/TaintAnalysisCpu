import matplotlib
import matplotlib.pyplot as plt
from numpy import genfromtxt

matplotlib.use('TkAgg')

values = genfromtxt("timings.csv", delimiter=',', usecols=(0,1,2))
print(values)

fig = plt.figure(figsize=(10,7))

plt.boxplot(values, labels=['CPU', 'GPU cuBLAS','GPU cuBool'], widths=0.6)
plt.yscale("log")

plt.show()