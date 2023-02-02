#include "../objects.h"
#ifndef FOODRESERVATION_SCHEDULEDB_H
#define FOODRESERVATION_SCHEDULEDB_H
bool creatSchedulesTable(PGconn* conn);
bool isScheduleId(const char id[]);
bool insertSchedule(schedule *self1);
bool delSchedule(const char id[]);
schedule **getAllSchedules(int *size);
schedule *getScheduleById(const char id[]);
#endif //FOODRESERVATION_SCHEDULEDB_H
