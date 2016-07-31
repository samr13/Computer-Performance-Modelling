import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
import os
import scipy.stats as stats
#tail *jobs.csv -n 1 | cat > allLastRows.csv


testingVar = [1,2,3,4,5]
#print stats.variation(testingVar)

i = 26
closedPlot = pd.read_csv(str(i)+"jobs.csv", names=['simTime', 'responseTime', 'proxy', 'router', 'originA', 'originB'])
print(closedPlot[0][-5:])

os.system('ls')

for i in range (26,37):
	

jobIndices = range(26,37)
listOfResponse = []
i = 0
with open('sumsOfJobs.csv', 'rb') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		print(str(row['responseTime']) + " " + str(jobIndices[i]))
		listOfResponse.append(float(row['responseTime'])/10000)
		i+=1
		

plt.plot(jobIndices, listOfResponse)

plt.xlabel('Number of Jobs')
plt.ylabel('Response Time')
plt.show()

#jobIndices = []
#for i in range(70,96):
	#if(i%2 == 0):
		#jobIndices.append(i)


#hw 7 jobs question


#listOfResponse = []
#i = 0
#with open('sumsOfHitRates.csv', 'rb') as csvfile:
	#reader = csv.DictReader(csvfile)
	#for row in reader:
		#print(str(row['responseTime']) + " " + str(jobIndices[i]))
		#listOfResponse.append(float(row['responseTime'])/10000)
		#i+=1
		

#plt.plot(jobIndices, listOfResponse)

#plt.xlabel('Hit Rate')
#plt.ylabel('Response Time')
#plt.show()



#problem 1
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



print variations

#plt.xlabel('simTime')
#plt.ylabel('router Average Util')
#plt.show()


plt.plot(myTimeList,variations)
plt.xlabel('simTime Batches')
plt.ylabel('router Util Variation')

plt.show()

			#print x
		#listOfResponse.append(float(row['responseTime'])/10000)
		
		

#plt.plot(jobIndices, listOfResponse)

#plt.xlabel('Hit Rate')
#plt.ylabel('Response Time')
#plt.show()




#for i in range (0,5):
#	print listofLast5[i]

