#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define CHARBUFF 256
#define SLEEPTIME 3 // sleepする秒数

union semun {
    int val;
    struct semid_ds *buf;
    int *array;
};

int main(int argc, char *argv[]){
    /* プロセス関連 */
    int id = atoi(argv[1]); // プロセスIDではないID(子プロセスのプロセスIDが異なれば加算)
    /* ファイル関連 */
	FILE *fp;
	char *fileName = "pid.txt"; // ファイル名
	/* セマフォ関連 */
	union semun arg;
	key_t key;
	int semid;
    struct sembuf sb;
    /* その他 */
    int i; // ループ回数i
    int psum = 0; // 今回の子プロセスで出現した合計値
    int fsum = 0; // ファイルから取得した合計値

    /* セマフォの初期化 */
    if((key = ftok("sem.dat", 'S')) == -1){
		perror("ftok");
		exit(1);
	}
	if ((semid = semget(key, 1, 0666 | IPC_CREAT)) == -1) {
        perror("semget");
        exit(1);
    }
    arg.val = 1; // ここで定員設定
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    /* Lock */
	sb.sem_op=-1;
	if(semop(semid, &sb, 1) == -1){
		perror("(L)semop");
		exit(1);
	}

    /* ファイルからの読み込み・表示 */
    fp = fopen(fileName, "r");
	fscanf(fp, "%d", &fsum);
	fclose(fp);

    /* sleep */
	sleep(SLEEPTIME);

    /* このへんで計算．加算とか．そうしてファイル上書き */
	for(i=id*10000+1; i<((id+1)*10000); i++){
		psum += i;
	}
    // 再生成
	fp = fopen(fileName, "w");
    printf("(c)%d + %d = %d\n", fsum, psum, fsum+psum);
    fsum += psum;
    fprintf(fp, "%d\n", fsum);
	fclose(fp);

	/* Unlock */
	sb.sem_op=1;
	if(semop(semid, &sb, 1) == -1){
		perror("(U)semop");
		exit(1);
	}

    return 0;
}