#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "reservedFoodsdb.h"

bool creatReservedFoodsTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS reserved_foods (\n"
                                 "\tid VARCHAR(20),\n"
                                 "\tuser_id VARCHAR(20))");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertReservedFood(reservedFood *reservedFood1){//add a user to database and if it's successfull return 1 otherwise return 0
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[300];
    sprintf(query, "INSERT INTO reserved_Foods (id, user_id)\n"
                   "VALUES('%s', '%s')", reservedFood1->id, reservedFood1->userId);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool isReservedFood(const char id[], const char userId[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM reserved_foods WHERE id = '%s' AND user_id = '%s'", id, userId);
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

bool delReservedFood(const char id[] , const char userId[]){
    char query[100];
    sprintf(query, "DELETE FROM reserved_foods WHERE id = '%s' AND user_id='%s'", id, userId);
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

reservedFood **getReservedFoodByUserId(const char userId[], int *size){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM reserved_foods WHERE user_id = '%s'", userId);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no reserved_food for that user_id\n");
        return NULL;
    }
    reservedFood **reservedFoods;
    reservedFoods = (reservedFood**)malloc(*size * sizeof (reservedFood*));
    for(int i = 0; i < *size; i++){
        reservedFoods[i] = (reservedFood*) malloc(sizeof (reservedFood));
        strcpy(reservedFoods[i]->id, PQgetvalue(res, i , 0));
        strcpy(reservedFoods[i]->userId, PQgetvalue(res, i , 1));
    }
    PQclear(res);
    return reservedFoods;
}

reservedFood **getReservedFoodById(const char id[], int *size){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM reserved_foods WHERE id = '%s'", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no reserved_food for that id\n");
        return NULL;
    }
    reservedFood **reservedFoods;
    reservedFoods = (reservedFood**)malloc(*size * sizeof (reservedFood*));
    for(int i = 0; i < *size; i++){
        reservedFoods[i] = (reservedFood*) malloc(sizeof (reservedFood));
        strcpy(reservedFoods[i]->id, PQgetvalue(res, i , 0));
        strcpy(reservedFoods[i]->userId, PQgetvalue(res, i , 1));
    }
    PQclear(res);
    return reservedFoods;
}

reservedFood **getAllReservedFoods(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM reserved_foods");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no reserved_food\n");
        return NULL;
    }
    reservedFood **reservedFoods;
    reservedFoods = (reservedFood**)malloc(*size * sizeof (reservedFood*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        reservedFoods[i] = (reservedFood*) malloc(sizeof (reservedFood));
        strcpy(reservedFoods[i]->id, PQgetvalue(res, i , 0));
        strcpy(reservedFoods[i]->userId, PQgetvalue(res, i , 1));
    }
    PQclear(res);
    return reservedFoods;
}
