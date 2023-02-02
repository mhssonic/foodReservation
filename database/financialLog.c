#include <stdlib.h>
#include <stdio.h>
#include "financialLog.h"
#include "databas.h"
//todo rename this file
bool creatFinancialLogTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS financial_log (\n"
                                 "\tuser_id VARCHAR(20),\n"
                                 "\tstate INT,\n"
                                 "\tmoney INT,\n"
                                 "\tdate timestamp)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertFinancialLog(financialLog *financialLog1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[300];
    sprintf(query, "INSERT INTO financial_log (user_id , state, date, money)\n"
                   "VALUES('%s', %d, '%d-%d-%d %.4d', %d)", financialLog1->userId, financialLog1->state,
            financialLog1->date.year, financialLog1->date.month, financialLog1->date.day, financialLog1->date.time, financialLog1->money);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

financialLog **getFinancialLogByUserId(int *size, const char userId[]){
    PGconn *conn = connetToDatabase();
    char query[150];
    sprintf(query, "SELECT * FROM financial_log WHERE user_id = '%s'", userId);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no financialLog\n");
        return NULL;
    }
    financialLog **financialLogs;
    financialLogs = (financialLog**)malloc(*size * sizeof (financialLog*));
    for(int i = 0; i < *size; i++){
        financialLogs[i] = (financialLog*) malloc(sizeof (financialLog));
        strcpy(financialLogs[i]->userId, PQgetvalue(res, i , 0));
        sscanf(PQgetvalue(res, i , 1) ,"%d" , &(financialLogs[i]->state));
        sscanf(PQgetvalue(res, i , 2) ,"%d" , &(financialLogs[i]->money));
        sscanf(PQgetvalue(res, i , 3) ,"%d-%d-%d %d" , &(financialLogs[i]->date.year),
               &(financialLogs[i]->date.month),
               &(financialLogs[i]->date.day),
               &(financialLogs[i]->date.time));
    }
    PQclear(res);
    return financialLogs;
}

financialLog **getAllFinancialLog(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM financial_log");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no financialLog\n");
        return NULL;
    }
    financialLog **financialLogs;
    financialLogs = (financialLog**)malloc(*size * sizeof (financialLog*));
    for(int i = 0; i < *size; i++){
        financialLogs[i] = (financialLog*) malloc(sizeof (financialLog));
        strcpy(financialLogs[i]->userId, PQgetvalue(res, i , 0));
        sscanf(PQgetvalue(res, i , 1) ,"%d" , &(financialLogs[i]->state));
        sscanf(PQgetvalue(res, i , 2) ,"%d" , &(financialLogs[i]->money));
        sscanf(PQgetvalue(res, i , 3) ,"%d-%d-%d %d" , &(financialLogs[i]->date.year),
               &(financialLogs[i]->date.month),
               &(financialLogs[i]->date.day),
               &(financialLogs[i]->date.time));
    }
    PQclear(res);
    return financialLogs;
}

financialLog **getFinancialLogByStateAndType(int *size, const char userId[], int state, Date start, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM financial_log WHERE date >= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')\n"
                   "AND date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", start.year, start.month, start.day, start.time,
            end.year, end.month, end.day, end.time);
    if (state >= 1 && userId != NULL){
        char temp[50];
        sprintf(temp, " AND state=%d AND user_id='%s'", state, userId);
        strcat(query, temp);
    }
    else if(state == -1 && userId != NULL){
        char temp[50];
        sprintf(temp, " AND user_id='%s'", userId);
        strcat(query, temp);
    }
    else if(state >= 1 && userId == NULL){
        char temp[50];
        sprintf(temp, " AND state=%d", state);
        strcat(query, temp);
    }
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no financialLog\n");
        return NULL;
    }
    financialLog **financialLogs;
    financialLogs = (financialLog**)malloc(*size * sizeof (financialLog*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        financialLogs[i] = (financialLog*) malloc(sizeof (financialLog));
        strcpy(financialLogs[i]->userId, PQgetvalue(res, i , 0));
        sscanf(PQgetvalue(res, i , 1) ,"%d" , &(financialLogs[i]->state));
        sscanf(PQgetvalue(res, i , 2) ,"%d" , &(financialLogs[i]->money));
        sscanf(PQgetvalue(res, i , 3) ,"%d-%d-%d %d" , &(financialLogs[i]->date.year),
               &(financialLogs[i]->date.month),
               &(financialLogs[i]->date.day),
               &(financialLogs[i]->date.time));
    }
    PQclear(res);
    return financialLogs;
}

int sumFinancialLogByStateAndType(const char userId[], int state, Date start, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT SUM(money) FROM financial_log WHERE date >= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')\n"
                   "AND date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", start.year, start.month, start.day, start.time,
            end.year, end.month, end.day, end.time);
    if (state >= 1 && userId != NULL){
        char temp[50];
        sprintf(temp, " AND state=%d AND user_id='%s'", state, userId);
        strcat(query, temp);
    }
    else if(state == -1 && userId != NULL){
        char temp[50];
        sprintf(temp, " AND user_id='%s'", userId);
        strcat(query, temp);
    }
    else if(state >= 1 && userId == NULL){
        char temp[50];
        sprintf(temp, " AND state=%d", state);
        strcat(query, temp);
    }
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return 0;
    }
    int size = PQntuples(res);
    if(size == 0){
        printf("there is no financialLog\n");
        return 0;
    }
    int sum = 0;
    sscanf(PQgetvalue(res, 0 , 0) ,"%d" , &sum);
    PQclear(res);
    return sum;
}