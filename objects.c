#include "objects.h"
#include <stdio.h>

void printUser(user* user1){
    printf("-------User--------------------\n");
    printf("name: %s\n",user1->name);
    printf("family: %s\n",user1->family);
    printf("pass: %s\n",user1->pass);
    printf("user ID: %s\n",user1->userId);
    printf("national ID code: %ld\n",user1->nationalIdCode);
    printf("birthdate: %d-%d-%d\n",user1->birthdate.year, user1->birthdate.month, user1->birthdate.day);
    printf("gender: %d\n",user1->gender);
    printf("role: %d\n",user1->role);
    printf("credit: %d\n",user1->credit);
}

void printSelf(self* self1){
    printf("-------Self--------------------\n");
    printf("name: %s\n",self1->name);
    printf("ID: %s\n",self1->id);
    printf("location: %s\n",self1->location);
    printf("meal: %s\n",self1->meal);
    printf("gender: %d\n",self1->gender);
    printf("size: %d\n",self1->size);
    printf("lunch start: %d\n",self1->lunch.start);
    printf("lunch end: %d\n",self1->lunch.end);
    printf("dinner start: %d\n",self1->dinner.start);
    printf("dinner end: %d\n",self1->dinner.end);

}

void printFood(food* food1){
    printf("-----------Food----------------\n");
    printf("name: %s\n",food1->name);
    printf("ID: %s\n",food1->id);
    printf("type: %d\n",food1->type);
    printf("price: %d\n",food1->price);
}

void printSchedule(schedule * schedule1){
    printf("-------Schedule--------------------\n");
    printf("id: %s\n",schedule1->id);
    printf("foodId: %s\n",schedule1->foodId);
    printf("type: %d\n",schedule1->type);
    printf("selfId ID: %s\n",schedule1->selfId);
    printf("meal: %d\n",schedule1->meal);
    printf("Date: %d-%d-%d\n",schedule1->date.year, schedule1->date.month, schedule1->date.day);
    printf("count: %d\n",schedule1->count);
}

void printReservedFood(reservedFood * reservedFood1){
    printf("-------Reserved Food--------------------\n");
    printf("id: %s\n",reservedFood1->id);
    printf("user ID: %s\n",reservedFood1->userId);
}

void printNews(news * news1){
    printf("-------News--------------------\n");
    printf("title: %s\n",news1->title);
    printf("content: %s\n",news1->content);
    printf("%d-%d-%d-%d\n",news1->date.year, news1->date.month, news1->date.day, news1->date.time);
}

void printPoll(poll *Poll1){
    printf("-------Vote--------------------\n");
    printf("id: %s\n",Poll1->id);
    printf("question: %s\n",Poll1->question);
    printf("cases:\n");
    for (int i = 0; i < 4; i++)
        printf("case %d: %s\nnumber of vote:%d\n", i, Poll1->cases[i], Poll1->votes[i]);
    printf("count: %d\n", Poll1->count);
    printf("%d-%d-%d-%d\n",Poll1->date.year, Poll1->date.month, Poll1->date.day, Poll1->date.time);
}

void printFoodLog(foodLog * foodLog1){
    printf("-------Food Log--------------------\n");
    printf("user ID: %s\n",foodLog1->userId);
    printf("food ID: %s\n",foodLog1->foodId);
    printf("self ID: %s\n",foodLog1->selfId);
    printf("type: %d\n",foodLog1->type);
    printf("state: %d\n",foodLog1->state);
    printf("price: %d\n",foodLog1->price);
    printf("%d-%d-%d-%d\n",foodLog1->date.year, foodLog1->date.month, foodLog1->date.day, foodLog1->date.time);
}

void printFinancialLog(financialLog * financialLog1){
    printf("-------Food Log--------------------\n");
    printf("user ID: %s\n",financialLog1->userId);
    printf("money: %d\n",financialLog1->money);
    printf("state: %d\n", financialLog1->state);
    printf("%d-%d-%d-%d\n",financialLog1->date.year, financialLog1->date.month, financialLog1->date.day, financialLog1->date.time);
}



