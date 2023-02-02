#include "../objects.h"
#ifndef FOODRESERVATION_FINANCIALLOG_H
#define FOODRESERVATION_FINANCIALLOG_H
bool creatFinancialLogTable(PGconn* conn);
bool insertFinancialLog(financialLog *financialLog1);
financialLog **getAllFinancialLog(int *size);
financialLog **getFinancialLogByUserId(int *size, const char userId[]);
financialLog **getFinancialLogByStateAndType(int *size, const char userId[], int state, Date start, Date end);//-1 if you want to see all of which one and NULL for see every user
int sumFinancialLogByStateAndType(const char userId[], int state, Date start, Date end);//-1 if you want to see all of which one and NULL for see every user
#endif //FOODRESERVATION_FINANCIALLOG_H