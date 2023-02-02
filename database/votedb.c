#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "votedb.h"
#include "databas.h"

bool creatVotesTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS votes (\n"
                                 "\tuser_id VARCHAR(20),\n"
                                 "\tpoll_id VARCHAR(20),\n"
                                 "\toption int)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }
    PQclear(res);
    return 1;
}

bool insertVote(vote *vote1){
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    char query[500];
    sprintf(query, "INSERT INTO votes (user_id, poll_id , option)\n"
                   "VALUES('%s', '%s', %d)", vote1->userId, vote1->pollId, vote1->option);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

bool delVote(const char poll_id[], const char user_id[]){
    char query[100];
    sprintf(query, "DELETE FROM votes WHERE poll_id = '%s' AND user_id = '%s'", poll_id, user_id);
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

bool isVoteById(const char poll_id[], const char user_id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM votes WHERE poll_id = '%s' AND user_id = '%s'", poll_id, user_id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return 0;
    }
    if(PQntuples(res) == 0){
        return 0;
    }
    return 1;
}

vote *getVote(const char poll_id[], const char user_id[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM votes WHERE poll_id = '%s' AND user_id = '%s'", poll_id, user_id);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return 0;
    }
    if(PQntuples(res) == 0){
        return 0;
    }
    vote *vote1;
    vote1 = (vote*) malloc(sizeof (vote));
    strcpy(vote1->userId, PQgetvalue(res, 0 , 0));
    strcpy(vote1->pollId, PQgetvalue(res, 0 , 1));
    sscanf(PQgetvalue(res, 0 , 2) ,"%d" , &(vote1->option));
    PQclear(res);
    return vote1;
}