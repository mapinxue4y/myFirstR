#include<stdio.h>
int main()
{
    int a,b;
    scanf("%d%d",&a,&b);
    int hour=a/100;
    int minu=a%100;
    if(b>0)
    {
        int midhour=(minu+b)/60;
        int midminu=(minu+b)%60;
        printf("%d%02d\n",hour+midhour,midminu);
    }
    if(b<0)
    {
        hour=hour-1-(-b)/60; 
        int midminu=(60+minu-(-b)%60)%60;
        hour=hour+(60+minu-(-b)%60)/60;
        printf("%d%02d\n",hour,midminu);
    }
    return 0;
}
