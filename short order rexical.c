#include<stdio.h>
int main()
{
    int ci[100]={8,6,4,45,34,24,78,4};
    int i=8,j,k;
    int *p;
    int *a[100];
    int binaryArrayF[100]={};
    int binaryArrayS[100]={};
    int orderArrayBin(int arrayA[],int n);
    int additionArray(int arrayB[],int arrayC[],int m,int z);
    for(j=0;j<(i/2);j++)
    {
        binaryArrayF[j]=ci[j];
    }
    for(k=j;k<i;k++)
    {
        binaryArrayS[k-j]=ci[k];
    }
    orderArrayBin(binaryArrayF,j);
    orderArrayBin(binaryArrayS,k-j);
    additionArray(binaryArrayF,binaryArrayS,j,k-j);
return 0;
}
int orderArrayBin(int arrayA[],int n)
{
    int l;
    int i,j;
    int t;
    l=n;
    arrayA[n]=1000000;
    for(i=0;i<n;i++){
    for(j=0;j<n;j++)
    {
        if(arrayA[j]>arrayA[j+1])
        {
            t=arrayA[j];
            arrayA[j]=arrayA[j+1];
            arrayA[j+1]=t;
        }
    }
    }
    return arrayA[n];
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
    return arrayD[k];
}
