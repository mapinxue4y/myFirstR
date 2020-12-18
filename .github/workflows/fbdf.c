#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<windows.h>
#include<string.h>

FILE *fp; //�򿪻�����Ϣ���ļ�ָ��
FILE *secfp;//�򿪹�����Ϣ���ļ�ָ��
int num=0;//�Ի������ʼ���
int numw=0;//�Թ�����Ϣ����
void sayHi();//��ʾǰ�к���
void mainamnu();//���˵�����
void inputData();//������Ϣ����
void judge(int j,int flag,int month);//�ж��Ƿ��Ѿ����ں���
void changeData();//�ı���Ϣ����
void changebyname();//�����ָı���Ϣ����
void changebynum();//�ù��Ÿı���Ϣ����
void deletebynum();//�ù���ɾ����Ϣ����
void selectProject();//������Ϣ����
void analyze();//��������
void diffdep();///��ͬѧԺ��������
void diffcla();//��ְͬ�Ʒ�������
void read_from_file();//��ȡ������Ϣ����
void scanfromfile();//��ȡ������Ϣ����
void write_to_file();//д�������Ϣ��
void inputtofile();//д�빤�ʺ���
void showall(int sdd);//��ʾ������Ϣ����
void showteabymonth();//�·���ʾ��Ϣ
void showteabynum();//������ʾ��Ϣ
void showteabyname();//������ʾ��Ϣ
void linksec(char s);
void jundges(char j);//�ж�������ȷin
void order();//����
int orders(int *a,int length);

struct Teacher {//������Ϣ
    int tnumber;
    char tname[20];
    char tclass[20];
    char tdep[20];
}tec[103];

struct Wage{//������Ϣ
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
    void sayHi()//��������
        {
        printf(" ��ӭ���ʽ̹�����ϵͳ\n");
        printf("             by��Ʒѧ\n");
        Sleep(1500);//�ӳ�1.5��
        system("cls");//����
        }



void mainamnu()
{
    order();
    system("cls");
    char n;
    printf("    ��У��ʦ���ʹ���ϵͳ\n");
    printf("1	¼������\n");
    printf("2	�޸�����\n");
    printf("3	��ѯ��ʾ\n");
    printf("4	ͳ�Ʒ���\n");
    printf("5	�˳�ϵͳ\n");
    printf("�밴���������������Ӧ����:");
    while(1){
        scanf("%s",&n);
            if(n=='1'){
                printf("��������� 1 \n");
                printf("����¼�����ݹ���\n");
                inputData();}
            else if(n=='2'){
                printf("������ 2 \n");
                printf("������޸����ݲ�����\n");
                changeData();}
            else if(n=='3'){
                printf("������ 3 \n");
                printf("����Բ�ѯ����\n");
                selectProject();}
            else if(n=='4'){
                printf("������ 4 \n");
                printf("ͳ�Ʒ���\n");
                analyze();}
            else if(n=='5'){
                write_to_file();
                inputtofile();
                char tm;
                printf("��ȷ��Ҫ�˳���\n");
                printf("���� 1 �˳�\n");
                scanf("%s",&tm);
                if(tm=='1')
                    exit(0);
                else{
                    system("cls");
                    mainamnu();}}
            else{//����³����
                printf("�������");}}}






int main()//������
{
    sayHi();
    read_from_file();//������
    scanfromfile();
    while(1){
    mainamnu();}
}




void read_from_file()//������Ϣ��ȡ
	{
	  if((fp=fopen("teacherData.txt","r"))==NULL){
	    printf("��ʦ���ʻ����ļ�������\n");
	    if((fp=fopen("teacherData.txt","w"))==NULL){
		  printf("����ʧ��\n");
		  exit(0);}}
	  fseek(fp,0,2);//���ļ�
	  if(ftell(fp)>0){
		rewind(fp);
		for(num=0;!feof(fp)&&fread(&tec[num],sizeof(struct Teacher),1,fp);num++);//���ļ���С�жϲ���ȡ�ļ�
    }//����ı���num��ֵ
}




void write_to_file()//��ȡ�ļ�
	{
	  int i;
	  if((fp=fopen("teacherData.txt","w"))==NULL)
	  printf("���ļ���ʧ��");
	  for(i=0;i<num;i++){
	    if(fwrite(&tec[i],sizeof(struct Teacher),1,fp)!=1)
		{printf("�ļ�д�����!\n");}}
	  fclose(fp);//�ر��ļ�
     // printf("��ʦ������Ϣ�ļ��ѱ���\n");
     }





void inputtofile()//д�빤����Ϣ
	{
	  int i;
	  if((secfp=fopen("teacherDataWage.txt","w"))==NULL)
	  printf("���ļ���ʧ��");
	  for(i=0;i<numw;i++){
	    if(fwrite(&wag[i],sizeof(struct Wage),1,secfp)!=1)
		{printf("�ļ�д�����!\n");}
		}
	  fclose(secfp);
      //printf("��ʦ������Ϣ�ļ��ѱ���\n");
    }




void scanfromfile()//��ȡ������Ϣ
	{
	  if((secfp=fopen("teacherDataWage.txt","r"))==NULL){
	    printf("��ʦ������Ϣ�ļ�������\n");
	    if((secfp=fopen("teacherDataWage.txt","w"))==NULL){
		  printf("����ʧ��\n");
		  exit(0);}}
	  fseek(secfp,0,2);
	  if(ftell(secfp)>0){
		rewind(secfp);
		for(numw=0;!feof(secfp)&&fread(&wag[numw],sizeof(struct Wage),1,secfp);numw++);//numw��ֵ�ı�
    }}




    void inputData()//��������
    {
        char x;
        system("cls");
        printf("���� 1 ¼�������Ϣ��\n���� 2 ¼�빤����Ϣ��\n3 ������һ��\n");
        scanf("%s",&x);
        if(x=='1'){
            printf("¼���ʦ�Ļ�����Ϣ��\n");
            printf("���빤�ţ�");
            scanf("%d",&(pa+num)->tnumber);
            judge(tec[num].tnumber,0,0);//�ж��غ�����
            printf("����������");
            scanf("%s",&(pa+num)->tname);
            printf("����ѧԺ��");
            printf("���� 1 ����ϢѧԺ\n");
            printf("���� 2 ����ѧԺ\n");
            printf("���� 3 ����ѧԺ\n");
            printf("���� 4 ����ѧԺ\n");
            printf("���� 5 ������ѧԺ\n");
            scanf("%s",&tec[num].tdep);
           // jundges(tec[num].tdep)
            printf("����ְ�ƣ�");
            printf("���� 1 :����\n");
            printf("���� 2 :������\n");
            printf("���� 3 :��ʦ\n");
            printf("���� 4 :����\n");
            scanf("%s",&tec[num].tclass);
            //jundges(tec[num].tclass);
            printf("¼�����\n");
            num++;
            printf("�����������");
            write_to_file();//��������
            getch();inputData();////����
        }
        else if(x=='2'){
            showall(1);
            //int s=100;
            printf("���빤�ţ�");
            scanf("%d",&(p+numw)->tnumbers);
            //int p=tec[s].tnumber;
            //s=link(tec[s].tnumber);
            //wag[s].tnumber=p;
            printf("�����·ݣ�");
            scanf("%d",&(p+numw)->tmonth);
            judge((p+numw)->tnumbers,1,(p+numw)->tmonth);
            printf("����������ʣ�");
            scanf("%d",&wag[numw].fundwage);
            printf("���������");
            scanf("%d",&wag[numw].addwage);
            printf("����۳����ã�");
            scanf("%d",&wag[numw].diffwage);
            wag[numw].shouldpay=wag[numw].fundwage+wag[numw].addwage;//����Ӧ������
            wag[numw].realypay=wag[numw].shouldpay-wag[numw].diffwage;//����ʵ������
            printf("¼����ɣ������������\n");
            numw++;
            inputtofile();//����
            getch();
            //system("cls");
            inputData();
        }
        else if(x=='3')
            {
            printf("ȷ������?\n");
            printf("��1 ����");
            printf("������������");
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
           printf("�������\n");//³����
           Sleep(200);
           inputData();}
        }
void selectProject()//���Һ���
{
    system("cls");
    char s;
    printf(" �������\n");
    printf("1 ��ʾ���н�ʦ�Ļ�����Ϣ���Թ���Ϊ��)\n");
    printf("2 �����·���ʾ���н�ʦ���¹�����Ϣ���Թ���Ϊ��\n");
    printf("3 ���ݹ��Ų�ѯĳλ��ʦĳһ�·ݵĻ�����Ϣ�͹�����Ϣ\n");
    printf("4 ����������ѯĳλ��ʦĳһ�·ݵĻ�����Ϣ�͹�����Ϣ\n");
    printf("5 ����\n");
    scanf("%s",&s);
    switch(s){
        case '1':showall(2);break;
        case '2':showteabymonth();break;
        case '3':showteabynum();break;
        case '4':showteabyname();break;
        case '5':mainamnu();break;
        default:{printf("�������");Sleep(200);selectProject();break;}
        }
}
void showall(int sdd)//�������е�����//���������ж��ô�
{
    int i;
    if(num!=0)//�ж��Ƿ�������
    {
        for(i=0;i<num;i++)
        {
            printf("\n���ţ�%d ������%s ",tec[i].tnumber,tec[i].tname);
            //printf("ѧԺ��%s  ְ�ƣ�%s",tec[i].tdep,tec[i].tclass );
            if(strcmp(tec[i].tdep,"1")==0)
                printf("��ϢѧԺ ");
            else if(strcmp(tec[i].tdep,"2")==0)
                printf("��ѧԺ ");
            else if(strcmp(tec[i].tdep,"3")==0)
                printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����1ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
        }
    }
    else
        printf("û���ҵ�����������\n");
    printf("\n�����������\n");
    if(sdd==1)
    {   getch();
        return;}
    if(sdd==2)
       {
           getch();
           selectProject();
       }
}

void showteabymonth()//���·������ҹ���
{
    int i;
    int month;
    printf("�����·ݣ�");
    int flag=1;//�ж��·��Ƿ����
    scanf("%d",&month);
    if(numw!=0)
        for(i=0;i<numw;i++)
        {
            if(wag[i].tmonth==month)
            {
            flag=0;
            printf("���ţ�%d �·ݣ�%d �������ʣ�%d",wag[i].tnumbers,wag[i].tmonth,wag[i].fundwage);
            printf("������%d �۳���%d Ӧ����%d ʵ�����ʣ�%d\n",wag[i].addwage,wag[i].diffwage,wag[i].shouldpay,wag[i].realypay);
            }
    }
    if(numw==0||flag==1)
        {
            printf("û���ҵ���Ҫ���·�\n");
            printf("�����������");
            getch();selectProject();
        }
        printf("\n�����������");
        getch();selectProject();
}
void showteabyname()//����������ѯ
{
    int i=0;
    char name[20];
    int as=1;
    int asd=1;
    printf("������������");
    scanf("%s",&name);
    for(i=0;i<num;i++)
    {
        if(strcmp(tec[i].tname,name)==0)
        {
            as=0;
            printf("ta�Ļ�����Ϣ�����ţ�%d\n",tec[i].tnumber);
            if(strcmp(tec[i].tdep,"1")==0)
                printf("��ϢѧԺ ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
            for(int k=0;k<numw;k++)
            {
                if(tec[i].tnumber==wag[k].tnumbers)
                {
                    asd=0;
                    printf("������Ϣ��%d�� �������ʣ�%dԪ Ӧ�����ʣ�%d \n",wag[k].tmonth,wag[k].fundwage,wag[k].shouldpay);
                }
            }
        }
    }
    if(as==1)//����ֵ�жϴ������
        {
            printf("û�ҵ��˽�ʦ��Ϣ");
        }
    if(asd==1)
    {
        printf("û�д˽н�ʦ�Ĺ�����Ϣ");
    }
    printf("�����������");
    getch();selectProject();
}
void showteabynum()
{
    int i,k;
    int flag=1;
    int jj=1;//��������ֵ
    printf("�����빤��");
    scanf("%d",&k);
    for(i=0;i<num;i++)
    {
        if(k==tec[i].tnumber)
        {
            printf("ta�Ļ�����Ϣ��������%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("��ϢѧԺ ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
            jj=0;
            for(int s=0;s<numw;s++)
            {
                if(k==wag[s].tnumbers)
                {
                    printf("�·ݣ�%d �������ʣ�%d ������%d �۳���%d Ӧ�����ʣ�%d ʵ�����ʣ�%d\n",wag[s].tmonth,wag[s].fundwage,wag[s].addwage,wag[i].diffwage,wag[i].shouldpay,wag[i].realypay);
                    flag=0;
                }
            }
        }
        }
        if(jj==1)
        printf("û�ҵ��˽�ʦ\n");
        if(flag==1)
        printf("û�й�����Ϣ\n");
        printf("�����������\n");
        getch();selectProject();//����
    }

void analyze()//�����˵�
{
    system("cls");
    printf("1 ͳ�Ʋ�ͬѧԺƽ������\n");
    printf("2 ͳ�Ʋ�ְͬλƽ������\n");
    printf("3 ����\n");
    char a;
    scanf("%s",&a);
    switch(a)
    {
        case '1':diffdep();break;
        case '2':diffcla();break;
        case '3':mainamnu();break;
        default:{printf("�������!");Sleep(200);analyze();}break;
    }
}
void diffdep()//�Բ�ͬ��Ժϵ
{
    int i;
    int sums=0,sumsf=0,sumsg=0,sumsl=0,sumss=0;
    int sumr=0,sumrf=0,sumrg=0,sumrl=0,sumrs=0;
    int y1=0,y2=0,y3=0,y4=0,y5=0;
    printf("�������·ݣ�");
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
        printf("��ϢѧԺ��Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ:%d\n",sums/y1,sumr/y1);
     else
        printf("����ϢѧԺ��Ϣ\n");
    if(y2!=0)
        printf("��ѧԺ:Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ:%d\n",sumsf/y2,sumrf/y2);
    //{ord[i][2]=sumrf/y2;ord[i].flag=2;i++;}
    else
        printf("�޹�ѧԺ��Ϣ\n");
    if(y3!=0)
        printf("��ѧԺ:Ӧ������ƽ��ֵ%d ʵ������ƽ��ֵ:%d\n",sumsg/y3,sumrg/y3);
    //{ord[i].aver=sumrg/y3;ord[i].flag=3;i++;}
    else
        printf("����ѧԺ��Ϣ\n");
   if(y4!=0)
        printf("��ѧԺ:Ӧ������ƽ��ֵ��%d ʵ������ƽ��ֵ��%d\n",sumsl/y4,sumrl/y4);
     //{ord[i].aver=sumrl/y4;ord[i].flag=4;i++;}
     else
        printf("����ѧԺ��Ϣ\n");
    if(y5!=0)
        printf("����ѧԺ��Ӧ��ƽ��ֵ��%d ʵ������ƽ��ֵ��%d\n",sumss/y5,sumrs/y5);
    //{ord[i]=sumrs/y5;ord[i].flag=5;i++;}
     else
        printf("������ѧԺ��Ϣ\n");

    /*int len=strlen(ord);
    printf("%d ",len);
    orders(ord,len);
    for(int f=0;f<len;f++)
    {
        switch(ord[f].flag){
            case 1:printf("��ϢѧԺ��Ӧ����%d  ʵ�����ʣ�%d",sums/y1,ord[f].aver);
            case 2:printf("");
    }
    }
    printf("");*/
    printf("�����������\n");
    getch();analyze();
}
void diffcla()//��������������
{
   int i;
   int month;
   printf("�����·ݣ�");
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
        printf("���ڣ�Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ:%d\n",sums/y1,sumr/y1);
    else
        printf("�޽�����Ϣ\n");
    if(y2!=0)
        printf("������:Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ:%d\n",sumsf/y2,sumrf/y2);
    else
        printf("�޸�������Ϣ\n");
    if(y3!=0)
        printf("��ʦ:Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ:%d\n",sumsg/y3,sumrg/y3);
    else
        printf("�޽�ʦ��Ϣ\n");
    if(y4!=0)
        printf("����:Ӧ������ƽ��ֵ:%d ʵ������ƽ��ֵ��%d",sumsl/y4,sumrl/y4);
    else
        printf("��������Ϣ\n");
    printf("�����������\n");
    getch();analyze();
}


void changeData()//�ı���Ϣ�˵�
{
    system("cls");
    printf("1 ���ݹ����޸�\n");
    printf("2 ���������޸�\n");
    printf("3 ���ݹ���ɾ��\n");
    printf("4 ����\n");
    char k;
    scanf("%s",&k);
    switch(k)
    {
        case '1':changebynum();break;
        case '2':changebyname();break;
        case '3':deletebynum();break;
        case '4':mainamnu();break;
        default:{printf("�������");Sleep(200);changeData();break;}
    }
}
void changebynum()//���Ÿı�
{
    int c;
    printf("���빤��");
    scanf("%d",&c);
    int j,i;
    int a;
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==c){
        printf("ta�Ļ�����Ϣ��������%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("��ϢѧԺ ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
    }
    }
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==c)
        {
            printf("������Ϣ���·ݣ���%d �������ʣ�%d Ӧ�����ʣ�%d ʵ�����ʣ�%d \n",wag[j].tmonth,wag[j].fundwage,wag[j].shouldpay,wag[j].realypay);
        }
    }
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==c)
        {
          a=i;
          printf("���¸�ֵ��");
          printf("\n��������:");
          scanf("%s",&tec[i].tname);
          printf("\n����Ժϵ��");
          scanf("%s",&tec[i].tdep);
          printf("\n����ְ�ƣ�");
          scanf("%s",&tec[i].tclass);
          //printf("�޸ĳɹ���");
        }
    }
    printf("�����·�\n");
    int rtre;
    scanf("%d",&rtre);
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==c)
        {
            if(wag[j].tmonth==rtre){
            printf("���¸�ֵ��\n");
            printf("����������ʣ�");
            scanf("%d",&wag[i].fundwage);
            printf("���������");
            scanf("%d",&wag[i].addwage);
            printf("����۳���");
            scanf("%d",&wag[i].diffwage);
            wag[i].shouldpay=wag[i].fundwage+wag[i].addwage;//yin fa gongZ
            wag[i].realypay=wag[i].shouldpay-wag[i].diffwage;
            printf("�޸ĳɹ���");
            }
        }
    }
    write_to_file();
    inputtofile();
    printf("�����������");
    getch();changeData();

}
void changebyname()//��������
{
    printf("����������");
    char c[20];
    scanf("%s",&c);
    int i,j;
    for(i=0;i<num;i++)
    {
        if(strcmp(tec[i].tname,c)==0)
        {
            printf("ta�Ļ�����Ϣ�����ţ�%d\n",tec[i].tnumber);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("��ϢѧԺ ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
            for(j=0;j<numw;j++)
            {
                if(tec[i].tnumber==wag[j].tnumbers)
                {
                    printf("�������ʣ�");
                    printf("%d",wag[j].fundwage);
                    printf("������");
                    printf("%d",wag[j].addwage);
                    printf("�۳����ʣ�");
                    printf("%d",wag[j].diffwage);
                }
            }
        }
    }
    int fir,sec;
    printf("\n���빤��:\n");
    scanf("%d",&fir);
    printf("�����·ݣ�");
    scanf("%d",&sec);
    for(i=0;i<num;i++)
    {
        if(tec[i].tnumber==fir)
        {
            printf("����ְ�ƣ�");
            scanf("%s",&tec[i].tclass);
            printf("����Ժϵ��");
            scanf("%s",&tec[i].tdep);
        }
    }
    for(j=0;j<numw;j++)
    {
        if(wag[j].tnumbers==fir){
            if(wag[j].tmonth==sec){
        printf("����������ʣ�");
        scanf("%d",&wag[j].fundwage);
        printf("���������");
        scanf("%d",&wag[j].addwage);
        printf("����۳����ʣ�");
        scanf("%d",&wag[j].diffwage);
        }
        }
    }
    write_to_file();
    inputtofile();//д��
    printf("�����������");
    getch();
    changeData();
}
void deletebynum()//�����//ɾ����Ҫ��ǰһ������һ��������
{
    int i,j,r,t;
    int nums;
    int k=0;
    printf("����Ҫɾ���Ĺ��ţ�");
    scanf("%d",&nums);
    for(i=0;i<num;i++)//���������Ϣ
    {
        if(nums==tec[i].tnumber)
        {
            printf("ta�Ļ�����Ϣ��������%s\n",tec[i].tname);
            if(strcmp(tec[i].tdep,"1")==0)
            printf("��ϢѧԺ ");
        else if(strcmp(tec[i].tdep,"2")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"3")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"4")==0)
            printf("��ѧԺ ");
        else if(strcmp(tec[i].tdep,"5")==0)
            printf("����ѧԺ");

        if(strcmp(tec[i].tclass,"1")==0)
            printf(" ���� ");
        else if(strcmp(tec[i].tclass,"2")==0)
            printf(" ������  ");
        else if(strcmp(tec[i].tclass,"3")==0)
            printf(" ��ʦ ");
        else if(strcmp(tec[i].tclass,"4")==0)
            printf(" ���� ");
        }
    }
    for(i=0;i<numw;i++)
    {
        if(nums==wag[i].tnumbers)
        {
            printf("�·ݣ�%d �������ʣ�%d Ӧ�����ʣ�%d ʵ�����ʣ�%d ",wag[i].tmonth,wag[i].fundwage,wag[i].shouldpay,wag[i].realypay);
        }
    }
    printf("ȷ��ɾ����\n����yȷ�ϣ�n����");
    char qwqqw='c';
    while(1){//ȷ��ѭ��
    scanf("%c",&qwqqw);
    if(qwqqw=='y')
        break;
    else if(qwqqw=='n')
    changeData();
    else
    printf("�������");
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
    printf("ɾ����ɣ�");
    printf("�����������");
    getch();changeData();
}


void judge(int j,int flag,int month)//�ж��Ƿ��Ѿ�����
{   int bolean=0;
    if(flag==0){
    for(int i=0;i<num;i++)
    {
        if(j==tec[i].tnumber)//�жϹ���
        {
            printf("�˺����Ѿ����ֹ���\n");
            printf("�����ǣ�%s\n",tec[i].tname);
            printf("�����������\n");
            getch();
            inputData();
        }
    }
    }
    else
    {
        for(int i=0;i<numw;i++)
        {
            if(j==wag[i].tnumbers)//�жϹ���
            {
                if(month==wag[i].tmonth)
                    printf("����·��Ѿ����ֹ���\n");
                    printf("�������ʣ�%d\n",wag[i].fundwage);
                    printf("�����������\n");
                    getch();
                    inputData();}}
     for(int d=0;d<num;d++){
            if(j==tec[d].tnumber)
                bolean=1;}
     if(bolean==0)
        {printf("û�д˹���\n�����������\n");getch();inputData();}}}
//order(tec);
void order()
{
    int i, j, temp;
    char ad[20],af[20],ag[20];//ð�������㷨������ n-1 �ֱȽ�
    for(i=0; i<num-1; i++){//ÿһ�ֱȽ�ǰ n-1-i ����Ҳ����˵���Ѿ�����õ���� i �����ñȽ�
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
