#include <stdio.h>
struct Teacher{
int number;
char name;
char dep;
char clasa;
}tec[6];
int main(){
    tec[3].number=100;
    tec[1].number=103;
    tec[2].number=132;
    tec[0].number=143;
    tec[0].name='w';
    tec[1].name='f';
    tec[2].name='d';
    tec[3].name='t';
    int i, j, temp;
    char ad;//ð�������㷨������ n-1 �ֱȽ�
    for(i=0; i<3; i++){//ÿһ�ֱȽ�ǰ n-1-i ����Ҳ����˵���Ѿ�����õ���� i �����ñȽ�
        for(j=0; j<3-i; j++){
            if(tec[j].number > tec[j+1].number){
                temp = tec[j].number;
                ad = tec[j].name;
                tec[j].number= tec[j+1].number;
                tec[j].name=tec[j+1].name;
                tec[j+1].number= temp;
                tec[j+1].name=ad;
            }
        }
    }

    //�������������
    return 0;
}

