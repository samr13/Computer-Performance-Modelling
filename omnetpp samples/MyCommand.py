import matplotlib.pyplot as plt
import csv
import pandas as pd
import numpy as np
import os
#os.system("tail 26jobs.csv -n 10000 | cut -d ',' -f 2 | awk '{s+=$1} END {print s}' | cat >> sumsOfJobs.csv;")
#for i in range(26,37):
	#os.system("tail "+str(i)+"jobs.csv -n 10000 | cut -d ',' -f 2 | awk '{s+=$1} END {print s}' | cat >> sumsOfJobs.csv;")


#os.system("tail 26jobs.csv -n 10000 | cut -d ',' -f 2 | awk '{s+=$1} END {print s}' | cat >> sumsOfJobs.csv;")
for i in range(70,96):
	if(i%2 == 0):
		os.system("tail "+str(i)+"outputClosed.txt -n 10000 | cut -d ',' -f 2 | awk '{s+=$1} END {print s}' ;")
