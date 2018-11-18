## 別講義の課題(tail.c)
### 問題文
tailコマンドを実装せよ．ただしオプションは考えなくても良い．
### 仕様
- オプション実装  
※オプションと入力の間にスペース必須．  
※コマンド引数において，読み込みファイルのあとにオプションを書くこと．
    - [-n N]  
    ・最後からN行だけ表示させる．  
    ・指定なし（デフォルト）で10行．
    
### 実行例
```
$ ./a.out tail_readme.txt
コマンドです．
And this program can work 
with multi-byte-characters.
そしてこれはマルチバイト
文字があっても使用可能です．
But we should keep a rule 
that we should add a break 
at the last line.
ただし，最後の行には改行を加えておくという
ルールを守っておく必要があります．
$ ./a.out tail_readme.txt -n 3
at the last line.
ただし，最後の行には改行を加えておくという
ルールを守っておく必要があります．
$
```