#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CHARBUFF 256
#define ALPHACNT 26

int wordCount(char*);
// int countCharArray(char*);
void countChars(char*, int*, char*);
int find(char, char*);
void sortChars(char*, int*);

int main(void){
    char input[CHARBUFF];
    char alphas[ALPHACNT] = {'\0'}; // アルファベットの数だけ． // 要素数をカウントするためゼロ初期化する．
    int cnts[ALPHACNT];
    
    printf("Input: ");
    fgets(input, CHARBUFF, stdin);
    input[strlen(input)-1] = '\0';

    // 単語のカウント
    int wordscnt = wordCount(input);
    // アルファベットごとの出現回数のカウント
    countChars(alphas, cnts, input);
    // 出現回数順，アルファベット順にソート
    sortChars(alphas, cnts);

    // 出力
    int i;
    for(i=0; i<strlen(alphas); i++){
        printf("%c(%c): %d\n", alphas[i], toupper(alphas[i]), cnts[i]);
    }
    printf("Word count: %d\n", wordscnt);

    return 0;
}


/*
単語の数をカウントする．
*/
int wordCount(char* input){
    int cnt = 0;
    while(*input != '\0'){
        if(*input++ == ' ') cnt++;
    }
    return cnt+1;
}


/*
これ「\0」までカウントだしstrlenとほぼ同じか．
※注意！※
関数に配列を”ポインタとして”渡した場合，その引数の長さは配列ではなく型の長さになってしまう．
だから，（過去にも合ったように）関数に渡す前に長さを求め，引数に長さの変数も渡すことを考えるべき．
*/
/*int countCharArray(char* alphas){
    int len = 0;
    while(*alphas != '\0'){
        len++;
        alphas++;

        if(len == ALPHA){ // char[n]で指定した長さnに等しくなった場合，抜ける．
            break;
        }
    }
    return len;
}*/


/*
アルファベットごとの出現回数をカウントする．
*/
void countChars(char* alphas, int* cnts, char* input){
    /*while(*input != '\0'){
        
    }*/
    int input_i,i;
    int len = strlen(input);
    char c;
    int alphas_i = 0, find_i; // alphasの初期長さが6っぽいので，「strlen(alphas)-1」とか期待できない．
    for(input_i=0; input_i<len; input_i++){
        c = tolower(input[input_i]);
        if(isalpha(c)){ // アルファベットか，区切り文字か
            find_i = find(c, alphas);
            if(find_i == -1){ // alphas配列に探索対象のアルファベットが無かった場合
                alphas[alphas_i] = c;
                cnts[alphas_i++] = 1;
            }else{
                cnts[find_i]++;
            }
        }
    }
}


/*
アルファベットの配列に目標のアルファベットが含まれているかを調べる．
[戻り値]
●含まれていた場合，そのインデックス．
●含まれていない場合，-1．
*/
int find(char c, char* alphas){
    int alphas_i;
    int len = strlen(alphas);
    for(alphas_i=0; alphas_i<len; alphas_i++){
        if(c == alphas[alphas_i]){
            return alphas_i;
        }
    }
    return -1;
}


/*
バブルソートで頻度順orアルファベット順に並べ替え
*/
void sortChars(char* alphas, int* cnts){
    char tempC;
    int tempI;
    int i,j;
    int len = strlen(alphas);
    for(i=0; i<len; i++){
        for(j=len-1; i<j; j--){
            if(cnts[j-1] <= cnts[j]){ // 左の方が右の回数以下の場合
                if(cnts[j-1] == cnts[j]){ // 頻度が同じ場合
                    if(alphas[j-1] < alphas[j]){ // 左のほうがアルファベット順で小さかったら置換不要
                        continue;
                    }
                }
                
                // 左のほうが右より頻度が少ない，もしくはアルファベット順で左が大きかった場合
                tempC = alphas[j];
                tempI = cnts[j];

                alphas[j] = alphas[j-1];
                cnts[j] = cnts[j-1];
                alphas[j-1] = tempC;
                cnts[j-1] = tempI;
            }
        }
    }
}