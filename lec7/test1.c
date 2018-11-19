#include <stdio.h>
#include <string.h>

#define ARRMAXSIZE(arr) sizeof(arr)/sizeof(*arr)

typedef struct{
    int rowNum, maxCSize;
}FileInfo;
typedef struct{
    char id[6];
    char isF;
    int scoreA, scoreB;
}ScoreData;

void preGetFileInfo(FILE*, FileInfo*);

int main(void){
    /*
    ファイルの読み込み
    */
    FILE *fp = fopen("Lesson08_1.txt", "r");
    if(fp==NULL){
        printf("Can't find file!\n");
        return -1;
    }


    /*
    ファイル構成の取得（前処理）
    */
    FileInfo fi;
    preGetFileInfo(fp, &fi);


    /*
    テキストファイルからのデータ読み込み
    [！注意！]
    ●fscanf()において，カンマ区切りのファイルを読み込む場合の，文字列の取得の仕方は特殊！
    (参考)
    https://qiita.com/oh-thevenin/items/6cbdd5081a4b31e41127
    https://edu.clipper.co.jp/pg-2-36.html
    */
    fseek(fp, 0, SEEK_SET); // preGetFileInfoによりファイル内のポインタが移動されているのでファイルの先頭に戻す．
    ScoreData sds[fi.rowNum];
    int rowCnt = 0;
    int idLen = ARRMAXSIZE(sds[0].id);
    while(fscanf(fp, "%[^,],%c,%d,%d", sds[rowCnt].id, &sds[rowCnt].isF, &(sds[rowCnt].scoreA), &(sds[rowCnt].scoreB)) != EOF){
        sds[rowCnt].id[idLen-1] = '\0';
        rowCnt++;
    }


    /*
    講義Aと講義Bの総合点を求める．
    */
    rowCnt = 0;
    double sumA=0, sumB=0;
    while(rowCnt < fi.rowNum){
        sumA += sds[rowCnt].scoreA;
        sumB += sds[rowCnt].scoreB;
        rowCnt++;
    }


    /*
    平均を求めて出力
    */
    printf("%.1f,%.1f\n", sumA/fi.rowNum, sumB/fi.rowNum);

    return 0;
}


/*
ファイル（構成）情報を取得する前処理
*/
void preGetFileInfo(FILE *fp, FileInfo *fi){
	int rowNum = 0; // 行数
	int cnum = 0; // 1行の文字数　※改行含む
	int maxSize = 0;
	char fc; // ファイルから読み込む1文字

	while((fc=fgetc(fp)) != EOF){ // 1文字ずつ調べる
		if(fc=='\n'){
			// 行の加算
			rowNum++;

			// 最大長の更新
			if(cnum > maxSize){ // 改行の分をここで加算して行の最大長を更新
				maxSize = cnum;
			}
			// 文字数の初期化
			cnum = 0;
		}else{
			cnum++; // ※マルチバイト文字は3byte/文字でカウントされる模様．どのみち余分に確保されるのでこのままで．
		}
	}

	// ファイル（構成）情報の構造体に登録
	fi->rowNum = rowNum;
	fi->maxCSize = maxSize;
}