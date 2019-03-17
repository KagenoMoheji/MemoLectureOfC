#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define CHARBUFF 256
#define RNDLENGTH 3 // rand()で求める整数の範囲（1以上RNDLENGTH以下）

int exist(int, int*, int);

int main(void){
	/* プロセス関連 */
	int cpids[RNDLENGTH+1] = {0}; // (親プロセスを0番目として)子プロセスのプロセスIDのリスト
	int cpids_i = 0; // cpidsのインデックス
	int id = 0; // プロセスIDではないID（子プロセスのプロセスIDが異なれば加算）
	int pret; // fork()の戻り値
	int n; // 乱数によって決定するプロセス数n
	int status; // 子プロセスの状態
	/* ファイル関連 */
	FILE *fp;
	char *fileName = "pid.txt"; // ファイル名
	/* その他 */
	char args[CHARBUFF]; // execlの第3引数に渡す子プロセスのコマンドライン入力
	int i; // ループ回数i
	int sum = 0;

	/* 共有メモリとしてのファイルへの初期値書き出し */
	fp = fopen(fileName, "w");
	fprintf(fp, "%d\n", 0);
	fclose(fp);
	
	/* 乱数で子プロセスの数nを決定 */
	srand(time(NULL));
	n = rand() % RNDLENGTH + 1;
	printf("n = %d\n", n);

	/* 親プロセスを0番目に格納 */
	cpids[cpids_i++] = getpid();

	/* fork */
	for(i=0; i<n; i++){
		if((pret=fork()) == 0){ // n個の子プロセスを生成．
			sprintf(args, "%d", id);
			printf("id: %d\n", id);

			/* 子プロセスの実行 */
			if(execl("child", "child", args, NULL) < 0){
				perror("execl");
				exit(1);
			}
		}else if(pret > 0){
			wait(&status);

			if(WIFEXITED(status)){
				//printf("(p)子プロセスは終了ステータス%dで正常終了\n", WEXITSTATUS(status));
				if(!exist(pret, cpids, cpids_i)){ // プロセスIDが異なっている場合
					cpids[cpids_i++] = pret;
					// ここでIDの加算
					id++;
				}
			}
			if(WIFSIGNALED(status)){
				printf("(p)子プロセスはシグナル番号%dで終了\n", WTERMSIG(status));
			}
		}else{
			perror("fork");
			exit(1);
		}
	}

	/* 合計の表示 */
	fp = fopen(fileName, "r");
	fscanf(fp, "%d", &sum);
	printf("(p)sum = %d\n", sum);
	fclose(fp);

	return 0;
}

/*
@func
cpidsリストに同じプロセスIDが存在しているかを判定する．
@param(newChildID) 新しく生成した子プロセスのプロセスID．
@param(cpids) 過去に生成されたプロセスのプロセスID．
@param(cpids_i) cpidsのインデックス．
@return cpidsにnewChildIDと一致するものがあったら1．
*/
int exist(int newChildID, int *cpids, int cpids_i){
	int i;
	for(i=0; i<=cpids_i; i++){
		if(cpids[i] == newChildID){
			return 1;
		}
	}
	return 0;
}