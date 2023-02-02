#ifndef FOODRESERVATION_LOGS_H
#define FOODRESERVATION_LOGS_H
#include "app.h"
void addToFinancialLog(char userId[], food *tempFood, float price_multi, int state);
void addToFoodLog(char userId[], food *tempFood, self *tempSelf, float price_multi, int state);
#endif //FOODRESERVATION_LOGS_H
