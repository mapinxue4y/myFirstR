#include<stdio.h>
int main()
{
    int cm,inch,foot;
    double m;
    scanf("%d",&cm);
    m=cm/100.0/0.3048*12;
    foot=m/12;
    inch=(m-foot*12);
    printf("%d %d",foot,inch);
    return 0;
}
