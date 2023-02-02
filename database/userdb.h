#include "../objects.h"
#ifndef FOODRESERVATION_USERDB_H
#define FOODRESERVATION_USERDB_H
#include "databas.h"
bool creatUsersTable(PGconn* conn);
bool insertUser(user* user1);
user *getUserByUserId(const char[]);
user **getUsersByRole(int , int *);//list all user by role n, and store size of that list in *size
bool updateUser(const char[], const char[], const char *);//userId , column , value
bool delUser(const char[]);
bool isUserId(const char[]);// if there is one return 1
bool updateCreditUser(const char userId[], int credit);
#endif //FOODRESERVATION_USERDB_H
