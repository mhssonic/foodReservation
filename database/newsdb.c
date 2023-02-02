#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "newsdb.h"
#include "databas.h"

bool creatNewsTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS news (\n"
                                 "\ttitle VARCHAR(50),\n"
                                 "\tcontent VARCHAR(300),\n"
                                 "\tdate timestamp)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertNews(news *news1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[500];
        sprintf(query, "INSERT INTO news (title , content ,date)\n"
                       "VALUES('%s', '%s', '%d-%d-%d %d')", news1->title, news1->content, news1->date.year, news1->date.month, news1->date.day, news1->date.time);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool delNews(const char id[]){
    char query[100];
    sprintf(query, "DELETE FROM news WHERE id = '%s'", id);
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

//news *getNewsById(const char id[]){
//    PGconn *conn = connetToDatabase();
//    char query[200];
//    sprintf(query, "SELECT * FROM newss WHERE id = '%s'", id);
//    PGresult  *res = PQexec(conn, query);
//    if (PQresultStatus(res) != PGRES_TUPLES_OK){
//        printf("No data retrieved\n");
//        PQclear(res);
//        close();
//        return NULL;
//    }
//    if(PQntuples(res) == 0){
//        printf("there is no news for that id\n");
//        return NULL;
//    }
//    news *news1;
//    char temp[10];
//    news1 = (news*) malloc(sizeof (news));
//    strcpy(news1->id, PQgetvalue(res, 0 , 0));
//    strcpy(news1->name, PQgetvalue(res, 0 , 1));
//    strcpy(news1->location, PQgetvalue(res, 0 , 2));
//    strcpy(news1->meal, PQgetvalue(res, 0 , 5));
//    sscanf(PQgetvalue(res, 0 , 3) ,"%d" , &(news1->size));
//    sscanf(PQgetvalue(res, 0 , 6) ,"%d" , &(news1->lunch.start));
//    sscanf(PQgetvalue(res, 0 , 7) ,"%d" , &(news1->lunch.end));
//    sscanf(PQgetvalue(res, 0 , 8) ,"%d" , &(news1->dinner.start));
//    sscanf(PQgetvalue(res, 0 , 9) ,"%d" , &(news1->dinner.end));
//    strcpy(temp, PQgetvalue(res, 0 , 4));
//    if(temp[0] == 't')//male
//        news1->gender = 1;
//    if(temp[0] == 'f')//female
//        news1->gender = 0;
//    PQclear(res);
//    return news1;
//}

news **getAllNews(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM news");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no news\n");
        return NULL;
    }
    news **newss;
    newss = (news**)malloc(*size * sizeof (news*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        newss[i] = (news*) malloc(sizeof (news));
        strcpy(newss[i]->title, PQgetvalue(res, i , 0));
        strcpy(newss[i]->content, PQgetvalue(res, i , 1));
        sscanf(PQgetvalue(res, i , 2) ,"%d-%d-%d %d" , &(newss[i]->date.year),
               &(newss[i]->date.month),
               &(newss[i]->date.day),
               &(newss[i]->date.time));
    }
    PQclear(res);
    return newss;
}

news **getAllNewsBeforeTime(int *size, Date end){//-1 if you want to see all of which one
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM news WHERE \n"
                   " date <= to_timestamp('%d-%d-%d %d', 'YYYY/MM/DD HH24MI')", end.year, end.month, end.day, end.time);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no news\n");
        return NULL;
    }
    news **newss;
    newss = (news**)malloc(*size * sizeof (news*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        newss[i] = (news*) malloc(sizeof (news));
        strcpy(newss[i]->title, PQgetvalue(res, i , 0));
        strcpy(newss[i]->content, PQgetvalue(res, i , 1));
        sscanf(PQgetvalue(res, i , 2) ,"%d-%d-%d %d" , &(newss[i]->date.year),
               &(newss[i]->date.month),
               &(newss[i]->date.day),
               &(newss[i]->date.time));
    }
    PQclear(res);
    return newss;
}