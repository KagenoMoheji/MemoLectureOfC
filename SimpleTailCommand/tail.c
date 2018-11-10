#include <stdio.h>
#include <string.h>

#define CHARBUFF 256
#define LEN(arr) sizeof(arr)/sizeof(*arr)

int strlen2break(char*);

/*
[参考]
●コマンドライン引数
http://www.wakhok.ac.jp/~kanayama/C/02/node186.html
●fseek()
http://www9.plala.or.jp/sgwr-t/lib/fseek.html
*/
int main(int cinLen, char *cinStr[]){
	FILE *fp;
	if((fp= fopen(cinStr[1], "r"))==NULL){ // ファイルが見つからなかった場合
		printf("Can't find any file!\n");
		return -1;
	}
	
	int setRow = 10; // 読み込む最後の行数
	char buf[setRow][CHARBUFF]; // setRow行分の文字列を格納する
	char line[CHARBUFF];
	int len = LEN(line);
	int len2break = 0; // 各行における，'\n'までの文字数
	int rowNum = 0; // 行数
	int cp = -1; // ファイルにおけるポインタ（最後尾からなので負）

	fseek(fp, cp, SEEK_END);
	if(fgetc(fp)=='\n'){ // -1に改行ならば次にポインタを動かす．0はどのみち'EOF'になる．
		cp--;
	}

	while(rowNum<setRow){
		if(fseek(fp, --cp, SEEK_END)!=0){ // 先頭に到達したらその行を出力して終了
			fseek(fp, cp+1, SEEK_END);
			fgets(line, len, fp);
			len2break = strlen2break(line);
			line[len2break-1] = '\0';
			strcpy(buf[rowNum++], line);
			break;
		}

		if(fgetc(fp)=='\n'){ // 後ろから探索して'\n'が見つかった時
			fseek(fp, cp+1, SEEK_END); // '\n'の直後の文字にポインタを移す
			fgets(line, len, fp);
			len2break = strlen2break(line);
			line[len2break-1] = '\0';
			strcpy(buf[rowNum++], line);
		}
	}

	/*
	ファイル操作の変数を閉じる
	*/
	fclose(fp);

	/*
	出力
	*/
	int i;
	for(i=rowNum-1; 0<=i; i--){
		printf("%s\n", buf[i]);
	}

	return 0;
}

/*
'\n'までの文字数をカウントする．
※'\n'もカウントに含む．
*/
int strlen2break(char *line){
	int cnt = 0;
	while(1){
		if(*(line++)=='\n') return cnt+1;
		cnt++;
	}
}
