#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN(arr) sizeof(arr)/sizeof(*arr)
#define CHARBUFF 256
#define MAXSIZE 1024

typedef struct{
	char id[10]; // ※※※fgetsにおける\nが含まれてしまうことと，終端文字も考慮して2文字余分に確保．
	int score;
}Record;

int getScore(Record*, int, char*);

int main(void){
	FILE *fp = fopen("Lesson6.txt", "r");
	if(fp==NULL){
		printf("Can't found file\n");
		return -1;
	}

	Record records[MAXSIZE];
	int len_id = LEN((*records).id); // 終端文字を挿入するため配列の長さを取得しておく
	char str[CHARBUFF];
	int recordsCnt = 0;
	/* 実装方法①：sscanfを用いる．
	while((fgets(str, LEN(str), fp))!=NULL){ // 1行読み込み
		/*char *p = strchr(str, (int)'\n'); // 「\n」を分割文字として探索．
		if(p != NULL){ // 「\n」の直後が空だったら「\n」をNULL文字に置換．
			*(p-1) = '\0';
		}*

		//printf("(str)%s\n",str); // 確認用
		//printf("(null?)%s\n",(str[strlen(str)]=='\0') ? "true":"false"); // 確認用（strとnullの間になぜか1文字増えている案件）
		
		sscanf(str, "%s\t%d", records[recordsCnt].id, &(records[recordsCnt].score)); //
		records[recordsCnt].id[len_id-1]='\0'; // ※※※終端文字を追加※※※
		printf("%s: %d\n", records[recordsCnt].id, records[recordsCnt].score);

		recordsCnt++;
	}
	*/

	/* 実装方法②：fscanfを用いる．
	http://www.isl.ne.jp/pcsp/beginC/C_Language_16.html
	*/
	while(fscanf(fp, "%s\t%d", records[recordsCnt].id, &(records[recordsCnt].score)) != EOF){
		records[recordsCnt].id[len_id-1]='\0';  // ※※※終端文字を追加※※※
		//printf("%s: %d\n", records[recordsCnt].id, records[recordsCnt].score); // 確認用
		recordsCnt++;
	}


	/*
	ファイル操作変数を閉じる
	*/
	fclose(fp);


	/*
	ここから下が標準入力＆探索
	*/
	char inputID[len_id]; // 学籍IDを格納する構造体変数と同じ長さにする．
	int score = 0;
	while(1){
		/*
		標準入力
		*/
		printf("ID: ");
		fgets(inputID, len_id, stdin);
		inputID[strlen(inputID)-1] = '\0'; // 改行を除去

		score = getScore(records, recordsCnt, inputID);

		/*
		標準出力
		*/
		if(score==-1){
			printf("該当する学籍IDは存在しませんでした．\n");
		}else{
			printf("Score: %d\n", score);
		}
	}

	return 0;
}


/*
指定された学籍IDのスコアを取得する．
*/
int getScore(Record* records, int recordsCnt, char* inputID){
	int i;
	for(i=0; i<recordsCnt; i++){
		if(!strcmp(records[i].id, inputID)){
			return records[i].score;
		}
	}
	return -1;
}