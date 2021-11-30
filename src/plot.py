import matplotlib
import matplotlib.pyplot as plt
from numpy import genfromtxt
import numpy

matplotlib.use('TkAgg')

values = genfromtxt("timings.csv", delimiter=',', usecols=(0,1,2))
averages = numpy.average(values,axis=0)

fig = plt.figure(figsize=(10,7))

labels = ['CPU', 'GPU cuBLAS','GPU cuBool']
# plt.boxplot(values, labels=['CPU', 'GPU cuBLAS','GPU cuBool'], widths=0.6)
plt.bar(labels, averages)
plt.yscale("log")
plt.gca().set_ylabel('time [μs]')

plt.show()