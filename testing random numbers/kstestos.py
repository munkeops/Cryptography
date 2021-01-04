import random
from pprint import pprint
import pandas as pd
import numpy as np

randomlist = []

def maximum(a, b): 
      
    if a >= b: 
        return a 
    else: 
        return b 

def kstest(randmat,up,down):
    
    results=[]
    for i in range(len(randmat)):
        k=np.array([m+1 for m in range(len(randmat[0]))])
        k1=np.array([m for m in range(len(randmat[0]))])

        table=[]

        y=randmat[i]

        y.sort()
        # print(y)
        yarr=np.array(y)
        # print(yarr)
        # fnk1=[(z-1)/len(k) for z in k]
        fnk1=(k1)/len(y)

        # fnk=[(z)/len(k) for z in k]
        fnk=k/len(y)

        # f0=[y0/(up-down) for y0 in y]
        f0=yarr/(up-down)

        fn0=abs(fnk1-f0)
        f0n=abs(f0-fnk)
        # print(f0n)
        max1=np.amax(fn0)
        max2=np.amax(f0n)
        # print(max1)
        result=maximum(max1,max2)
        table.append(y)
        table.append(fnk1)
        table.append(f0)
        table.append(fnk)
        table.append(fn0)
        table.append(f0n)
        # print(table)
        table=np.array(table).T
        df = pd.DataFrame(table,columns=["y","Fn(k-1)","F0(y)","Fn(k)","|Fn(k-1)-F0|","|F0-Fn(k)|"])  
        print(df ) 
        print("result :",result)
        results.append(result)
    return results


        
def randomLIST(seed):
    random.seed(seed) 
    randomlist=[]
    for i in range(0,30):
        n = float(random.SystemRandom().randint(1,1000))/float(100)
        randomlist.append(n)
    # print(randomlist)
    return randomlist

randommat=[]
numlists=13
for i in range(numlists):
    seedval=random.SystemRandom().randint(1,100)
    randommat.append(randomLIST(seedval))

results=kstest(randommat,30,0)


ninenine=0.48895
ninefive=0.40925

print("KsTable vals ")
print("95 : "+str(ninefive)+" 99 : ",ninenine)
count=0
for i in results:
    passed99=False
    passed95=False
    if(i<ninefive):
        passed95=True
    if(i<ninenine):
        passed99=True
    count+=1
    print("index : "+str(count)+" 99 : "+str(passed99)+" 95 : "+str(passed99)+" val : "+str(i))

# pprint(results)
# print()

# print(randommat)



# # importing library 
# import csv 
  
# # opening the csv file in 'w' mode 
# file = open('pythonrands.csv', 'w', newline ='') 
# header= [i+1 for i in range(len(randommat))]
  
# with file:     
#     write = csv.writer(file) 
#     write.writerows(randommat) 