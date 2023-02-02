#include <stdlib.h>
#include <stdio.h>
#include "foodLogdb.h"
#include "databas.h"
#include <string.h>

bool creatFoodLogTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS food_log (\n"
                                 "\tuser_id VARCHAR(20),\n"
                                 "\tfood_id VARCHAR(20),\n"
                                 "\tself_id VARCHAR(20),\n"
                                 "\ttype BOOLEAN,\n"
                                 "\tstate INT,\n"
                                 "\tprice INT,\n"
                                 "\tdate timestamp)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertFoodLog(foodLog *foodLog1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[300];
    sprintf(query, "INSERT INTO food_log (user_id, food_id, self_id , state, type, date, price)\n"
                   "VALUES('%s', '%s','%s', %d, %d::BOOLEAN, '%d-%d-%d %d', %d)", foodLog1->userId, foodLog1->foodId, foodLog1->selfId, foodLog1->state, foodLog1->type,
                   foodLog1->date.year, foodLog1->date.month, foodLog1->date.day, foodLog1->date.time, foodLog1->price);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

int stateFoodLog(const char userId[], const char foodId[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM food_log WHERE user_id = '%s' AND food_id = '%s'", userId, foodId);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return 0;
    }
    if(PQntuples(res) == 0)
        return 0;
    int temp;
    sscanf(PQgetvalue(res, 0 , 4) ,"%d" , &(temp));
    return temp;
}

foodLog **getAllFoodLog(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM food_log");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no foodLog\n");
        return NULL;
    }
    foodLog **foodLogs;
    foodLogs = (foodLog**)malloc(*size * sizeof (foodLog*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        foodLogs[i] = (foodLog*) malloc(sizeof (foodLog));
        strcpy(foodLogs[i]->userId, PQgetvalue(res, i , 0));
        strcpy(foodLogs[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(foodLogs[i]->selfId, PQgetvalue(res, i , 2));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(foodLogs[i]->state));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(foodLogs[i]->price));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d %d" , &(foodLogs[i]->date.year),
               &(foodLogs[i]->date.month),
               &(foodLogs[i]->date.day),
               &(foodLogs[i]->date.time));
        strcpy(temp, PQgetvalue(res, i , 3));
        if(temp[0] == 't')
            foodLogs[i]->type = 1;
        if(temp[0] == 'f')
            foodLogs[i]->type = 0;
    }
    PQclear(res);
    return foodLogs;
}

foodLog **getFoodLogByUserId(int *size, const char userId[]){
    PGconn *conn = connetToDatabase();
    char query[150];
    sprintf(query, "SELECT * FROM food_log WHERE user_id = '%s'", userId);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no foodLog\n");
        return NULL;
    }
    foodLog **foodLogs;
    foodLogs = (foodLog**)malloc(*size * sizeof (foodLog*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        foodLogs[i] = (foodLog*) malloc(sizeof (foodLog));
        strcpy(foodLogs[i]->userId, PQgetvalue(res, i , 0));
        strcpy(foodLogs[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(foodLogs[i]->selfId, PQgetvalue(res, i , 2));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(foodLogs[i]->state));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(foodLogs[i]->price));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d %d" , &(foodLogs[i]->date.year),
               &(foodLogs[i]->date.month),
               &(foodLogs[i]->date.day),
               &(foodLogs[i]->date.time));
        strcpy(temp, PQgetvalue(res, i , 3));
        if(temp[0] == 't')
            foodLogs[i]->type = 1;
        if(temp[0] == 'f')
            foodLogs[i]->type = 0;
    }
    PQclear(res);
    return foodLogs;
}

foodLog **getFoodLogByUserIdAndState(int *size, const char userId[], int state){
    PGconn *conn = connetToDatabase();
    char query[150];
    sprintf(query, "SELECT * FROM food_log WHERE user_id = '%s' AND state = %d", userId, state);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no foodLog\n");
        return NULL;
    }
    foodLog **foodLogs;
    foodLogs = (foodLog**)malloc(*size * sizeof (foodLog*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        foodLogs[i] = (foodLog*) malloc(sizeof (foodLog));
        strcpy(foodLogs[i]->userId, PQgetvalue(res, i , 0));
        strcpy(foodLogs[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(foodLogs[i]->selfId, PQgetvalue(res, i , 2));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(foodLogs[i]->state));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(foodLogs[i]->price));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d %d" , &(foodLogs[i]->date.year),
               &(foodLogs[i]->date.month),
               &(foodLogs[i]->date.day),
               &(foodLogs[i]->date.time));
        strcpy(temp, PQgetvalue(res, i , 3));
        if(temp[0] == 't')
            foodLogs[i]->type = 1;
        if(temp[0] == 'f')
            foodLogs[i]->type = 0;
    }
    PQclear(res);
    return foodLogs;
}

foodLog **getFoodLogByStateAndType(int *size, int state, int type, Date start, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM food_log WHERE date >= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')\n"
                   "AND date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", start.year, start.month, start.day, start.time,
                   end.year, end.month, end.day, end.time);
    if (state >= 1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND state=%d AND type=%d::BOOLEAN", state, type);
        strcat(query, temp);
    }
    else if(state == -1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND type=%d::BOOLEAN", type);
        strcat(query, temp);
    }
    else if(state >= 1 && type == -1){
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
        printf("there is no foodLog\n");
        return NULL;
    }
    foodLog **foodLogs;
    foodLogs = (foodLog**)malloc(*size * sizeof (foodLog*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        foodLogs[i] = (foodLog*) malloc(sizeof (foodLog));
        strcpy(foodLogs[i]->userId, PQgetvalue(res, i , 0));
        strcpy(foodLogs[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(foodLogs[i]->selfId, PQgetvalue(res, i , 2));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(foodLogs[i]->state));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(foodLogs[i]->price));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d %d" , &(foodLogs[i]->date.year),
               &(foodLogs[i]->date.month),
               &(foodLogs[i]->date.day),
               &(foodLogs[i]->date.time));
        strcpy(temp, PQgetvalue(res, i , 3));
        if(temp[0] == 't')
            foodLogs[i]->type = 1;
        if(temp[0] == 'f')
            foodLogs[i]->type = 0;
    }
    PQclear(res);
    return foodLogs;
}

int sumFoodLogByStateAndType(int state, int type, Date start, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT SUM(price) FROM food_log WHERE date >= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')\n"
                   "AND date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", start.year, start.month, start.day, start.time,
            end.year, end.month, end.day, end.time);
    if (state >= 1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND state=%d AND type=%d::BOOLEAN", state, type);
        strcat(query, temp);
    }
    else if(state == -1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND type=%d::BOOLEAN", type);
        strcat(query, temp);
    }
    else if(state >= 1 && type == -1){
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
        printf("there is no foodLog\n");
        return 0;
    }
    int sum = 0;
    sscanf(PQgetvalue(res, 0 , 0) ,"%d" , &sum);
    PQclear(res);
    return sum;
}

int countFoodLogByStateAndType(int state, int type, Date start, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM food_log WHERE date >= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')\n"
                   "AND date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", start.year, start.month, start.day, start.time,
            end.year, end.month, end.day, end.time);
    if (state >= 1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND state=%d AND type=%d::BOOLEAN", state, type);
        strcat(query, temp);
    }
    else if(state == -1 && type >= 0){
        char temp[50];
        sprintf(temp, " AND type=%d::BOOLEAN", type);
        strcat(query, temp);
    }
    else if(state >= 1 && type == -1){
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
    return size;
}