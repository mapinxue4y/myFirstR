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
    char ad;//冒泡排序算法：进行 n-1 轮比较
    for(i=0; i<3; i++){//每一轮比较前 n-1-i 个，也就是说，已经排序好的最后 i 个不用比较
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

    //输出排序后的数组
    return 0;
}

