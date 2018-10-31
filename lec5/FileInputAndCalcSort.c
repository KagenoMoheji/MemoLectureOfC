#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN(arr) sizeof(arr)/sizeof(*arr)
#define CHARBUFF 256

void sortAsc(int*, int);
double getMedian(int*, int);

int main(void){
	/*
	読み込むファイルの指定．
	*/
	FILE *fp = fopen("Lesson5.txt", "r");
	if(fp==NULL){
		printf("Can't found file\n");
		return -1;
	}

	char str[CHARBUFF];
	if((fgets(str, LEN(str), fp))!=NULL){ // これで1行読み込みできている．
		/*
		行の終端の設定
		*/
		char *p = strchr(str, (int)'\n'); // 「\n」を分割文字として探索．
		if(p != NULL){ // 「\n」の直後が空だったら「\n」をNULL文字に置換．
			*(p-1) = '\0';
		}


		/*
		合計値を求めつつ，要素数を数える
		*/
		char temp[strlen(str)+1]; // '\0'も考慮して1個余分に加算．
		// strをstrtokの引数に使っちゃうと，その後のstrがポインタ型として1つのデータしか指さなくなってしまうので，それを避けるためコピーする．
		// tempが身代わりに成ることで変数strはchar配列として使えるままになる．
		// よってこの後に来る2度目のstrtokでstrを使える．（すっきりしないがこのやり方しかなさそう）
		strcpy(temp, str);

		int cnt=0, sum=0;
		char *sp = strtok(temp, "\t"); // 分割関数strtokを使用．ただしtempを引数に使う．
		while(sp != NULL){
			sum += atoi(sp);
			cnt++; // 要素数加算
			
			/* ここで文字列の置換してみたいが実装方法が見つからない…．
			former = atoi(sp-3);
			current = atoi(sp);
			if(former > current)
			*/
			sp = strtok(NULL, "\t");
		}


		/*
		あまりすっきりしないが・・・int型配列格納のためまたstrtokでループ．
		*/
		int nums[cnt], i=0;
		sp = strtok(str, "\t");
		while(sp != NULL){
			nums[i++] = atoi(sp);

			sp = strtok(NULL, "\t");
		}
		
		sortAsc(nums, cnt);
		double ave = (double)sum/cnt;
		double med = getMedian(nums, cnt);

		/*
		出力
		*/
		printf("average = %.4f\n", ave);
		printf("median = %.4f\n", med);
	}

	/*
	ファイル操作変数を閉じる
	*/
	fclose(fp);

	return 0;
}


/*
int型配列を昇順ソートする関数．
手法はバブルソート．
*/
void sortAsc(int* nums, int len){
	int i, j, tmp;
	for(i=0; i<len-1; i++){
		for(j=i+1; j<len; j++){
			if(nums[i]>nums[j]){
				tmp = nums[j];
				nums[j] = nums[i];
				nums[i] = tmp;
			}
		}
	}
}


/*
中央値を取得する関数
*/
double getMedian(int* nums, int len){
	if(len%2==0){ // 要素数が偶数なら中央2つの平均を取る
		int i;
		i = len/2;
		return (nums[i]+nums[i-1])/2;
	}else{
		return nums[len/2];
	}
}