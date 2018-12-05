#include <stdio.h>
#include <string.h>
#define CHARBUFF 256

int main(void){
	FILE *fp = fopen("Lesson08.txt", "r");
	if(fp==NULL){
		printf("Can't find file!\n");
		return -1;
	}
	
	char attr[CHARBUFF];
	fgets(attr, CHARBUFF, fp); // アトリビュートはここで取得
	attr[strlen(attr)-1] = '\0';
	
	double shortScore;
	double freeScore;
	double shortSum = 0;
	double freeSum = 0;
	int rowCnt = 0; // 行数
	/*
	https://edu.clipper.co.jp/pg-2-56.html
	*/
	while(fscanf(fp, "%*[^,],%*[^,],%lf,%lf\n", &(shortScore), &(freeScore)) != EOF){
		shortSum += shortScore;
		freeSum += freeScore;
		rowCnt++;
	}

	printf("Short = %.2f\nFree = %.2f\n", shortSum/rowCnt, freeSum/rowCnt);

	return 0;
}
