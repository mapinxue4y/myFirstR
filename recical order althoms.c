#include<stdio.h>
int main()
{
    int ci[100]={8,6,4,45,34,24,78,4};
    int i=8,j,k;
    int binaryArrayF[100]={};
    int binaryArrayS[100]={};
    int orderArrayBin(int arrayA[],int n);
    int additionArray(int arrayB[],int arrayC[],int m,int z);
    for(i=0;i<8;i++)
    {
        printf("%d ",ci[i]);
    }
    printf("\n");
    printf("the first array:\n");
    for(j=0;j<(i/2);j++)
    {
        binaryArrayF[j]=ci[j];
        printf("%d ",binaryArrayF[j]);
    }
    printf("\n");
    printf("the second array: \n");
    for(k=j;k<i;k++)
    {
        binaryArrayS[k-j]=ci[k];
        printf("%d ",binaryArrayS[k-j]);
    }
    printf("\n");
    printf("%d \n",j);
    orderArrayBin(binaryArrayF,j);
    orderArrayBin(binaryArrayS,k-j);
    for(i=0;i<2*j;i++)
    {
        if(i<j)
        {
            printf("%d ",binaryArrayF[i]);
        }
        else
        {
            printf("%d ",binaryArrayS[i-j]);
        }
    }
    printf("\n");
    additionArray(binaryArrayF,binaryArrayS,j,k-j);
return 0;
}
int orderArrayBin(int arrayA[],int n)
{
    int l;
    int i,j;
    int t;
    l=n;
    printf("%d \n",n);
    for(i=0;i<n;i++)
    {
        printf("%d ",arrayA[i]);
    }
    arrayA[n]=1000000;
    printf("\n");
    for(i=0;i<n;i++){
    for(j=0;j<n;j++)
    {
        printf("%d ",arrayA[j]);
        if(arrayA[j]>arrayA[j+1])
        {
            t=arrayA[j];
            arrayA[j]=arrayA[j+1];
            arrayA[j+1]=t;
        }
    }
    }
        printf("\n");
        printf("order array:");
        for(i=0;i<l;i++)
        {
            printf("%d ",arrayA[i]);
        }
        printf("\n");
    return arrayA;
}
int additionArray(int arrayB[],int arrayC[],int m,int z)
{
    int arrayD[100];
    arrayB[m]=1000000;
    arrayC[z]=1000000;
    int i,j,k;
    for(k=0,i=0,j=0;k<m+z;k++)
    {
        if(arrayB[i]<=arrayC[j])
        {
            arrayD[k]=arrayB[i];
            i++;
        }
        else
        {
            arrayD[k]=arrayC[j];
            j++;
        }
        printf("%d ",arrayD[k]);
    }
    return arrayD;
}
