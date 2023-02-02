#include "logs.h"
#include <stdlib.h>

void addToFinancialLog(char userId[], food *tempFood, float price_multi, int state){
    financialLog *tempFinancialLog =  (financialLog *)malloc(sizeof (financialLog));
    tempFinancialLog->date = *getTime();
    tempFinancialLog->state = state;
    tempFinancialLog->money = tempFood->price * price_multi;
    strcpy(tempFinancialLog->userId, userId);

    insertFinancialLog(tempFinancialLog);
    free(tempFinancialLog);
}

void addToFoodLog(char userId[], food *tempFood, self *tempSelf, float price_multi, int state){
    foodLog *tempFoodLog;
    tempFoodLog = (foodLog *)malloc(sizeof (foodLog));
    tempFoodLog->state = state;
    tempFoodLog->date = *getTime();
    strcpy(tempFoodLog->userId, userId);
    strcpy(tempFoodLog->foodId, tempFood->id);
    strcpy(tempFoodLog->selfId, tempSelf->id);
    tempFoodLog->type = tempFood->type;
    tempFoodLog->price = -tempFood->price * price_multi;

    insertFoodLog(tempFoodLog);
    free(tempFoodLog);
}