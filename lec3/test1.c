#include <stdio.h>
#include <string.h>
#include <stdlib.h> // atoi(), abs()
//#include <ctype.h> // isdigit()
#define CHARBUFF 256

int main(void){
    char input[CHARBUFF];
    int inputX, inputY;
    char strCounter[4]="1st";
    int x[3], y[3];
    int errFlag = 0; // エラーが生じた場合のフラグ

    int i, coordinateIndex = 0;
    for(i=0; i<3; i++){
        if(i==1){
            sprintf(strCounter,"2nd");
        }else if(i==2){
            sprintf(strCounter,"3rd");
        }

        printf("Set the %s coordinate like '(13,2)': ", strCounter);
        fgets(input, CHARBUFF, stdin);

        /*
        ●sscanfで安全な数値代入をする方法
        https://qiita.com/7of9/items/d1cf45fcd0f798882d8f
        */
        if(sscanf(input, "(%d,%d)", &inputX, &inputY)<1){
            printf("Input is not Integer, or not Correct.\n");
            errFlag = 1;
            break;
        }
        //printf("%d, %d\n", inputX, inputY);

        x[coordinateIndex] = inputX;
        y[coordinateIndex++] = inputY;
    }

    if(!errFlag){
        int gX = (x[0]+x[1]+x[2])/3;
        int gY = (y[0]+y[1]+y[2])/3;
        int s = abs(((x[0]-x[2])*(y[1]-y[2])-(x[1]-x[2])*(y[0]-y[2])))/2;

        printf("(%d,%d), (%d,%d), (%d,%d)について，\n", x[0], y[0], x[1], y[1], x[2], y[2]);
        printf("重心: (%d, %d)\n", gX, gY);
        printf("面積: %d\n", s);
    }

    return 0;
}