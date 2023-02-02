#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "scheduledb.h"
#include "databas.h"

bool creatSchedulesTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS schedules (\n"
                                 "\tid SERIAL UNIQUE,\n"
                                 "\tid_food VARCHAR(20),\n"
                                 "\ttype BOOLEAN,\n"
                                 "\tid_self VARCHAR(20),\n"
                                 "\tmeal INT,\n"
                                 "\tcount SERIAL,\n"
                                 "\tdate date)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertSchedule(schedule *schedule1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[300];
    sprintf(query, "INSERT INTO schedules (id_food , id_self, type ,meal, count, date)\n"
                   "VALUES('%s', '%s', %d::BOOLEAN, %d, %d, '%d-%d-%d')", schedule1->foodId, schedule1->selfId , schedule1->type, schedule1->meal, schedule1->count, schedule1->date.year, schedule1->date.month, schedule1->date.day);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool isScheduleId(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM schedules WHERE id = %s", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return 0;
    }
    if(PQntuples(res) == 0)
        return 0;
    return 1;
}

bool delSchedule(const char id[]){
    char query[100];
    sprintf(query, "DELETE FROM schedules WHERE id = %s", id);
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        PQclear(res);
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

schedule *getScheduleById(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM schedules WHERE id = %s", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    if(PQntuples(res) == 0){
        printf("there is no schedule for that id\n");
        return NULL;
    }
    schedule *schedule1;
    char temp[10];
    schedule1 = (schedule*) malloc(sizeof (schedule));
    strcpy(schedule1->id, PQgetvalue(res, 0 , 0));
    strcpy(schedule1->foodId, PQgetvalue(res, 0 , 1));
    strcpy(temp, PQgetvalue(res, 0 , 2));
    strcpy(schedule1->selfId, PQgetvalue(res, 0 , 3));
    sscanf(PQgetvalue(res, 0 , 4) ,"%d" , &(schedule1->meal));
    sscanf(PQgetvalue(res, 0 , 5) ,"%d" , &(schedule1->count));
    sscanf(PQgetvalue(res, 0 , 6) ,"%d-%d-%d" , &(schedule1->date.year), &(schedule1->date.month), &(schedule1->date.day));
    if (temp[0] == 't')
        schedule1->type = 1;
    if(temp[0] == 'f')
        schedule1->type = 0;
    PQclear(res);
    return schedule1;
}

schedule **getAllSchedules(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM schedules");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no schedule\n");
        return NULL;
    }
    schedule **schedules;
    schedules = (schedule**)malloc(*size * sizeof (schedule*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        schedules[i] = (schedule*) malloc(sizeof (schedule));
        strcpy(schedules[i]->id, PQgetvalue(res, i , 0));
        strcpy(schedules[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(temp, PQgetvalue(res, i , 2));
        strcpy(schedules[i]->selfId, PQgetvalue(res, i , 3));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(schedules[i]->meal));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(schedules[i]->count));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d" , &(schedules[i]->date.year), &(schedules[i]->date.month), &(schedules[i]->date.day));
        if (temp[0] == 't')
            schedules[i]->type = 1;
        if(temp[0] == 'f')
            schedules[i]->type = 0;
    }
    PQclear(res);
    return schedules;
}

schedule **getSchedulesByTimeAndFood(int *size, Date date , const char food_id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM schedules WHERE date == to_timestamp('%d-%d-%d', 'YYYY/MM/DD')\n"
                   "AND food_id = '%s'", date.year, date.month, date.day, food_id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no schedule\n");
        return NULL;
    }
    schedule **schedules;
    schedules = (schedule**)malloc(*size * sizeof (schedule*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        schedules[i] = (schedule*) malloc(sizeof (schedule));
        strcpy(schedules[i]->id, PQgetvalue(res, i , 0));
        strcpy(schedules[i]->foodId, PQgetvalue(res, i , 1));
        strcpy(temp, PQgetvalue(res, i , 2));
        strcpy(schedules[i]->selfId, PQgetvalue(res, i , 3));
        sscanf(PQgetvalue(res, i , 4) ,"%d" , &(schedules[i]->meal));
        sscanf(PQgetvalue(res, i , 5) ,"%d" , &(schedules[i]->count));
        sscanf(PQgetvalue(res, i , 6) ,"%d-%d-%d" , &(schedules[i]->date.year), &(schedules[i]->date.month), &(schedules[i]->date.day));
        if (temp[0] == 't')
            schedules[i]->type = 1;
        if(temp[0] == 'f')
            schedules[i]->type = 0;
    }
    PQclear(res);
    return schedules;
}