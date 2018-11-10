#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHARBUFF 256
#define LEN(arr) sizeof(arr)/sizeof(*arr)

typedef struct{
	char id[9];
	int score;
}Record;

void sortRecordsByScore(Record*, int);

int main(void){
	FILE *fp = fopen("Lesson07.txt", "r");
	if(fp==NULL){
		printf("Can't found file\n");
		return EXIT_FAILURE;
	}

	Record records[CHARBUFF];
	int lenID = LEN((*records).id);
	int recCnt = 0; // 格納されたレコードの数

	while(fscanf(fp, "%s\t%d", records[recCnt].id, &records[recCnt].score)!=EOF){
		records[recCnt].id[lenID-1] = '\0'; // ※※文字列の末尾に必ず終端文字を！※※
		recCnt++; // recCnt=配列の最後のインデックスなので、長さではないため、forの範囲などにて注意。
	}

	fclose(fp);


	sortRecordsByScore(records, recCnt);


	/*
	出力
	*/
	int i;
	for(i=0; i<recCnt; i++){
		printf("%s\t%d\n", records[i].id, records[i].score);
	}


	return 0;
}


/*
スコア順にソートする関数
*/
void sortRecordsByScore(Record *records, int recCnt){
	int i, j;
	int nTmp;
	char strTmp[9];
	/*for(i=0; i<recCnt-1; i--){
		for(j=i+1; j<recCnt; j++){
			if(records[i].score > records[j].score){
				// アロー記述では「(records+i)->score」、ほかにも「(*(records+i)).score」という書き方でも可能。
				// ↓配列でポインタにアクセスしたらポインタではないのでアロー記述は無効！↓
				// https://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q13144909248
				nTmp = records[i].score;
				sprintf(strTmp, "%s", records[i].id); // ただの＝での代入はchar*の互換によりできない！
				records[i].score = records[j].score;
				sprintf(records[i].id, "%s", records[j].id);
				records[j].score = nTmp;
				sprintf(records[j].id, "%s", strTmp);				
			}
		}
	}*/


	/*学籍番号順にもしておくならこっち。*/
	for(i=recCnt; i>=0; i--){
		for(j=0; j<recCnt-1; j++){
			if(records[j].score > records[j+1].score){
				nTmp = records[j].score;
				sprintf(strTmp, "%s", records[j].id);
				records[j].score = records[j+1].score;
				sprintf(records[j].id, "%s", records[j+1].id);
				records[j+1].score = nTmp;
				sprintf(records[j+1].id, "%s", strTmp);				
			}
		}
	}
}
