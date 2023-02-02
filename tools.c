#include "tools.h"

static Date dateRightNow;

void printCenter(const char msg[300], int line){
    int col, row;
    col = getmaxx(stdscr);		/* get the number of rows and columns */
    mvprintw(line,(col-strlen(msg))/2,"%s",msg);
}


bool isNumber(char c){
    return (c >= '0' && c <= '9');
}


bool isLetter(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isOkStr(const char str[]){
    for(int i = 0; str[i] != '\0'; i++)
        if(!(isNumber(str[i]) || isLetter(str[i]) || str[i] == '.' || str[i] == '!' || str[i] == '-' || str[i] == '_' || str[i] == '?')){
            printf("%s : %d", str, str[i]);
            return 0;
        }
    return 1;
}

void setTime(Date date){
    dateRightNow = date;
}

Date *getTime(){
    return &dateRightNow;
}

int minusTimes(Date d1, Date d2) {//return minus in hours (d1 - d2)
    return ((((d1.year - d2.year) * 12 + d1.month - d2.month) * 30 - d1.day - d2.day) * 24 + d1.time / 100 -
            d2.time / 100);
}
