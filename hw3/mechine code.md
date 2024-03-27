### Mechine code
```c
1: #include<stdio.h>
2: int power(int x,int y){
3:     if(y==0) {
    ENT  0
    LLA  2
    LI  
    PSH 
    IMM  0
    EQ  
    BZ   0
4:         return 1;
    IMM  1
    LEV 
5:     }
6:     else{
    JMP  0
7:         return x*power(x,y-1);
    LLA  3
    LI  
    PSH
    LLA  3
    LI
    PSH
    LLA  2
    LI
    PSH
    IMM  1
    SUB
    PSH
    JSR  -1370947432
    ADJ  2
    MUL
    LEV
8:     }
9: }
    LEV
10: int main(){
11:     printf("power(3,3)=%d\n", power(3,3));
    ENT  0
    IMM  -1370685280
    PSH
    IMM  3
    PSH
    IMM  3
    PSH
    JSR  -1370947432
    ADJ  2
    PSH
    PRTF
    ADJ  2
12:   return 0;
    IMM  0
    LEV
}
```
