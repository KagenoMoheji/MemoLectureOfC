#include <stdio.h>
#include <string.h>
#define CHARBUFF 256

typedef struct{
	char name[CHARBUFF];
	char country[CHARBUFF];
	double total;
}ScoreData;

void sortByScore(ScoreData*, int);

int main(void){
	FILE *fp = fopen("Lesson08.txt", "r");
	if(fp==NULL){
		printf("Can't find file!\n");
		return -1;
	}

	ScoreData sd[CHARBUFF];
	
	char attr[CHARBUFF];
	fgets(attr, CHARBUFF, fp); // アトリビュートはここで取得
	attr[strlen(attr)-1] = '\0';

	/*
	選手名と国名とスコアを構造体リストに読み込み
	*/
	int rowCnt = 0;
	double shortScore, freeScore;
	while(fscanf(fp, "%[^,],%[^,],%lf,%lf\n", sd[rowCnt].name, sd[rowCnt].country, &shortScore, &freeScore) != EOF){
		sd[rowCnt].total = shortScore + freeScore;
		rowCnt++;
	}

	/*
	スコア順にソート
	*/
	sortByScore(sd, rowCnt);
	
	/*
	出力
	*/
	int i;
	for(i=0; i<rowCnt; i++){
		printf("%s %.2lf\n", sd[i].name, sd[i].total);
	}

	return 0;
}


/*
バブルソート
*/
void sortByScore(ScoreData *sd, int len){
	int i, j;
	double dtmp = 0;
	char ntmp[CHARBUFF], ctmp[CHARBUFF];
	for(i=0; i<len-1; i++){
		for(j=i+1; j<len; j++){
			if(((sd+i)->total) < ((sd+j)->total)){
				dtmp = (sd+i)->total;
				sprintf(ntmp, "%s", (sd+i)->name);
				sprintf(ctmp, "%s", (sd+i)->country);
				(sd+i)->total = (sd+j)->total;
				sprintf((sd+i)->name, "%s", (sd+j)->name);
				sprintf((sd+i)->country, "%s", (sd+j)->country);
				(sd+j)->total = dtmp;
				sprintf((sd+j)->name, "%s", ntmp);
				sprintf((sd+j)->country, "%s", ctmp);
			}
		}
	}
}
