#ifndef FOODRESERVATION_NEWSDB_H
#define FOODRESERVATION_NEWSDB_H
#include "../objects.h"
#include "databas.h"
news **getAllNews(int *size);
bool delNews(const char id[]);
bool insertNews(news *news1);
bool creatNewsTable(PGconn* conn);
#endif //FOODRESERVATION_NEWSDB_H
