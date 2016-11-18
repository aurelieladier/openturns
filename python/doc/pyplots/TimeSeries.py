import openturns as ot
from matplotlib import pyplot as plt
from openturns.viewer import View


# Create a bivariate normal process
myTG = ot.RegularGrid(0.0, 0.01, 100)
myCov = ot.ExponentialModel([3.0], [1.2])
myProcess = ot.TemporalNormalProcess(myCov, myTG)

myTS = myProcess.getRealization()

graph = myTS.drawMarginal(0)

fig = plt.figure(figsize=(8, 4))
plt.suptitle("A time series")
axis = fig.add_subplot(111)
axis.set_xlim(auto=True)

View(graph, figure=fig, axes=[axis], add_legend=True)
