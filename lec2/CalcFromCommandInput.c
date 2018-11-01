#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHARBUFF 124

int isIntArray(char*, char*);
int isDelimiter(char, char*);
 
int main(void){
	char input[CHARBUFF]; //標準入力を格納する変数．
	char delimiter[]=":, "; // ここで区切り文字を指定．
	char *splitted_p; // strtok()の戻り値であるアドレスを格納する変数．
	int elem_num, sum, ave; //分割後の個数，合計値，平均値

	while(1){
		elem_num=0, sum=0, ave=0;

		printf("Input numbers: ");
		//scanf("%s",input); //これでは空白を読み込めない！！空白が\0になりそこで入力の終わりになってしまう（入力の末端にも\0が自動追記される）．
		fgets(input,CHARBUFF,stdin); //こっちなら空白も1文字として読み込んでくれる．ただし最後に\nが入る．だから…↓
		input[strlen(input)-1]='\0'; //最後の文字を\nから\0に置換する．

		// Quitかどうか。
		if(!strcmp(input,"Q")){
			printf("Bye\n");
			break;
		}

		// 数字・指定の区切り文字以外が含まれていないかどうか．
		if(!isIntArray(input,delimiter)){
			printf("IOERROR: Input only numbers. Ex)1,2,3\n");
			break;
		}

		/*
		http://www9.plala.or.jp/sgwr-t/lib/strtok.html
		*/
		splitted_p=strtok(input,delimiter);// 1つ目
		sum+=atoi(splitted_p);
		elem_num++;

		while(splitted_p != NULL){ //2つ目以降
			splitted_p=strtok(NULL, delimiter);
			
			if(splitted_p!=NULL){
				sum+=atoi(splitted_p);
				elem_num++;
			}
		}
		
		//出力
		printf("Sum: %d\n",sum);
		ave=sum/elem_num;
		printf("Ave: %d\n",ave);
	}

	return 0;
}


/*
渡された文字列に半角数字・指定の区切り文字が含まれていないか判定する．
*/
int isIntArray(char* cArray, char* delimiter){
	char c;
	int i=0;
	int len=strlen(cArray);
	do{
		c=cArray[i];
		if(c<'0' || '9'<c){
			if(!isDelimiter(c,delimiter)){
				return 0;
			}
		}
	}while(++i<len);
	return 1;
}


/*
渡された1文字が区切り文字かを判定する（数字判定はisIntArray()ですでにしてある）．
*/
int isDelimiter(char c, char* delimiter){
	int i;
	int currentNotDelm=1; //delimiterの今の文字と不一致だったら1
	for(i=0;i<strlen(delimiter);i++){
		/*
		https://dixq.net/forum/viewtopic.php?t=4764
		*/
		currentNotDelm=(delimiter[i]!=c);

		if(!currentNotDelm){ //一致する区切り文字だった場合
			break;
		}
	}

	if(currentNotDelm){ //delimiterのいずれとも一致しなかったらcurrentNotDelm=1
		//printf("DelimiterError\n");
		return 0;
	}
	
	return 1;
}