#ifndef FOODRESERVATION_OBJECTS_H
#define FOODRESERVATION_OBJECTS_H
#include <stdbool.h>
#include <postgresql/libpq-fe.h>
#include <string.h>


typedef struct Date{
    int month;
    int day;
    int year;
    int time;
}Date;

typedef enum {
    ADMIN,
    STUDENT,
    REG_STUDENT,
    DIS_STUDENT,
    REG_ADMIN
};

typedef enum {//type of foods
    DESSERT,
    FOOD
};

typedef enum {//state of food log
    RESERVED,
    NOT_RESERVED,
    DAILY_RESERVED,
    CANCELED,
    EATEN
};

typedef enum {//return of test cases
    SUCCESSS,
    NOT_FOUND,
    INVALID,
    PERMISSION_DENIED
};

typedef enum {//state of financial log
    RESERVE_FOOD,
    CHARGE,
    DAILY_RESERVE,
    CANCEL_RESERVE,
    SEND_CHARGE
};

typedef enum {
    LUNCH,
    DINNER
};

typedef struct user{
    char userId[20];
    long int nationalIdCode;
    char name[20];
    char family[20];
    bool gender;// 1 for male and 0 for female
    Date birthdate;
    char pass[20];
    int role;
    int credit;
} user;
void printUser( user*);

typedef struct timeLimited{
    int start;
    int end;
} timeLimited;

typedef struct self{
    char id[20];
    char name[20];
    char location[50];
    int size;
    bool gender;
    timeLimited lunch;
    timeLimited dinner;
    char meal[3];//like 01 means dinner and 11 mean both
}self;
void printSelf(self *);

typedef struct food{
    char id[20];
    char name[20];
    bool type;
    int price;
}food;
void printFood(food *);

typedef struct schedule{
    char id[20];
    char foodId[20];
    bool type;
    char selfId[20];
    int meal;
    int count;
    Date date;
}schedule;
void printSchedule(schedule *);

typedef struct reservedFood{
    char id[20];
    char userId[20];
}reservedFood;
void printReservedFood(reservedFood *);

typedef struct news{
    char title[50];
    char content[300];
    Date date;
}news;
void printNews(news * news1);

typedef struct poll{
    char id[20];
    char question[100];
    char cases[4][50];
    int votes[4];
    int count;
    Date date;
}poll;
void printPoll(poll * poll1);

typedef struct foodLog{
    char userId[20];
    char foodId[20];
    char selfId[20];
    bool type;
    int state;
    Date date;
    int price;
}foodLog;
void printFoodLog(foodLog * foodLog1);

typedef struct financialLog{
    char userId[20];
    int money;
    int state;
    Date date;
}financialLog;
void printFinancialLog(financialLog * financialLog1);

typedef struct vote{
    char userId[20];
    char pollId[20];
    int option;
}vote;

#endif //FOODRESERVATION_OBJECTS_H
