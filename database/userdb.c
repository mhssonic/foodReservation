#include <stdlib.h>
#include <stdio.h>
#include "userdb.h"

bool creatUsersTable(PGconn* conn){
    PGresult *res = PQexec(conn, "CREATE TABLE IF NOT EXISTS users (\n"
                                 "\tuser_id VARCHAR(20),\n"
                                 "\tnational_id_code BIGSERIAL,\n"
                                 "\tname VARCHAR(20),\n"
                                 "\tfamily VARCHAR(20),\n"
                                 "\tpass VARCHAR(20),\n"
                                 "\tgender BOOLEAN, \n"
                                 "\trole smallserial,\n"
                                 "\tbirthdate Date,\n"
                                 "\tcredit INT\n"
                                 ")");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        return 0;
    }

    PQclear(res);
    res = PQexec(conn, "SELECT * FROM users WHERE user_id = 'admin'");
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        return 0;
    }
    if(PQntuples(res) == 0){
        PQclear(res);
        res = PQexec(conn, "INSERT INTO users (user_id, pass, role) VALUES('admin','admin', 0)");
        if (PQresultStatus(res) != PGRES_COMMAND_OK){
            PQclear(res);
            return 0;
        }
    }
    PQclear(res);
    return 1;
}

bool insertUser(user *user1){//add a user to database and if it's successfull return 1 otherwise return 0
    PGconn *conn = connetToDatabase();//todo test it in case of being NULL
    if(user1->birthdate.day > 31 || user1->birthdate.day < 0)
        return 1;
    if(user1->birthdate.month > 12 || user1->birthdate.day < 0)
        return 1;
    if(user1->birthdate.year < 0)
        return 1;
    char query[300];
    sprintf(query, "INSERT INTO users (user_id, national_id_code, name, family , pass, gender, role, birthdate, credit)\n"
                   "VALUES('%s', %ld , '%s', '%s', '%s', %d::BOOLEAN, %d, '%d-%d-%d', %d)", user1->userId, user1->nationalIdCode, user1->name, user1->family, user1->pass, user1->gender, user1->role, user1->birthdate.year, user1->birthdate.month, user1->birthdate.day, user1->credit);
    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        close();
        return 0;
    }
    PQclear(res);
    return 1;
}

user *getUserByUserId(const char userId[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM users WHERE user_id = '%s'", userId);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    if(PQntuples(res) == 0){
        printf("there is no user for that userId\n");
        return NULL;
    }
    user *user1;
    user1 = (user*)malloc(sizeof (user));
    char temp[30];
    strcpy(user1->userId, PQgetvalue(res, 0 , 0));
    sscanf(PQgetvalue(res, 0 , 1) ,"%ld" , &(user1->nationalIdCode));
    strcpy(user1->name, PQgetvalue(res, 0 , 2));
    strcpy(user1->family, PQgetvalue(res, 0 , 3));
    strcpy(user1->pass, PQgetvalue(res, 0 , 4));
    strcpy(temp, PQgetvalue(res, 0 , 5));
    if(temp[0] == 't')//male
        user1->gender = 1;
    if(temp[0] == 'f')//female
        user1->gender = 0;
    sscanf(PQgetvalue(res, 0 , 6) ,"%d" , &(user1->role));
    sscanf(PQgetvalue(res, 0 , 7) ,"%d-%d-%d" , &(user1->birthdate.year), &(user1->birthdate.month), &(user1->birthdate.day));
    sscanf(PQgetvalue(res, 0 , 8) ,"%d" , &(user1->credit));
    PQclear(res);
    return user1;
}


user **getUsersByRole(int role, int *size){//list all user by role n, and store size of that list in *size
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM users WHERE role = %d", role);
    PGresult  *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK){
        printf("No data retrieved\n");
        PQclear(res);
        close();
        return NULL;
    }
    *size = PQntuples(res);
    if(*size == 0){
        printf("there is no user for that role\n");
        return NULL;
    }
    user **users;
    users = (user**)malloc(*size * sizeof (user*));
    char temp[10];
    for(int i = 0; i < *size; i++){
        users[i] = (user*) malloc(sizeof (user));
        strcpy(users[i]->userId, PQgetvalue(res, i , 0));
        sscanf(PQgetvalue(res, i , 1) ,"%ld" , &(users[i]->nationalIdCode));
        strcpy(users[i]->name, PQgetvalue(res, i , 2));
        strcpy(users[i]->family, PQgetvalue(res, i , 3));
        strcpy(users[i]->pass, PQgetvalue(res, i , 4));
        strcpy(temp, PQgetvalue(res, i , 5));
        if(temp[0] == 't')//male
            users[i]->gender = 1;
        if(temp[0] == 'f')//female
            users[i]->gender = 0;
        sscanf(PQgetvalue(res, i , 6) ,"%d" , &(users[i]->role));
        sscanf(PQgetvalue(res, i , 7) , "%d-%d-%d" , &(users[i]->birthdate.year), &(users[i]->birthdate.month), &(users[i]->birthdate.day));
        sscanf(PQgetvalue(res, i , 8) ,"%d" , &(users[i]->credit));
    }
    PQclear(res);
    return users;
}

bool updateUser(const char userId[], const char column[], const char value[]){//update user with userId NOTE: if you want feed a string make sure to pas 'string'
    char query[300] = "UPDATE users SET ";
    strcat(query, column);
    strcat(query, "=");
    strcat(query, value);
    char temp[100];
    sprintf(temp, " WHERE user_id='%s'", userId);
    strcat(query, temp);
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

bool updateCreditUser(const char userId[], int credit){
    char temp[30];
    sprintf(temp, "credit + %d", credit);
    return updateUser(userId, "credit", temp);
}

bool delUser(const char userId[]){
    char query[100];
    sprintf(query, "DELETE FROM users WHERE user_id = '%s'", userId);
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

bool isUserId(const char userId[]){
    PGconn *conn = connetToDatabase();
    char query[200];
    sprintf(query, "SELECT * FROM users WHERE user_id = '%s'", userId);
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