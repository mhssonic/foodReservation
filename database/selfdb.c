#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "selfdb.h"
#include "databas.h"

bool creatSelfsTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS selfs (\n"
                                 "\tid VARCHAR(20),\n"
                                 "\tname VARCHAR(20),\n"
                                 "\tlocation VARCHAR(50),\n"
                                 "\tsize INT,\n"
                                 "\tgender BOOLEAN,\n"
                                 "\tlunch_start INT,\n"
                                 "\tlunch_end INT,\n"
                                 "\tdinner_start INT,\n"
                                 "\tdinner_end INT,\n"
                                 "\tmeal VARCHAR(3))");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertSelf(self *self1){//add a user to database and if it's successfull return 1 otherwise return 0
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    if(self1->meal[0] == '0' && self1->meal[1] == '0' && self1->meal[2] == '0')
        return 1;
    char query[300];
    sprintf(query, "INSERT INTO selfs (id, name, location , size, gender, meal , lunch_start, lunch_end, dinner_start, dinner_end)\n"
                   "VALUES('%s', '%s', '%s', %d, %d::BOOLEAN, '%s', %d , %d , %d , %d)", self1->id, self1->name, self1->location, self1->size, self1->gender, self1->meal, self1->lunch.start, self1->lunch.end, self1->dinner.start, self1->dinner.end);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool isSelfId(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM selfs WHERE id = '%s'", id);
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

bool delSelf(const char id[]){
    char query[100];
    sprintf(query, "DELETE FROM selfs WHERE id = '%s'", id);
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

self *getSelfById(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM selfs WHERE id = '%s'", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    if(PQntuples(res) == 0){
        printf("there is no self for that id\n");
        return NULL;
    }
    self *self1;
    char temp[10];
    self1 = (self*) malloc(sizeof (self));
    strcpy(self1->id, PQgetvalue(res, 0 , 0));
    strcpy(self1->name, PQgetvalue(res, 0 , 1));
    strcpy(self1->location, PQgetvalue(res, 0 , 2));
    strcpy(self1->meal, PQgetvalue(res, 0 , 5));
    sscanf(PQgetvalue(res, 0 , 3) ,"%d" , &(self1->size));
    sscanf(PQgetvalue(res, 0 , 6) ,"%d" , &(self1->lunch.start));
    sscanf(PQgetvalue(res, 0 , 7) ,"%d" , &(self1->lunch.end));
    sscanf(PQgetvalue(res, 0 , 8) ,"%d" , &(self1->dinner.start));
    sscanf(PQgetvalue(res, 0 , 9) ,"%d" , &(self1->dinner.end));
    strcpy(temp, PQgetvalue(res, 0 , 4));
    if(temp[0] == 't')//male
        self1->gender = 1;
    if(temp[0] == 'f')//female
        self1->gender = 0;
    PQclear(res);
    return self1;
}

self **getAllSelfs(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM selfs");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no self\n");
        return NULL;
    }
    self **selfs;
    selfs = (self**)malloc(*size * sizeof (self*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        selfs[i] = (self*) malloc(sizeof (self));
        strcpy(selfs[i]->id, PQgetvalue(res, i , 0));
        strcpy(selfs[i]->name, PQgetvalue(res, i , 1));
        strcpy(selfs[i]->location, PQgetvalue(res, i , 2));
        strcpy(selfs[i]->meal, PQgetvalue(res, i , 5));
        sscanf(PQgetvalue(res, i , 3) ,"%d" , &(selfs[i]->size));
        sscanf(PQgetvalue(res, i , 6) ,"%d" , &(selfs[i]->lunch.start));
        sscanf(PQgetvalue(res, i , 7) ,"%d" , &(selfs[i]->lunch.end));
        sscanf(PQgetvalue(res, i , 8) ,"%d" , &(selfs[i]->dinner.start));
        sscanf(PQgetvalue(res, i , 9) ,"%d" , &(selfs[i]->dinner.end));
        strcpy(temp, PQgetvalue(res, i , 4));
        if(temp[0] == 't')//male
            selfs[i]->gender = 1;
        if(temp[0] == 'f')//female
            selfs[i]->gender = 0;
    }
    PQclear(res);
    return selfs;
}



