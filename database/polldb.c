#include <stdlib.h>
#include <stdio.h>
#include "polldb.h"
#include "databas.h"

bool creatPollsTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS polls (\n"
                                 "\tid VARCHAR(20),\n"
                                 "\tquestion VARCHAR(100),\n"
                                 "\tcase1 VARCHAR(50),\n"
                                 "\tcase2 VARCHAR(50),\n"
                                 "\tcase3 VARCHAR(50),\n"
                                 "\tcase4 VARCHAR(50),\n"
                                 "\tpoll1 INT,\n"
                                 "\tpoll2 INT,\n"
                                 "\tpoll3 INT,\n"
                                 "\tpoll4 INT,\n"
                                 "\tcount INT,\n"
                                 "\tdate timestamp)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertPoll(poll *poll1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[1000];
    sprintf(query, "INSERT INTO polls (id , question, case1, case2, case3, case4, poll1, poll2, poll3, poll4, date, count)\n"
                   "VALUES('%s', '%s' , '%s' , '%s' , '%s' , '%s', %d, %d, %d, %d, '%d-%d-%d %d', %d)", poll1->id, poll1->question, poll1->cases[0], poll1->cases[1] , poll1->cases[2] , poll1->cases[3],
            poll1->votes[0],poll1->votes[1],poll1->votes[2],poll1->votes[3],poll1->date.year, poll1->date.month, poll1->date.day, poll1->date.time, poll1->count);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

poll **getAllPoll(int *size){
    PGconn *conn = connetToDatabase();
    PGresult  *res = PQexec(conn, "SELECT * FROM polls");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no poll\n");
        return NULL;
    }
    poll **polls;
    polls = (poll**)malloc(*size * sizeof (poll*));
    for(int i = 0; i < *size; i++){
        polls[i] = (poll*) malloc(sizeof (poll));
        strcpy(polls[i]->id, PQgetvalue(res, i , 0));
        strcpy(polls[i]->question, PQgetvalue(res, i , 1));
        strcpy(polls[i]->cases[0], PQgetvalue(res, i , 2));
        strcpy(polls[i]->cases[1], PQgetvalue(res, i , 3));
        strcpy(polls[i]->cases[2], PQgetvalue(res, i , 4));
        strcpy(polls[i]->cases[3], PQgetvalue(res, i , 5));
        sscanf(PQgetvalue(res, i , 6) ,"%d" , &(polls[i]->votes[0]));
        sscanf(PQgetvalue(res, i , 7) ,"%d" , &(polls[i]->votes[1]));
        sscanf(PQgetvalue(res, i , 8) ,"%d" , &(polls[i]->votes[2]));
        sscanf(PQgetvalue(res, i , 9) ,"%d" , &(polls[i]->votes[3]));
        sscanf(PQgetvalue(res, i , 10) ,"%d" , &(polls[i]->count));
        sscanf(PQgetvalue(res, i , 11) ,"%d-%d-%d %d" , &(polls[i]->date.year),
               &(polls[i]->date.month),
               &(polls[i]->date.day),
               &(polls[i]->date.time));
    }
    PQclear(res);
    return polls;
}

poll *getPollById(const char id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM polls WHERE id = '%s'", id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    if(PQntuples(res) == 0){
        printf("there is no poll for that id\n");
        return NULL;
    }
    poll *poll1;
    poll1 = (poll*) malloc(sizeof (poll));
    strcpy(poll1->id, PQgetvalue(res, 0 , 0));
    strcpy(poll1->question, PQgetvalue(res, 0 , 1));
    strcpy(poll1->cases[0], PQgetvalue(res, 0 , 2));
    strcpy(poll1->cases[1], PQgetvalue(res, 0 , 3));
    strcpy(poll1->cases[2], PQgetvalue(res, 0 , 4));
    strcpy(poll1->cases[3], PQgetvalue(res, 0 , 5));
    sscanf(PQgetvalue(res, 0 , 6) ,"%d" , &(poll1->votes[0]));
    sscanf(PQgetvalue(res, 0 , 7) ,"%d" , &(poll1->votes[1]));
    sscanf(PQgetvalue(res, 0 , 8) ,"%d" , &(poll1->votes[2]));
    sscanf(PQgetvalue(res, 0 , 9) ,"%d" , &(poll1->votes[3]));
    sscanf(PQgetvalue(res, 0 , 10) ,"%d" , &(poll1->count));
    sscanf(PQgetvalue(res, 0 , 11) ,"%d-%d-%d %d" , &(poll1->date.year),
           &(poll1->date.month),
           &(poll1->date.day),
           &(poll1->date.time));
    PQclear(res);
    return poll1;
}

bool delPoll(const char id[]){
    char query[100];
    sprintf(query, "DELETE FROM polls WHERE id = '%s'", id);
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

bool votePoll(const char id[], int numCase, int numberOfVote){
    char query[150] = "";
    sprintf(query, "UPDATE polls SET poll%d=poll%d+ %d WHERE id='%s'", numCase, numCase, numberOfVote, id);
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