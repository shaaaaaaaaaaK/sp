//使用chatGPT做成的
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 自定义的输入缓冲区
#define BUFFER_SIZE 100
char buffer[BUFFER_SIZE];
int buffer_index = 0;       //建立一個緩衝區

int getch() {               //讀取數值
    if (buffer_index == 0) {//緩衝區為0時開始讀取輸入的值
        fgets(buffer, BUFFER_SIZE, stdin);
    }

    char ch = buffer[buffer_index];
    buffer_index++;         //讀取下一位的值
    
    if (buffer[buffer_index] == '\0' || buffer[buffer_index] == '\n') {//讀取到 \0 或 \n 時結束
        buffer_index = 0;   //緩衝區數值歸零
    }
    
    return ch;
}

int my_scanf(const char *format, int *value) {
    char ch;
    int sign = 1, num = 0, read_digits = 0;
    
    do {
        ch = getch();       
    } while (isspace(ch));  //先讀取一次數值，如果是空格就繼續讀取下一位，直到讀到數值爲止
    
    if (ch == '-') {
        sign = -1;          //讀到 - 的時候將sign變爲-1，以便在後面將其轉爲負數
        ch = getch();       //繼續讀取下一位數值
    }
    
    while (isdigit(ch)) {   //當讀到數字字符時重複下列動作
        num = num * 10 + (ch - '0');    //因爲數字字符會轉爲ASCII碼，所以要先減去0的ASCII碼，將其轉換爲整數而不是字符，再轉爲十進制
        ch = getch();
        read_digits = 1;    //確認有讀到數字
    }
    
    if (!read_digits) {     //如果沒有讀到數字就return 0
        return 0;
    }
    
    *value = sign * num;    //確認正負數
    return 1;
}

int main() {
    int number;
    printf("请输入一个整数: ");
    
    if (my_scanf("%d", &number)) {
        printf("你输入的整数是: %d\n", number);
    } else {
        printf("输入无效！\n");
    }
    
    return 0;
}
