#include <stdio.h>
#include <string.h>

#define ARRMAXSIZE(arr) sizeof(arr)/sizeof(*arr)

typedef struct{
    int charNum; // コンマやピリオドはカウントしない．
    int wordNum;
}Counters;

void countCharWord(FILE*, Counters*);

int main(void){
    /*
    ファイルの読み込み
    */
    FILE *fp = fopen("Lesson08_2.txt", "r");
    if(fp==NULL){
        printf("Can't find file!\n");
        return -1;
    }

    Counters cts;
    countCharWord(fp, &cts);


    /*
    出力
    */
    printf("%d,%d\n", cts.charNum, cts.wordNum);

    return 0;
}


/*
文字数・単語数をカウントする
*/
void countCharWord(FILE *fp, Counters *cts){
	char fc; // ファイルから読み込む1文字
    int charNum=0, wordNum=0;

	while((fc=fgetc(fp)) != EOF){ // 1文字ずつ調べる
        //printf("%c",fc);
		if(fc=='\n' || fc==',' || fc=='.'){
            continue;
        }

        if(fc==' '){
            wordNum++;
            continue;
        }
        
        charNum++;
	}

    cts->charNum = charNum;
    cts->wordNum = wordNum+1;
}