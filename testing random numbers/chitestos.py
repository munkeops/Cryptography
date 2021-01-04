


import random
import numpy as np
import pandas as pd

def chitest(randlist,up):
    sum1=0
    expect=len(randlist)/up
    uniquerand=[0]*(up)
    for i in randlist:
        # print(i)
        uniquerand[i-1]+=1

    obs=uniquerand
    expected=[expect]*len(uniquerand)
    calc=[]
    table=[]

    for i in uniquerand:
        val=i-expect
        sum1=sum1+val*val/expect
        calc.append(val*val/expect)
    table.append(np.array(obs))
    table.append(np.array(expected))
    table.append(np.array(calc))
    table=np.array(table).T
    df = pd.DataFrame(table,columns=["obs","expected","(o-e)**2/e"])  
    print(df )
    accept=False
    if(sum1<553.127):
        accept=True
    print("calc : "+str(sum1)+"  chi table : 553.127  accepted : ",accept)
    return sum1


def randomLIST(seed):
    random.seed(seed) 
    randomlist=[]
    for i in range(0,5000):
        n = random.SystemRandom().randint(1,500)
        randomlist.append(n)
    # print(randomlist)
    return randomlist
for i in range(0,13):
    seed=random.SystemRandom().randint(1,100)
    chitest(randomLIST(seed),500)
# chitest(randomLIST(0),500)
