#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define CHARBUFF 256

/*
server
http://www.geekpage.jp/programming/linux-network/http-server.php
http://blog.majide.com/2009/02/socket-programming-server/
*/

int main(void){
	// ソケットの定義
	int serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	// ソケット情報を設定
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY; // IPアドレスの設定

	bind(serv_sock, (struct sockaddr *)&addr, sizeof(addr));

	// ポート解放※5回通信試行する？
	listen(serv_sock, 5);
	
	printf("接続要求中\n");
	
	// クライアントとの接続
	struct sockaddr_in client;
	int len = sizeof(client);
	int client_sock = accept(serv_sock, (struct sockaddr *)&client, &len);

	printf("接続完了\n");

	char buf[CHARBUFF];
	int read_n = 0; // データ受信成功フラグ
	while(1){
		/*
		クライアントから受信した内容を送信．
		*/
		memset(buf, 0, sizeof(buf));
		read_n = read(client_sock, buf, sizeof(buf));
		if(read_n < 0){
			// 受信に問題あり？
		}else if(read_n == 0){
			printf("接続が切れた\n");
			break;
		}else{
			write(client_sock, buf, strlen(buf));
		}
	}
	
	close(client_sock);
	close(serv_sock);

	return 0;
}
