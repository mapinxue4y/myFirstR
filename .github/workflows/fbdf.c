#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<windows.h>
#include<string.h>

FILE *fp; //打开基本信息的文件指针
FILE *secfp;//打开工资信息的文件指针
int num=0;//对基本工资记数
int numw=0;//对工资信息记数
void sayHi();//提示前行函数
void mainamnu();//主菜单函数
void inputData();//输入信息函数
void judge(int j,int flag,int month);//判断是否已经存在函数
void changeData();//改变信息函数
void changebyname();//用名字改变信息函数
void changebynum();//用工号改变信息函数
void deletebynum();//用工号删除信息函数
void selectProject();//查找信息函数
void analyze();//分析函数
void diffdep();///不同学院分析函数
void diffcla();//不同职称分析函数
void read_from_file();//读取基本信息函数
void scanfromfile();//读取工资信息函数
void write_to_file();//写入基本信息函
void inputtofile();//写入工资函数
void showall(int sdd);//显示基本信息函数
void showteabymonth();//月份显示信息
void showteabynum();//工号显示信息
void showteabyname();//姓名显示信息
void linksec(char s);
void jundges(char j);//判断输入正确in
void order();//排序
int orders(int *a,int length);

struct Teacher {//基本信息
    int tnumber;
    char tname[20];
    char tclass[20];
    char tdep[20];
}tec[103];

struct Wage{//工资信息
    int tnumbers;
    int tmonth;
    int fundwage;
    int addwage;
    int diffwage;
    int shouldpay;
    int realypay;
}wag[1200];

struct Wage *p=wag;
struct Teacher *pa=tec;
    void sayHi()//开屏函数
        {
        printf(" 欢迎访问教工工资系统\n");
        printf("             by马品学\n");
        Sleep(1500);//延迟1.5秒
        system("cls");//清屏
        }



void mainamnu()
{
    order();
    system("cls");
    char n;
    printf("    高校教师工资管理系统\n");
    printf("1	录入数据\n");
    printf("2	修改数据\n");
    printf("3	查询显示\n");
    printf("4	统计分析\n");
    printf("5	退出系统\n");
    printf("请按照您的需求键入相应数字:");
    while(1){
        scanf("%s",&n);
            if(n=='1'){
                printf("您输入的是 1 \n");
                printf("进入录入数据功能\n");
                inputData();}
            else if(n=='2'){
                printf("输入了 2 \n");
                printf("你可以修改数据并保存\n");
                changeData();}
            else if(n=='3'){
                printf("输入了 3 \n");
                printf("你可以查询数据\n");
                selectProject();}
            else if(n=='4'){
                printf("输入了 4 \n");
                printf("统计分析\n");
                analyze();}
            else if(n=='5'){
                write_to_file();
                inputtofile();
                char tm;
                printf("你确定要退出吗？\n");
                printf("输入 1 退出\n");
                scanf("%s",&tm);
                if(tm=='1')
                    exit(0);
                else{
                    system("cls");
                    mainamnu();}}
            else{//体现鲁棒性
                printf("输入错误！");}}}






int main()//主函数
{
    sayHi();
    read_from_file();//读数据
    scanfromfile();
    while(1){
    mainamnu();}
}




void read_from_file()//基本信息读取
	{
	  if((fp=fopen("teacherData.txt","r"))==NULL){
	    printf("教师工资基本文件不存在\n");
	    if((fp=fopen("teacherData.txt","w"))==NULL){
		  printf("建立失败\n");
		  exit(0);}}
	  fseek(fp,0,2);//找文件
	  if(ftell(fp)>0){
		rewind(fp);
		for(num=0;!feof(fp)&&fread(&tec[num],sizeof(struct Teacher),1,fp);num++);//对文件大小判断并读取文件
    }//这里改变了num的值
}




void write_to_file()//读取文件
	{
	  int i;
	  if((fp=fopen("teacherData.txt","w"))==NULL)
	  printf("打开文件夹失败");
	  for(i=0;i<num;i++){
	    if(fwrite(&tec[i],sizeof(struct Teacher),1,fp)!=1)
		{printf("文件写入错误!\n");}}
	  fclose(fp);//关闭文件
     // printf("教师基本信息文件已保存\n");
     }





void inputtofile()//写入工资信息
	{
	  int i;
	  if((secfp=fopen("teacherDataWage.txt","w"))==NULL)
	  printf("打开文件夹失败");
	  for(i=0;i<numw;i++){
	    if(fwrite(&wag[i],sizeof(struct Wage),1,secfp)!=1)
		{printf("文件写入错误!\n");}
		}
	  fclose(secfp);
      //printf("教师工资信息文件已保存\n");
    }




void scanfromfile()//读取工资信息
	{
	  if((secfp=fopen("teacherDataWage.txt","r"))==NULL){
	    printf("教师工资信息文件不存在\n");
	    if((secfp=fopen("teacherDataWage.txt","w"))==NULL){
		  printf("建立失败\n");
		  exit(0);}}
	  fseek(secfp,0,2);
	  if(ftell(secfp)>0){
		rewind(secfp);
		for(numw=0;!feof(secfp)&&fread(&wag[numw],sizeof(struct Wage),1,secfp);numw++);//numw数值改变
    }}




    void inputData()//输入数据
    {
        char x;
        system("cls");
        printf("输入 1 录入基本信息：\n输入 2 录入工资信息：\n3 返回上一级\n");
        scanf("%s",&x);
        if(x=='1'){
            printf("录入教师的基本信息：\n");
            printf("输入工号：");
            scanf("%d",&(pa+num)->tnumber);
            judge(tec[num].tnumber,0,0);//判断重合数据
            printf("输入姓名：");
            scanf("%s",&(pa+num)->tname);
            printf("输入学院：");
            printf("输入 1 ：信息学院\n");
            printf("输入 2 ：工学院\n");
            printf("输入 3 ：林学院\n");
            printf("输入 4 ：理学院\n");
            printf("输入 5 ：生物学院\n");
            scanf("%s",&tec[num].tdep);
           // jundges(tec[num].tdep)
            printf("输入职称：");
            printf("输入 1 :教授\n");
            printf("输入 2 :副教授\n");
            printf("输入 3 :教师\n");
            printf("输入 4 :助教\n");
            scanf("%s",&tec[num].tclass);
            //jundges(tec[num].tclass);
            printf("录入完成\n");
            num++;
            printf("按任意键返回");
            write_to_file();//保存数据
            getch();inputData();////返回
        }
        else if(x=='2'){
            showall(1);
            //int s=100;
            printf("输入工号：");
            scanf("%d",&(p+numw)->tnumbers);
            //int p=tec[s].tnumber;
            //s=link(tec[s].tnumber);
            //wag[s].tnumber=p;
            printf("输入月份；");
            scanf("%d",&(p+numw)->tmonth);
            judge((p+numw)->tnumbers,1,(p+numw)->tmonth);
            printf("输入基本工资：");
            scanf("%d",&wag[numw].fundwage);
            printf("输入津贴：");
            scanf("%d",&wag[numw].addwage);
            printf("输入扣除费用：");
            scanf("%d",&wag[numw].diffwage);
            wag[numw].shouldpay=wag[numw].fundwage+wag[numw].addwage;//计算应发工资
            wag[numw].realypay=wag[numw].shouldpay-wag[numw].diffwage;//计算实发工资
            printf("录入完成，按任意键返回\n");
            numw++;
            inputtofile();//保存
            getch();
            //system("cls");
            inputData();
        }
        else if(x=='3')
            {
            printf("确定返回?\n");
            printf("按1 返回");
            printf("按其他键留下");
            char ba;
            scanf("%s",&ba);
                if(ba=='1')
                {
                    system("cls");
                    mainamnu();
                }
                else{
                    inputData();
                }
            }

        else{
           printf("输入错误\n");//鲁棒性
           Sleep(200);
           inputData();}
        }
void selectProject()//查找函数
{
    system("cls");
    char s;
    printf(" 输入命令：\n");
    printf("1 显示所有教师的基本信息（以工号为序)\n");
    printf("2 根据月份显示所有教师当月工资信息（以工号为序）\n");
    printf("3 根据工号查询某位教师某一月份的基本信息和工资信息\n");
    printf("4 根据姓名查询某位教师某一月份的基本信息和工资信息\n");
    printf("5 返回\n");
    scanf("%s",&s);
    switch(s){
        case '1':showall(2);break;
        case '2':showteabymonth();break;
        case '3':showteabynum();break;
        case '4':showteabyname();break;
        case '5':mainamnu();break;
        default:{printf("输入错误！");Sleep(200);selectProject();break;}
        }
}
void showall(int sdd)//表现所有的数据//参数用来判断用处
{
    int i;
    if(num!=0)//判断是否有数据
    {
        for(i=0;i<num;i++)
        {
            printf("\n工号：%d 姓名：%s ",tec[i].tnumber,tec[i].tname);
            //printf("学院：%s  职称：%s",tec[i].tdep,tec[i].tclass );
            if(strcmp(tec[i].tdep,"1")==0)
                printf("信息学院 ");
            else if(strcmp(tec[i].tdep,"2")==0)
                printf("工学院 ");
            else if(strcmp(tec[i].tdep,"3")==0)
                printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物1学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
        }
    }
    else
        printf("没有找到，请先输入\n");
    printf("\n按任意键继续\n");
    if(sdd==1)
    {   getch();
        return;}
    if(sdd==2)
       {
           getch();
           selectProject();
       }
}

void showteabymonth()//用月份来查找工资
{
    int i;
    int month;
    printf("输入月份：");
    int flag=1;//判断月份是否存在
    scanf("%d",&month);
    if(numw!=0)
        for(i=0;i<numw;i++)
        {
            if(wag[i].tmonth==month)
            {
            flag=0;
            printf("工号；%d 月份：%d 基本工资：%d",wag[i].tnumbers,wag[i].tmonth,wag[i].fundwage);
            printf("津贴：%d 扣除：%d 应发：%d 实发工资：%d\n",wag[i].addwage,wag[i].diffwage,wag[i].shouldpay,wag[i].realypay);
            }
    }
    if(numw==0||flag==1)
        {
            printf("没有找到你要的月份\n");
            printf("按任意键返回");
            getch();selectProject();
        }
        printf("\n按任意键返回");
        getch();selectProject();
}
void showteabyname()//用姓名来查询
{
    int i=0;
    char name[20];
    int as=1;
    int asd=1;
    printf("请输入姓名：");
    scanf("%s",&name);
    for(i=0;i<num;i++)
    {
        if(strcmp(tec[i].tname,name)==0)
        {
            as=0;
            printf("ta的基本信息：工号：%d\n",tec[i].tnumber);
            if(strcmp(tec[i].tdep,"1")==0)
                printf("信息学院 ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("工学院 ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
            for(int k=0;k<numw;k++)
            {
                if(tec[i].tnumber==wag[k].tnumbers)
                {
                    asd=0;
                    printf("工资信息：%d月 基本工资：%d元 应发工资：%d \n",wag[k].tmonth,wag[k].fundwage,wag[k].shouldpay);
                }
            }
        }
    }
    if(as==1)//布尔值判断存在与否
        {
            printf("没找到此教师信息");
        }
    if(asd==1)
    {
        printf("没有此叫教师的工资信息");
    }
    printf("按任意键返回");
    getch();selectProject();
}
void showteabynum()
{
    int i,k;
    int flag=1;
    int jj=1;//两个布尔值
    printf("请输入工号");
    scanf("%d",&k);
    for(i=0;i<num;i++)
    {
        if(k==tec[i].tnumber)
        {
            printf("ta的基本信息：姓名：%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("信息学院 ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("工学院 ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
            jj=0;
            for(int s=0;s<numw;s++)
            {
                if(k==wag[s].tnumbers)
                {
                    printf("月份：%d 基本工资：%d 津贴：%d 扣除：%d 应发工资：%d 实发工资：%d\n",wag[s].tmonth,wag[s].fundwage,wag[s].addwage,wag[i].diffwage,wag[i].shouldpay,wag[i].realypay);
                    flag=0;
                }
            }
        }
        }
        if(jj==1)
        printf("没找到此教师\n");
        if(flag==1)
        printf("没有工资信息\n");
        printf("按任意键返回\n");
        getch();selectProject();//返回
    }

void analyze()//分析菜单
{
    system("cls");
    printf("1 统计不同学院平均工资\n");
    printf("2 统计不同职位平均工资\n");
    printf("3 返回\n");
    char a;
    scanf("%s",&a);
    switch(a)
    {
        case '1':diffdep();break;
        case '2':diffcla();break;
        case '3':mainamnu();break;
        default:{printf("输入错误!");Sleep(200);analyze();}break;
    }
}
void diffdep()//对不同的院系
{
    int i;
    int sums=0,sumsf=0,sumsg=0,sumsl=0,sumss=0;
    int sumr=0,sumrf=0,sumrg=0,sumrl=0,sumrs=0;
    int y1=0,y2=0,y3=0,y4=0,y5=0;
    printf("请输入月份：");
    int month;
    scanf("%d",&month);
    for(i=0;i<num;i++)
    {
        for(int j=0;j<numw;j++)
        {
        if(strcmp(tec[i].tdep,"1")==0)
        {
            if(tec[i].tnumber==wag[j].tnumbers)
            {
                if(wag[j].tmonth==month){
            y1++;
            sums=sums+wag[j].shouldpay;
            sumr=sumr+wag[j].realypay;}}
        }
        if(strcmp(tec[i].tdep,"2")==0)
        {
            y2++;
            if(tec[i].tnumber==wag[j].tnumbers){
            if(wag[j].tmonth==month){
            sumsf+=wag[j].shouldpay;
            sumrf+=wag[j].realypay;}}
        }
        if(strcmp(tec[i].tdep,"3")==0)
        {
            y3++;
            if(tec[i].tnumber==wag[j].tnumbers){
            if(wag[j].tmonth==month){
            sumsg+=wag[j].shouldpay;
            sumrg+=wag[j].realypay;}}
        }
        if(strcmp(tec[i].tdep,"4")==0)
        {
            y4++;
            if(tec[i].tnumber==wag[j].tnumbers)
            {
                if(wag[j].tmonth==month){
                sumsl+=wag[j].shouldpay;
                sumrl+=wag[j].realypay;}
            }
        }
        if(strcmp(tec[i].tdep,"5")==0)
        {
            y5++;
            if(tec[i].tnumber==wag[j].tnumbers)
            {
                if(wag[j].tmonth==month){
                sumss+=wag[j].shouldpay;
                sumrs+=wag[j].realypay;}
            }
        }
    }}
    int ord[30][10];
    i=0;
    if(y1!=0)
        printf("信息学院：应发工资平均值:%d 实发工资平均值:%d\n",sums/y1,sumr/y1);
     else
        printf("无信息学院信息\n");
    if(y2!=0)
        printf("工学院:应发工资平均值:%d 实发工资平均值:%d\n",sumsf/y2,sumrf/y2);
    //{ord[i][2]=sumrf/y2;ord[i].flag=2;i++;}
    else
        printf("无工学院信息\n");
    if(y3!=0)
        printf("林学院:应发工资平均值%d 实发工资平均值:%d\n",sumsg/y3,sumrg/y3);
    //{ord[i].aver=sumrg/y3;ord[i].flag=3;i++;}
    else
        printf("无林学院信息\n");
   if(y4!=0)
        printf("理学院:应发工资平均值：%d 实发工资平均值：%d\n",sumsl/y4,sumrl/y4);
     //{ord[i].aver=sumrl/y4;ord[i].flag=4;i++;}
     else
        printf("无理学院信息\n");
    if(y5!=0)
        printf("生物学院：应发平均值：%d 实发工资平均值：%d\n",sumss/y5,sumrs/y5);
    //{ord[i]=sumrs/y5;ord[i].flag=5;i++;}
     else
        printf("无生物学院信息\n");

    /*int len=strlen(ord);
    printf("%d ",len);
    orders(ord,len);
    for(int f=0;f<len;f++)
    {
        switch(ord[f].flag){
            case 1:printf("信息学院：应发：%d  实发工资：%d",sums/y1,ord[f].aver);
            case 2:printf("");
    }
    }
    printf("");*/
    printf("按任意键返回\n");
    getch();analyze();
}
void diffcla()//类似于上面那样
{
   int i;
   int month;
   printf("输入月份：");
   scanf("%d",&month);
    int sums=0,sumsf=0,sumsg=0,sumsl=0;
    int sumr=0,sumrf=0,sumrg=0,sumrl=0;
    int y1=0,y2=0,y3=0,y4=0;
    for(i=0;i<num;i++)
    {
        for(int j=0;j<numw;j++){
        if(strcmp(tec[i].tclass,"1")==0)
        {
        if(tec[i].tnumber==wag[j].tnumbers)
            {
                if(wag[j].tmonth==month){
            y1++;
            sums=sums+wag[j].shouldpay;
            sumr=sumr+wag[j].realypay;}}
        }
        if(strcmp(tec[i].tclass,"2")==0)
        {
            y2++;
            if(tec[i].tnumber==wag[j].tnumbers){
            if(wag[j].tmonth==month){
            sumsf+=wag[j].shouldpay;
            sumrf+=wag[j].realypay;}}
        }
        if(strcmp(tec[i].tclass,"3")==0)
        {
            y3++;
            if(tec[i].tnumber==wag[j].tnumbers){
            if(wag[j].tmonth==month){
            sumsg+=wag[j].shouldpay;
            sumrg+=wag[j].realypay;}}
        }
        if(strcmp(tec[i].tclass,"4")==0)
        {
            y4++;
            if(tec[i].tnumber==wag[j].tnumbers)
            {
                if(wag[j].tmonth==month){
                sumsl+=wag[j].shouldpay;
                sumrl+=wag[j].realypay;}
            }
        }
    }}
    if(y1!=0)
        printf("教授：应发工资平均值:%d 实发工资平均值:%d\n",sums/y1,sumr/y1);
    else
        printf("无教授信息\n");
    if(y2!=0)
        printf("副教授:应发工资平均值:%d 实发工资平均值:%d\n",sumsf/y2,sumrf/y2);
    else
        printf("无副教授信息\n");
    if(y3!=0)
        printf("讲师:应发工资平均值:%d 实发工资平均值:%d\n",sumsg/y3,sumrg/y3);
    else
        printf("无讲师信息\n");
    if(y4!=0)
        printf("助教:应发工资平均值:%d 实发工资平均值：%d",sumsl/y4,sumrl/y4);
    else
        printf("无助教信息\n");
    printf("按任意键返回\n");
    getch();analyze();
}


void changeData()//改变信息菜单
{
    system("cls");
    printf("1 根据工号修改\n");
    printf("2 根据姓名修改\n");
    printf("3 根据工号删除\n");
    printf("4 返回\n");
    char k;
    scanf("%s",&k);
    switch(k)
    {
        case '1':changebynum();break;
        case '2':changebyname();break;
        case '3':deletebynum();break;
        case '4':mainamnu();break;
        default:{printf("输入错误");Sleep(200);changeData();break;}
    }
}
void changebynum()//工号改变
{
    int c;
    printf("输入工号");
    scanf("%d",&c);
    int j,i;
    int a;
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==c){
        printf("ta的基本信息：姓名：%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("信息学院 ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("工学院 ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
    }
    }
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==c)
        {
            printf("工资信息：月份：：%d 基本工资：%d 应发工资：%d 实发工资：%d \n",wag[j].tmonth,wag[j].fundwage,wag[j].shouldpay,wag[j].realypay);
        }
    }
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==c)
        {
          a=i;
          printf("重新赋值：");
          printf("\n输入姓名:");
          scanf("%s",&tec[i].tname);
          printf("\n输入院系：");
          scanf("%s",&tec[i].tdep);
          printf("\n输入职称：");
          scanf("%s",&tec[i].tclass);
          //printf("修改成功！");
        }
    }
    printf("输入月份\n");
    int rtre;
    scanf("%d",&rtre);
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==c)
        {
            if(wag[j].tmonth==rtre){
            printf("重新赋值：\n");
            printf("输入基本工资：");
            scanf("%d",&wag[i].fundwage);
            printf("输入津贴：");
            scanf("%d",&wag[i].addwage);
            printf("输入扣除：");
            scanf("%d",&wag[i].diffwage);
            wag[i].shouldpay=wag[i].fundwage+wag[i].addwage;//yin fa gongZ
            wag[i].realypay=wag[i].shouldpay-wag[i].diffwage;
            printf("修改成功！");
            }
        }
    }
    write_to_file();
    inputtofile();
    printf("按任意键返回");
    getch();changeData();

}
void changebyname()//输入姓名
{
    printf("输入姓名：");
    char c[20];
    scanf("%s",&c);
    int i,j;
    for(i=0;i<num;i++)
    {
        if(strcmp(tec[i].tname,c)==0)
        {
            printf("ta的基本信息：工号：%d\n",tec[i].tnumber);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("信息学院 ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("工学院 ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
            for(j=0;j<numw;j++)
            {
                if(tec[i].tnumber==wag[j].tnumbers)
                {
                    printf("基本工资：");
                    printf("%d",wag[j].fundwage);
                    printf("津贴：");
                    printf("%d",wag[j].addwage);
                    printf("扣除工资：");
                    printf("%d",wag[j].diffwage);
                }
            }
        }
    }
    int fir,sec;
    printf("\n输入工号:\n");
    scanf("%d",&fir);
    printf("输入月份：");
    scanf("%d",&sec);
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==fir)
        {
            printf("输入职称：");
            scanf("%s",&tec[i].tclass);
            printf("输入院系：");
            scanf("%s",&tec[i].tdep);
        }
    }
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==fir){
            if(wag[j].tmonth==sec){
        printf("输入基本工资：");
        scanf("%d",&wag[j].fundwage);
        printf("输入津贴：");
        scanf("%d",&wag[j].addwage);
        printf("输入扣除工资：");
        scanf("%d",&wag[j].diffwage);
        }
        }
    }
    write_to_file();
    inputtofile();//写入
    printf("按任意键返回");
    getch();
    changeData();
}
void deletebynum()//已完成//删除主要是前一个背后一个所覆盖
{
    int i,j,r,t;
    int nums;
    int k=0;
    printf("输入要删除的工号：");
    scanf("%d",&nums);
    for(i=0;i<num;i++)//输出基本信息
    {
        if(nums==tec[i].tnumber)
        {
            printf("ta的基本信息：姓名：%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("信息学院 ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("工学院 ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("林学院 ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("理学院 ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("生物学院");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" 教授 ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" 副教授  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" 讲师 ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" 主讲 ");
        }
    }
    for(i=0;i<numw;i++)
    {
        if(nums==wag[i].tnumbers)
        {
            printf("月份：%d 基本工资：%d 应发工资：%d 实发工资：%d ",wag[i].tmonth,wag[i].fundwage,wag[i].shouldpay,wag[i].realypay);
        }
    }
    printf("确认删除？\n输入y确认，n返回");
    char qwqqw='c';
    while(1){//确认循环
    scanf("%c",&qwqqw);
    if(qwqqw=='y')
        break;
    else if(qwqqw=='n')
    changeData();
    else
    printf("输入错误");
    }
    for(i=0;i<num;i++)
    {
        if(nums==tec[i].tnumber)
        {
            for(j=i;j<num-1;j++)
			  tec[j]=tec[j+1];
			  num--;
			  k++;
        }
    }
    for(r=0;r<numw;r++)
    {
        if(nums==wag[r].tnumbers)
        {
            for(t=r;t<numw-1;t++)
                wag[t]=wag[t+1];
            numw--;
            k++;
        }
    }write_to_file();
    inputtofile();
    printf("删除完成！");
    printf("按任意键返回");
    getch();changeData();
}


void judge(int j,int flag,int month)//判断是否已经存在
{   int bolean=0;
    if(flag==0){
    for(int i=0;i<num;i++)
    {
        if(j==tec[i].tnumber)//判断工号
        {
            printf("此号码已经出现过了\n");
            printf("姓名是：%s\n",tec[i].tname);
            printf("按任意键返回\n");
            getch();
            inputData();
        }
    }
    }
    else
    {
        for(int i=0;i<numw;i++)
        {
            if(j==wag[i].tnumbers)//判断工号
            {
                if(month==wag[i].tmonth)
                    printf("这个月份已经出现过了\n");
                    printf("基本工资：%d\n",wag[i].fundwage);
                    printf("按任意键返回\n");
                    getch();
                    inputData();}}
     for(int d=0;d<num;d++){
            if(j==tec[d].tnumber)
                bolean=1;}
     if(bolean==0)
        {printf("没有此工号\n按任意键返回\n");getch();inputData();}}}
//order(tec);
void order()
{
    int i, j, temp;
    char ad[20],af[20],ag[20];//冒泡排序算法：进行 n-1 轮比较
    for(i=0; i<num-1; i++){//每一轮比较前 n-1-i 个，也就是说，已经排序好的最后 i 个不用比较
        for(j=0; j<num-i-1; j++){
            if(tec[j].tnumber > tec[j+1].tnumber){
                temp = tec[j].tnumber;
                strcpy(ad, tec[j].tname);
                strcpy(af , tec[j].tclass);
                strcpy(ag , tec[j].tdep);
                tec[j].tnumber= tec[j+1].tnumber;
                strcpy(tec[j].tname,tec[j+1].tname);
                strcpy(tec[j].tclass,tec[j+1].tclass);
                strcpy(tec[j].tdep, tec[j+1].tdep);
                tec[j+1].tnumber=temp;
                strcpy(tec[j+1].tname,ad);
                strcpy(tec[j+1].tclass,af);
                strcpy(tec[j+1].tdep,ag);
            }
        }
    }
write_to_file();
}
int orders(int *a,int length)
{
    int i, j, k;
    for(i=0; i<length-1; i++)
    {
        for(j=0; j<length-1-i; j++)
        {
            if(a[j] > a[j+1])
            {
                k = a[j];
                a[j] = a[j+1];
                a[j+1] = k;
            }
        }
    }}
