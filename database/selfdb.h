#include "../objects.h"
#ifndef FOODRESERVATION_SELFDB_H
#define FOODRESERVATION_SELFDB_H
bool creatSelfsTable(PGconn* conn);
bool isSelfId(const char id[]);
bool insertSelf(self *self1);
bool delSelf(const char id[]);
self **getAllSelfs(int *size);
self *getSelfById(const char id[]);
#endif //FOODRESERVATION_SELFDB_H
