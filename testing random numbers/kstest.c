#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void bubblesort(double*arr,int len)
{
    int i,j;
    double temp;
    printf("%ld",sizeof(arr));
    for(i=0;i<len;i++)
    {
        for(j=0;j<len-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

double max(double * arr,int len)
{
    int i;
    double max=arr[0];
    for(i=0;i<len;i++)
    {
        if(max<arr[i])
        {
            max=arr[i];
        }
    }
    return max;
}

double kstest(int seed,int up,int down)
{
    srand(seed);
    int num_samp=30;
    int i;
    double random[num_samp];
    double fnk1[num_samp];
    double fnk2[num_samp];
    double f0[num_samp];
    double div1[num_samp];
    double div2[num_samp];
    for(i=0;i<num_samp;i++)
    {
        random[i]=(float)(rand()%1000)/(float)(100);
    }
    bubblesort(random,num_samp);
    // fn[0]=i;
    printf("k\tval\t\tfn(k-1)\t\tF0\t\tFn(k)\t\tmod1\t\tmod2\n");
    for(i=0;i<num_samp;i++)
    {
        fnk1[i]=(float)(i+1-1)/num_samp;
        fnk2[i]=(float)(i+1)/num_samp;
        f0[i]=random[i]/(float)(up-down);
        div1[i]=fabs(fnk1[i]-f0[i]);
        div2[i]=fabs(f0[i]-fnk2[i]);
        printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n",i+1,random[i],fnk1[i],f0[i],fnk2[i],div1[i],div2[i]);
    }
    double max1=max(div1,num_samp);
    double max2=max(div2,num_samp);
    double max= (max1>max2)?max1:max2;
    // printf("the max val : %f\n",max);
    return max;

    
    
    // return random;
}



void main()
{
    int i;
    double ksvals[13];
    for(i=0;i<13;i++)
    {
        ksvals[i]=kstest(rand()%100,30,0);
        // printf("%f\n",ksvals[i]);
    }
    // bubblesort(ksvals);
    printf("\n");
    printf("99 test : %f and 95 test :%f\n", 0.40925,0.48895);
    for(i=0;i<13;i++)
    {
        printf("max vals : %f\n",ksvals[i]);
    }
}