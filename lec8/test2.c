#include <stdio.h>
#include <string.h>
#define CHARBUFF 256

typedef struct{
	char name[CHARBUFF];
	char country[CHARBUFF];
	//double shortScore;
	//double freeScore;
}ScoreData;

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
	選手名と国名を構造体リストに読み込み
	*/
	int rowCnt = 0;
	while(fscanf(fp, "%[^,],%[^,],%*lf,%*lf\n", sd[rowCnt].name, sd[rowCnt].country) != EOF) rowCnt++;

	/*
	以下ループ処理
	*/
	char input[CHARBUFF];
	while(1){
		/*
		標準入力
		*/
		printf("Country: ");
		fgets(input, CHARBUFF, stdin);
		input[strlen(input)-1] = '\0';

		/*
		同じ国名を探索して出力
		*/
		int i = 0;
		while(i < rowCnt){
			if(!strcmp(sd[i].country, input)){
				printf("%s\n", sd[i].name);
			}
			i++;
		}
	}
	

	return 0;
}
