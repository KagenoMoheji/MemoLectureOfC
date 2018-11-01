## 課題2(CalcFromCommandInput.c，CalcFromCommandInputSimple.c)
### 問題文
任意の個数の文字列を入力すると、その合計と平均を表示するプログラムを作ってください。
- 条件
    - 入力はコンマかスペースでつなぎます。例）1,2,3
    - Q以外の文字が出た場合は、エラーメッセージを表示させて、処理を繰り返してください。
### 実行例
```
$ ./a.out
Input numbers: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
Sum: 55
Average: 5.5
Input numbers: 100, 200, 300
Sum: 600
Average: 200
Input numbers: abc
IOERROR: Input only numbers. Ex) 1, 2, 3
Input numbers: Q
Bye
$ 
```
