```c
void DOWHILE() {
  int dowhileBegin = nextLabel();//�ŧi�禡���}�l
  int dowhileEnd = nextLabel();//�ŧi�禡������
  emit("(L%d)\n", dowhileBegin);//�I�s STMT() �禡�ӸѪR�j���餺���y�y
  skip("do");//���L����r"do"
  STMT();//�I�s STMT() �禡�ӸѪR�j���餺���y�y�C
  skip("while");//���L����r "while"�C
  skip("(");//���L���A�� "("�C
  int e = E();//�ѪR�j������F���A�I�s E() �禡����������F�������G�C
  emit("if T%d goto L%d\n", e, dowhileBegin);//�ϥ� emit �禡��X����P�_�A�p�G���󦨥߫h����^�j��}�l�����ҡA�_�h����j�鵲���C
  skip(")");//���L�k�A�� ")"�C
  emit("(L%d)\n", dowhileEnd);//�ϥ� emit �禡��X�j�鵲�������Ҧ�m (L%d)�C
}
```