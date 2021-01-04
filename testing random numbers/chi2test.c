#include<stdio.h>
#include<stdlib.h>

double chitest(int ival)
{
    srand(ival);
    int i;
    int randnum[5000];
    int rands[500];
    double diff[500];
    for(i=0;i<500;i++)
    {
        rands[i]=0;
    }
    for(i=0;i<5000;i++)
    {
        randnum[i]=rand()%500;
        rands[randnum[i]]++;
        
    }
    double sum=0.0;
    int expect=5000/500;
    for(i=0;i<500;i++)
    {
        diff[i]=rands[i]-expect;
        sum=sum+(diff[i]*diff[i])/expect;
        // printf("%d\t%f\t%f\t%f\n",rands[i],diff[i],diff[i]/150,sum);
    }
    
    printf("chi val at seed %d :%f\n",ival,sum);
    return sum;
}
void main()
{
    int i;
    double chivals[13];
    for(i=0;i<13;i++)
    {
        chivals[i]=chitest(rand()%100);
    }
}