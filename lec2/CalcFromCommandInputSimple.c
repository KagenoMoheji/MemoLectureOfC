#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define CHARBUFF 124

int main(void){
	char input[CHARBUFF];
	char delimiter[]=":, ";
	char *splitted_p;
	int elem_num, sum, ave;
	int errFlag; //最後にエラー処理するかのフラグ．

	while(1){
		elem_num=0, sum=0, ave=0, errFlag=0;

		printf("Input numbers: ");
		fgets(input,CHARBUFF,stdin);
		input[strlen(input)-1]='\0';
		
		// Quitかどうか。
		if(!strcmp(input,"Q")){
			printf("Bye\n");
			break;
		}

		/*
		http://www9.plala.or.jp/sgwr-t/lib/strtok.html
		*/
		splitted_p=strtok(input,delimiter);// 1つ目
		while(splitted_p != NULL){
			/*
			https://bituse.info/c_func/21
			http://marycore.jp/prog/cpp/convert-string-to-char/#std%3A%3Astring%20%E2%86%92%20char
			*/
			if(isdigit(splitted_p[0])){
				sum+=atoi(splitted_p);
				elem_num++;
			}else{
				errFlag=1;
				break;
			}

			splitted_p=strtok(NULL, delimiter);//2つ目以降
		}
		
		//出力
		if(!errFlag){
			printf("Sum: %d\n",sum);
			ave=sum/elem_num;
			printf("Ave: %d\n",ave);
		}else{
			printf("IOERROR: Input only numbers. Ex)1,2,3\n");
			break;
		}
	}

	return 0;
}