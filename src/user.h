#include "app.h"
#ifndef FOODRESERVATION_USER_H
#define FOODRESERVATION_USER_H
void menuRegister();
user *userLogin(const char userId[], const char password[]);
void UserSetTime();
void userChangePassword(user *user1);
user* updateUserWithDB(user *user1);
bool userChangeCredit(const char userId[], int credit);
void userCharge(user *user1);
void checkNews();
bool userChangePass(const char userId[], const char newPass[]);
bool userChangeRole(const char userId[], int newRole);
bool userRegister(const char name[], const char family[], char userId[], const char pass[], long int nationalIdCode, int year, int month, int day, bool gender, int role);
bool userDelStudent(const char userId[]);
#endif //FOODRESERVATION_USER_H
