#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define CHARBUFF 256

/*
client
http://www.geekpage.jp/programming/linux-network/http-client.php
*/

int main(void){
	// ソケットの定義
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	
	// ソケット情報の設定
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(12345);
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); // IPアドレスの設定
	
	// ソケットに接続
	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0){
		char buf[CHARBUFF];
		int read_n = 0; // データ受信成功フラグ
		while(1){
			/*
			標準入力の内容をサーバに送信
			*/
			memset(buf, 0, sizeof(buf));
			printf("Input: ");
			fgets(buf, sizeof(buf), stdin);
			buf[strlen(buf)-1] = '\0';
			write(sock, buf, sizeof(buf));
			
			/*
			サーバから受信した内容を標準出力
			https://www.ibm.com/support/knowledgecenter/ja/SSLTBW_2.2.0/com.ibm.zos.v2r2.bpxbd00/rtrea.htm#rtrea
			*/
			memset(buf, 0, sizeof(buf));
			read_n = read(sock, buf, sizeof(buf));
			if(read_n < 0){
				// 受信に問題あり？
			}else if(read_n == 0){
				printf("接続が切れました\n");
				break;
			}else{
				printf("ServerResponse: %s\n", buf);
			}
		}
	}else{
		printf("接続失敗\n");
	}

	
	close(sock);

	return 0;

	
}
