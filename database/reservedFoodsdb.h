#ifndef FOODRESERVATION_RESERVEDFOODSDB_H
#define FOODRESERVATION_RESERVEDFOODSDB_H
#include "databas.h"
bool creatReservedFoodsTable(PGconn* conn);
bool insertReservedFood(reservedFood *reservedFood1);
bool isReservedFood(const char id[], const char userId[]);
bool delReservedFood(const char id[] , const char userId[]);
reservedFood **getReservedFoodByUserId(const char userId[], int *size);
reservedFood **getReservedFoodById(const char id[], int *size);
reservedFood **getAllReservedFoods(int *size);
#endif //FOODRESERVATION_RESERVEDFOODSDB_H
