```c
void DOWHILE() {
  int dowhileBegin = nextLabel();//宣告函式的開始
  int dowhileEnd = nextLabel();//宣告函式的結束
  emit("(L%d)\n", dowhileBegin);//呼叫 STMT() 函式來解析迴圈體內的語句
  skip("do");//跳過關鍵字"do"
  STMT();//呼叫 STMT() 函式來解析迴圈體內的語句。
  skip("while");//跳過關鍵字 "while"。
  skip("(");//跳過左括號 "("。
  int e = E();//解析迴圈條件表達式，呼叫 E() 函式來獲取條件表達式的結果。
  emit("if T%d goto L%d\n", e, dowhileBegin);//使用 emit 函式輸出條件判斷，如果條件成立則跳轉回迴圈開始的標籤，否則執行迴圈結束。
  skip(")");//跳過右括號 ")"。
  emit("(L%d)\n", dowhileEnd);//使用 emit 函式輸出迴圈結束的標籤位置 (L%d)。
}
```