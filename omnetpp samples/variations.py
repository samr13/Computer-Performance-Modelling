import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
import os
import scipy.stats as stats
listOfResponse = []
i = 1
x = 100*i
hundredSec = 1
average = 0
mySum = 0

routerSum = 0
proxySum = 0
originASum = 0
originBSum = 0
length = 0

routerAverages = []
proxyAverages = []
originAAverages = []
originBAverages = []
timeList = []
#timeList.append(100)
with open('output.txt', 'rb') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		length += 1
		#print row
		#print(str(row['responseTime']))
		proxySum += float(row['proxy'])
		routerSum += float(row['router'])
		originASum += float(row['originA'])
		originBSum += float(row['originB'])
		if((float(row['simTime'])>x)):
			routerAverages.append(proxySum/length)
			proxyAverages.append(routerSum/length)
			originAAverages.append(originASum/length)
			originBAverages.append(originBSum/length )
			
			routerSum = 0
			proxySum = 0
			originASum = 0
			originBSum = 0
			length = 0
			timeList.append(x)
			i = i +1
			x = i*100
		if x > 10000:
			break;
			#print i
			#print x


#for 
#print len(timeList)
#print len(routerAverages)

#plt.plot(timeList,routerAverages)
varList = []
i = 1
variations = []

myTimeList = []
#timeList
for average in routerAverages:
	varList.append(average)
	if i%(10)==0:
		variations.append(stats.variation(varList))
		varList = []
		myTimeList.append(i*100)
	i += 1


plt.plot(myTimeList,variations)
plt.xlabel('simTime Batches')
plt.ylabel('router Util Variation')

plt.show()
