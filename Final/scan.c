#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXNum 100
char temp[MAXNum];
int temp_index=0;

int getChar(){
    if(temp_index == 0){
        fgets(temp, MAXNum , stdin);
    }

    char Char=temp[temp_index];
    temp_index++;

    if(Char == '\0' || Char=='\n'){
        temp_index=0;
    } 

    return Char;
}

int scan(const char *format,int *value){
    char Char;
    int sign=1,num=0,isRead=0;

    do{
        Char=getChar();
    }while (isspace(Char));
    
    if(Char == '-'){
        sign = -1;
        Char = getChar();
    }

    while (isdigit(Char))
    {
        num=num*10 + (Char - '0');
        Char=getChar();
        isRead=1;
    }

    if(isRead==0){
        return 0;
    }

    *value= sign * num;
    return 1;
}

int main(){
    int number;

    printf("輸入數字：\n");
    if(scan("%d",&number)){
        printf("你輸入的數字是：%d\n",number);
    }
    else printf("輸入錯誤\n");
}