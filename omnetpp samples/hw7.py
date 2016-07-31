#%matplotlib inline
import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np

#plt.plot([1,2,3,4], [1,4,9,16], 'ro')
#plt.axis([0, 6, 0, 20])
#plt.show()

mySum = 0
myLength = 0

#simTimeList = []
#responseTimeList = []
#with open('movingAverageOutput.csv', 'rb') as csvfile:
	#reader = csv.DictReader(csvfile)
	#for row in reader:
		##mySum += float(row['responseTime'])
		##myLength += 1
		#simTimeList.append(row['responseTime'])
		#responseTimeList.append(row['responseTime'])


closedPlot = pd.read_csv("closedTimed.txt", names=['simTime', 'responseTime', 'proxy', 'router', 'originA', 'originB'])
print("closed has", len(closedPlot.index), "rows")

#print closedPlot[-5:]

#print closedPlot['simTime']
#myDf.columns=['x','sin(x)','cos(x)']
#myPlot = closedPlot.plot(x='simTime',y= 'responseTime')
#myPlot.set_xlabel("Sim Time")
#myPlot.set_ylabel("Response Time")

#plt.plot(simTimeList,responseTimeLists, 'ro')



#myPlot = closedPlot.plot(x='simTime',y= 'proxy')
#myPlot = closedPlot.plot(x='simTime',y= 'router')
#myPlot = closedPlot.plot(x='simTime',y= 'originA',ylim=(0,1.1))
myPlot = closedPlot.plot(x='simTime',y= 'originB')

plt.show()
plt.plot([1, 2, 3, 4], [1, 4, 9, 16])


#print mySum
#print myLength
#print "The average is : " + str(mySum/myLength)
		
