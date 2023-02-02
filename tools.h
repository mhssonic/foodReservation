#include "objects.h"
#ifndef FOODRESERVATION_TOOLS_H
#define FOODRESERVATION_TOOLS_H
#include "curses.h"
#include <string.h>
void printCenter(const char msg[300], int line);
bool isNumber(char c);
bool isLetter(char c);
bool isOkStr(const char str[]);
void setTime(Date date);
int minusTimes(Date d1, Date d2);
Date *getTime();
#endif //FOODRESERVATION_TOOLS_H
