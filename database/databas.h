#ifndef FOODRESERVATION_DATABAS_H
#define FOODRESERVATION_DATABAS_H
#include "../objects.h"
#include "userdb.h"
#include "selfdb.h"
#include "fooddb.h"
#include "scheduledb.h"
#include "reservedFoodsdb.h"
#include "foodLogdb.h"
#include "financialLog.h"
#include "polldb.h"
#include "newsdb.h"
#include "votedb.h"

PGconn *connetToDatabase();
void close();
#endif //FOODRESERVATION_DATABAS_H