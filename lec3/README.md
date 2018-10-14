## 課題2(CountAndSortChars.c)
### 問題文
任意の英文を入力すると、下記の条件に従って、各文字の出現個数を昇順に表示するプログラムを作成してください。
- 条件
    - コンマ、ピリオド、スペースの結果は表示しない。
    - 同じ個数の場合、アルファベット順とする。
    - 大文字・小文字の区別をしない。
### 実行例
```
$ ./a.out
Input: Hello, I am Iio.⏎
i(I): 3
l(L): 2
o(O): 2
a(A): 1
e(E): 1
h(H): 1
m(M): 1
Word count: 4
$ 
```
## テスト対策1(test1.c)
### 問題文
入力された3つの点から成る三角形の重心と面積を出力せよ．  
入力の受け取り方は各自で決めるものとする．
### 実行例(自分の実装に基づく)
```
$ ./a.out
Set the 1st coordinate like '(13,2)': (2,42)
Set the 2nd coordinate like '(13,2)': (13,6)
Set the 3rd coordinate like '(13,2)': (52,33)
(2,42), (13,6), (52,33)について，
重心: (22, 27)
面積: 850
```
### 実行例(入力における数値判定エラー)
```
Set the 1st coordinate like '(13,2)': (3,f)
Set the 2nd coordinate like '(13,2)': (s,3)
Input is not Integer, or not Correct.
```
(x,y)の入力のうちxの場合は数値判定ができているが，yの方でできていない．  
sscanf()の問題だろうか？
