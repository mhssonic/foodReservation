#include "../objects.h"
#ifndef FOODRESERVATION_FOODDB_H
#define FOODRESERVATION_FOODDB_H
bool creatFoodsTable(PGconn* conn);
bool isFoodId(const char id[]);
bool insertFood(food *food1);
bool delFood(const char id[]);
food **getAllFoods(int *size);
food *getFoodById(const char id[]);
#endif //FOODRESERVATION_FOODDB_H