#include <stdlib.h>
#include <stdio.h>
#include "fooddb.h"
#include "databas.h"

bool creatFoodsTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS foods (\n"
                                 "\tid VARCHAR(20),\n"
                                 "\tname VARCHAR(20),\n"
                                 "\tprice INT,\n"
                                 "\ttype BOOLEAN)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertFood(food *food1){//add a user to database and if it's successfull return 1 otherwise return 0
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[300];
    sprintf(query, "INSERT INTO foods (id, name , price, type)\n"
                   "VALUES('%s', '%s', %d, %d::BOOLEAN)", food1->id, food1->name, food1->price, food1->type);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool isFoodId(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM foods WHERE id = '%s'", id);
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

bool delFood(const char id[]){
    char query[100];
    sprintf(query, "DELETE FROM foods WHERE id = '%s'", id);
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

food *getFoodById(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM foods WHERE id = '%s'", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    if(PQntuples(res) == 0){
        printf("there is no food for that id\n");
        return NULL;
    }
    food *food1;
    char temp[10];
    food1 = (food*) malloc(sizeof (food));
    strcpy(food1->id, PQgetvalue(res, 0 , 0));
    strcpy(food1->name, PQgetvalue(res, 0 , 1));
    sscanf(PQgetvalue(res, 0 , 2) ,"%d" , &(food1->price));
    strcpy(temp, PQgetvalue(res, 0 , 3));
    if(temp[0] == 't')//male
        food1->type = 1;
    if(temp[0] == 'f')//female
        food1->type = 0;
    PQclear(res);
    return food1;
}

food **getAllFoods(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM foods");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no food\n");
        return NULL;
    }
    food **foods;
    foods = (food**)malloc(*size * sizeof (food*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        foods[i] = (food*) malloc(sizeof (food));
        strcpy(foods[i]->id, PQgetvalue(res, i , 0));
        strcpy(foods[i]->name, PQgetvalue(res, i , 1));
        sscanf(PQgetvalue(res, i , 2) ,"%d" , &(foods[i]->price));
        strcpy(temp, PQgetvalue(res, i , 3));
        if(temp[0] == 't')//male
            foods[i]->type = 1;
        if(temp[0] == 'f')//female
            foods[i]->type = 0;
    }
    PQclear(res);
    return foods;
}