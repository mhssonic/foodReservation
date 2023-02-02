#include "../objects.h"
#ifndef FOODRESERVATION_FOODLOGDB_H
#define FOODRESERVATION_FOODLOGDB_H
bool creatFoodLogTable(PGconn* conn);
int stateFoodLog(const char userId[], const char foodId[]);
bool insertFoodLog(foodLog *foodLog1);
foodLog **getAllFoodLog(int *size);
foodLog **getFoodLogByUserId(int *size, const char userId[]);
foodLog **getFoodLogByStateAndType(int *size, int state, int type, Date start, Date end);//-1 if you want to see all of which one
int sumFoodLogByStateAndType(int state, int type, Date start, Date end);//-1 if you want to see all of which one
foodLog **getFoodLogByUserIdAndState(int *size, const char userId[], int state);
schedule **getSchedulesByTimeAndFood(int *size, Date date , const char food_id[]);
int countFoodLogByStateAndType(int state, int type, Date start, Date end);
#endif //FOODRESERVATION_FOODLOGDB_H
