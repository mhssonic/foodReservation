#include "databas.h"
#include <stdlib.h>
#include <stdio.h>
#include <postgresql/libpq-fe.h>

//static variable
static PGconn *conn;
static bool flagConnection = 0;

void close(){
    PQfinish(conn);
    flagConnection = 0;
    fprintf(stderr, "Connection failed %s", PQerrorMessage(conn));
    exit(1);
}

PGconn *connetToDatabase(){
    if (flagConnection == 1)
        return conn;
        conn = PQconnectdb("host=127.0.0.1 user=postgres password=pashmakid dbname=foodReservation");
    if(PQstatus(conn) == CONNECTION_BAD){
        close();
    }
    if (!creatUsersTable(conn)){
        close();
    }
    if (!creatSelfsTable(conn)){
        close();
    }
    if (!creatFoodsTable(conn)){
        close();
    }
    if (!creatSchedulesTable(conn)){
        close();
    }
    if(!creatReservedFoodsTable(conn)){
        close();
    }
    if(!creatFoodLogTable(conn)){
        close();
    }
    if(!creatFinancialLogTable(conn)){
        close();
    }
    if(!creatPollsTable(conn)){
        close();
    }
    if(!creatNewsTable(conn)){
        close();
    }
    if(!creatVotesTable(conn)){
        close();
    }
    system("clear");

    flagConnection = 1;
    return conn;
}

void testUserdb(){
//    Date date1;
//    date1.year = 1200;
//    date1.month = 2;
//    date1.day = 5;
//    user user1;
//    user1.birthdate  = date1;
//    user1.role = 1;
//    user1.gender = 1;
//    user1.family[0] = 't';
//    user1.family[1] = '\0';
//    user1.name[0] = 'd';
//    user1.name[1] = '\0';
//    user1.pass[0] = 't';
//    user1.pass[1] = '\0';
//    user1.userId[0] = '9';
//    user1.userId[1] = '\0';
//    user1.nationalIdCode = 5;
//    user1.credit = 100000;
//    insertUser(&user1);
//    printf("%d\n", isUserId(user1.userId));
//    user *user2 = getUserByUserId("admin");
//    printUser(user2);
//    user **users;
//    int size;
//    users = getUsersByRole(1, &size);
//    for(int i = 0; i < size; i++)
//        printUser(users[i]);
//    updateUser("8", "role", "5");
//    delUser("8");
    updateCreditUser("9", -5000);
}



void testSelfdb(){
//    self self1;
//    self1.gender = 1;
//    self1.name[0] = 'd';
//    self1.name[1] = '\0';
//    self1.location[1] = '\0';
//    self1.location[0] = 'c';
//    self1.id[0] = '5';
//    self1.id[1] = '\0';
//    self1.meal[0] = '1';
//    self1.meal[1] = '1';
//    self1.meal[2] = '1';
//    self1.meal[3] = '\0';
//    self1.size = 60;
//    timeLimited timeLimited1;
//    timeLimited1.start = 1100;
//    timeLimited1.end = 1300;
//    self1.lunch = timeLimited1;
//    timeLimited1.start = 1900;
//    timeLimited1.end = 2000;
//    self1.dinner = timeLimited1;
//    insertSelf(&self1);
//    printf("%d\n", isSelfId(self1.id));
//    self *self2 = getSelfById("5");

//    printSelf(self2);
//    self **selfs;
//    int size;
//    selfs = getAllSelfs(&size);
//    for(int i = 0; i < size; i++)
//        printSelf(selfs[i]);
//    delSelf("5");
}

void testfooddb(){
    food food1;
    food1.type = 1;
    food1.name[0] = 'd';
    food1.name[1] = '\0';
    food1.id[0] = '5';
    food1.id[1] = '\0';
    food1.price = 5000;
    insertFood(&food1);
//    printf("%d\n", isFoodId(food1.id));
//    food *food2 = getFoodById("5");
//    printFood(food2);
//    food **foods;
//    int size;
//    foods = getAllFoods(&size);
//    for(int i = 0; i < size; i++)
//        printFood(foods[i]);
//    delFood("5");
}

void testScheduledb(){
    Date date1;
    date1.year = 1200;
    date1.month = 2;
    date1.day = 5;
    schedule schedule1;
    schedule1.meal = 1;
    schedule1.foodId[0] = '5';
    schedule1.foodId[1] = '\0';\
    schedule1.id[0] = '8';
    schedule1.id[1] = '\0';
    schedule1.selfId[0] = '5';
    schedule1.selfId[1] = '\0';
    schedule1.count= 5000;
    schedule1.date = date1;
    insertSchedule(&schedule1);
//    printf("%d\n", isScheduleId(schedule1.id));
//    schedule *schedule2 = getScheduleById("5");
//    printSchedule(schedule2);
//    schedule **schedules;
//    int size;
//    schedules = getAllSchedules(&size);
//    for(int i = 0; i < size; i++)
//        printSchedule(schedules[i]);
//    delSchedule("5");
}

void testReservedFood(){
    reservedFood reservedFood1;
    reservedFood1.userId[0] = 'a';
    reservedFood1.userId[1]  = '\0';
    reservedFood1.id[0] = '7';
    reservedFood1.id[1] = '\0';
    insertReservedFood(&reservedFood1);
//    printf("%d\n", isReservedFood(reservedFood1.id, reservedFood1.userId));
//    reservedFood **reservedFoods;
//    int size;
//    reservedFoods = getAllReservedFoods(&size);
//    for(int i = 0; i < size; i++)
//        printReservedFood(reservedFoods[i]);
//    reservedFood **reservedFoods2;
//    int size2;
//    reservedFoods2 = getReservedFoodById("6", &size2);
//    for(int i = 0; i < size2; i++)
//        printReservedFood(reservedFoods2[i]);
//    reservedFood **reservedFoods3;
//    int size3;
//    reservedFoods3 = getReservedFoodByUserId("a", &size3);
//    for(int i = 0; i < size3; i++)
//        printReservedFood(reservedFoods3[i]);
//    delReservedFood("5", "d");
}

void testFoodLogdb(){
    Date date1;
    date1.year = 1200;
    date1.month = 2;
    date1.day = 5;
    date1.time = 1200;
    foodLog foodLog1;
    foodLog1.type = 1;
    foodLog1.foodId[0] = 'd';
    foodLog1.foodId[1] = '\0';
    foodLog1.userId[0] = 'a';
    foodLog1.userId[1] = '\0';
    foodLog1.date = date1;
    foodLog1.price = 500;
    foodLog1.state = 2;
    insertFoodLog(&foodLog1);
    printf("%d\n", stateFoodLog(foodLog1.userId, foodLog1.foodId));
    foodLog **foodLogs;
    int size;
    foodLogs = getFoodLogByStateAndType(&size, -1 , 1, date1, date1);
    for(int i = 0; i < size; i++)
        printFoodLog(foodLogs[i]);
    printf("%d\n", sumFoodLogByStateAndType(-1, -1 ,date1, date1));
}

void testFinancialLogdb(){
    Date date1;
    date1.year = 1200;
    date1.month = 2;
    date1.day = 5;
    date1.time = 1200;
    financialLog financialLog1;
    financialLog1.userId[0] = 'a';
    financialLog1.userId[1] = '\0';
    financialLog1.date = date1;
    financialLog1.money = 500;
    financialLog1.state = 2;
    insertFinancialLog(&financialLog1);
    financialLog **financialLogs;
    int size;
    financialLogs = getFinancialLogByStateAndType(&size, NULL, -1, date1, date1);
    for(int i = 0; i < size; i++)
        printFinancialLog(financialLogs[i]);
//    printf("%d\n", sumFinancialLogByStateAndType(financialLog1.userId, -1 ,date1, date1));
}

void testVotedb(){
//    Date date1;
//    date1.year = 1200;
//    date1.month = 2;
//    date1.day = 5;
//    date1.time = 1200;
//    poll poll1;
//    poll1.id[0] = '5';
//    poll1.id[1] = '\0';
//    poll1.date = date1;
//    poll1.question[0] = 'a';
//    poll1.question[1] = '\0';
//    poll1.count = 3;
//    poll1.cases[0][0] = 'a';
//    poll1.cases[0][1] = '\0';
//    poll1.cases[1][0] = 'b';
//    poll1.cases[1][1] = '\0';
//    poll1.votes[0] = 1;
//    poll1.votes[1] = 2;
//    insertPoll(&poll1);
    votePoll("5", 2 , 5);
//    poll *poll2 = getPollById("5");
//    printPoll(poll2);
//    poll *polls;
//    int size;
//    polls = getAllPoll(&size);
//    for(int i = 0; i < size; i++)
//        printPoll(polls[i]);
//    delPoll("5");
}

void testnewsdb(){
//    Date date1;
//    date1.year = 1200;
//    date1.month = 2;
//    date1.day = 5;
//    date1.time= 1300;
//    news news1;
//    news1.id[0] = 'd';
//    news1.id[1] = '\0';\
//    news1.title[0] = 'a';
//    news1.title[1] = '\0';
//    news1.content[0] = '6';
//    news1.content[1] = '\0';
//    news1.date = date1;
//    insertNews(&news1);
//    news **newss;
//    int size;
//    newss = getAllNews(&size);
//    for(int i = 0; i < size; i++)
//        printNews(newss[i]);
    delNews("d");
}

void testVotedb1(){
//    vote vote1;
//    vote1.userId[0] = '8';
//    vote1.userId[1] = '\0';
//    vote1.pollId[0] = '5';
//    vote1.pollId[1] = '\0';
//    vote1.option = 2;
//    insertVote(&vote1);
//    printf("%d\n", isVoteById("5", "8"));
//    vote *vote2;
//    vote2 = getVote("5", "8");
//    printf("%d", vote2 == NULL);
//    delVote("5" , "8");
}

//int main(){
////    testReservedFood();
////    testUserdb();
////    testSelfdb();
////    testfooddb();
//    testScheduledb();
////    testFoodLogdb();
////    testFinancialLogdb();
////    testVotedb();
////    testnewsdb();
////    testVotedb1();
//    return 0;
//}