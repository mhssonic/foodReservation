#include "student.h"
#include "user.h"
#include <stdlib.h>

void studentCharge(user *student){
    char c;
    int charge;
    char temp[30];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("Press 1 for get back to menu or pres any key for continue", 1);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        int col = getmaxx(stdscr);
        echo();

        mvprintw(3, 1 * (col- 20)/3,"%s","Cart Number: ");
        getstr(temp);

        mvprintw(3,2 * (col- 20)/3,"%s","password: ");
        getstr(temp);

        mvprintw(4, (col- 20)/2,"%s","Credit: ");
        getstr(temp);
        if (sscanf(temp, "%d", &charge) == 1){
            userChangeCredit(student->userId, charge);
            financialLog *financialLog1;
            financialLog1 = (financialLog *)malloc(sizeof (financialLog));
            strcpy(financialLog1->userId, student->userId);
            financialLog1->money = charge;
            financialLog1->date = *getTime();
            financialLog1->state = CHARGE;
            insertFinancialLog(financialLog1);
            free(financialLog1);
            printCenter("Your credit have been changed", 6);
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void studentFoodLog(user *student){
    int size;
    foodLog **foodLogs = getFoodLogByUserId(&size, student->userId);
    char c;
    int i = 1;
    food *tempFood;
    self *tempSelf;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your food logs", 1);
        mvprintw(8, 5, "food logs: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_news 6 for next food log", 2);
        int col = getmaxx(stdscr);
        if (size > 0){
            tempFood = getFoodById(foodLogs[i - 1]->foodId);
            tempSelf = getSelfById(foodLogs[i - 1]->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d %d" , foodLogs[i - 1]->date.year, foodLogs[i - 1]->date.month, foodLogs[i - 1]->date.day, foodLogs[i - 1]->date.time);
            if (foodLogs[i - 1]->state == EATEN)
                mvprintw(5, 2 * (col- 30)/3, "state: %s" , "EATEN");
            else if (foodLogs[i - 1]->state == RESERVED)
                mvprintw(5, 2 * (col- 30)/3, "state: %s" , "RESERVED");
            else if (foodLogs[i - 1]->state == NOT_RESERVED)
                mvprintw(5, 2 * (col- 30)/3, "state: %s" , "NOT RESERVED");
            else if (foodLogs[i - 1]->state == DAILY_RESERVE)
                mvprintw(5, 2 * (col- 30)/3, "state: %s" , "DAILY RESERVE");
            else if (foodLogs[i - 1]->state == CANCELED)
                mvprintw(5, 2 * (col- 30)/3, "state: %s" , "CANCELED");

        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        clear();
        endwin();
    }
}

void studentFinancialLog(user *student){
    int size;
    financialLog **financialLogs = getFinancialLogByUserId(&size, student->userId);
    char c;
    int i = 1;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your financial logs", 1);
        mvprintw(8, 5, "financial logs: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_news 6 for next financial log", 2);
        int col = getmaxx(stdscr);
        if (size > 0){
            mvprintw(5, 1 * (col- 30)/4, "Money: %d" , financialLogs[i - 1]->money);
            mvprintw(5, 2 * (col- 30)/4, "date: %d-%d-%d %d" , financialLogs[i - 1]->date.year, financialLogs[i - 1]->date.month, financialLogs[i - 1]->date.day, financialLogs[i - 1]->date.time);
            if (financialLogs[i - 1]->state == CHARGE)
                mvprintw(5, 3 * (col- 30)/4, "state: %s" , "CHARGE");
            else if (financialLogs[i - 1]->state == SEND_CHARGE)
                mvprintw(5, 3 * (col- 30)/4, "state: %s" , "SEND CHARGE");
            else if (financialLogs[i - 1]->state == RESERVE_FOOD)
                mvprintw(5, 3 * (col- 30)/4, "state: %s" , "RESERVE FOOD");
            else if (financialLogs[i - 1]->state == CANCEL_RESERVE)
                mvprintw(5, 3 * (col- 30)/4, "state: %s" , "CANCEL RESERVE");

        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        clear();
        endwin();
    }
}

void studentVote(user *student){
    int votedBefore = 0;
    int size;
    poll **polls = getAllPoll(&size);
    char c;
    int i = 1;
    int option = -1;
    while(1){
        option = -1;
        votedBefore = 0;
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Polls", 1);
        mvprintw(8, 5, "Polls: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_vote 6 for next vote log", 2);
        printCenter("Press a, b, c, d for vote or change your vote", 3);
        vote *vote1;
        int col = getmaxx(stdscr);
        if (size > 0){
            mvprintw(4, (col- 30)/2, "Question: %s" , polls[i - 1]->question);
            mvprintw(5, 20, "Case a) %s" , polls[i - 1]->cases[0]);
            mvprintw(6, 20, "Case b) %s" , polls[i - 1]->cases[1]);
            mvprintw(7, 20, "Case c) %s" , polls[i - 1]->cases[2]);
            mvprintw(8, 20, "Case d) %s" , polls[i - 1]->cases[3]);
            if(isVoteById(polls[i - 1]->id, student->userId)){
                vote1 = getVote(polls[i - 1]->id, student->userId);
                mvprintw(9, 15, "You have chosen (%c) already" , vote1->option + 'a');
                votedBefore = 1;
            }
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == 'a')
            option = 0;
        if(c == 'b')
            option = 1;
        if(c == 'c')
            option = 2;
        if(c == 'd')
            option = 3;
        if(size > 0 && option != -1){
            vote *vote2;
            vote2 = (vote *) malloc(sizeof (vote));
            strcpy(vote2->userId, student->userId);
            strcpy(vote2->pollId, polls[i - 1]->id);
            vote2->option = option;
            if (votedBefore == 1)
                delVote(vote2->pollId, vote2->userId);
            insertVote(vote2);
        }
        clear();
        endwin();
    }
}

void studentCancelReserve(user *student){
    int size;
    reservedFood **reservedFoods = getReservedFoodByUserId(student->userId, &size);
    char c;
    int i = 1;
    schedule *tempSchedule;
    food *tempFood;
    self *tempSelf;
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Reserved food", 1);
        mvprintw(8, 5, "Reserved Food: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_food 6 for next food or press 0 for cancel your reserve", 2);
        if (flag){
            printCenter("You can't cancel this food", 7);
        }
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            tempSchedule = getScheduleById(reservedFoods[i - 1]->id);
            tempFood = getFoodById(tempSchedule->foodId);
            tempSelf = getSelfById(tempSchedule->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , tempSchedule->date.year, tempSchedule->date.month, tempSchedule->date.day);
            if(tempSchedule->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == '0'){
            clear();
            endwin();
            if (size > 0 && i > 0){
                if (tempSchedule->meal == LUNCH)
                    tempSchedule->date.time = tempSelf->lunch.start;
                else //Dinner case
                    tempSchedule->date.time = tempSelf->dinner.start;
                if(minusTimes(tempSchedule->date, *getTime()) >= 1){
                    addToFinancialLog(student->userId, tempFood, 0.9,CANCEL_RESERVE);
                    addToFoodLog(student->userId, tempFood, tempSelf, -0.9 ,CANCEL_RESERVE);
                    updateCreditUser(student->userId, 0.9 * tempFood->price);
                    delReservedFood(tempSchedule->id, student->userId);

                    reservedFoods = getReservedFoodByUserId(student->userId, &size);
                }
                else
                    flag = 1;
            }
            continue;
        }
        clear();
        endwin();
    }
}

void studentDefineAgent (user *student){
    int size;
    reservedFood **reservedFoods = getReservedFoodByUserId(student->userId, &size);
    char c;
    int i = 1;
    schedule *tempSchedule;
    food *tempFood;
    self *tempSelf;
    char userId[20];
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Reserved food", 1);
        mvprintw(8, 5, "Reserved Food: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_food 6 for next food or press 0 for define your agent", 2);
        if (flag){
            printCenter("There isn't any user by that user ID", 7);
        }
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            tempSchedule = getScheduleById(reservedFoods[i - 1]->id);
            tempFood = getFoodById(tempSchedule->foodId);
            tempSelf = getSelfById(tempSchedule->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , tempSchedule->date.year, tempSchedule->date.month, tempSchedule->date.day);
            if(tempSchedule->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == '0'){
            if (size > 0 && i > 0){
                mvprintw(6,(col- 36)/3,"%s","Enter his user ID: ");
                getstr(userId);
                if(isUserId(userId)){
                    delReservedFood(tempSchedule->id, student->userId);
                    addToReservedFoods(tempSchedule->id, userId);
                    i = 0;
                    reservedFoods = getReservedFoodByUserId(student->userId, &size);
                    printCenter("Your agent have been changed", 8);
                    c = getch();
                }
                else
                    flag = 1;
            }
            clear();
            endwin();
            continue;
        }
        clear();
        endwin();
    }
}

void studentTakeFood(user *student){
    int size;
    reservedFood **reservedFoods = getReservedFoodByUserId(student->userId, &size);
    char c;
    int i = 1;
    schedule *tempSchedule;
    food *tempFood;
    self *tempSelf;
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Reserved food", 1);
        mvprintw(8, 5, "Reserved Food: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_food 6 for next food or press 0 for define your agent", 2);
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            tempSchedule = getScheduleById(reservedFoods[i - 1]->id);
            tempFood = getFoodById(tempSchedule->foodId);
            tempSelf = getSelfById(tempSchedule->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , tempSchedule->date.year, tempSchedule->date.month, tempSchedule->date.day);
            if(tempSchedule->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == '0'){
            if (size > 0 && i > 0){
                int start, end;
                if (tempSchedule->meal == LUNCH){
                    start = tempSelf->lunch.start;
                    end = tempSelf->lunch.end;

                }
                else { //Dinner case
                    start = tempSelf->dinner.start;
                    end = tempSelf->dinner.end;
                }
                Date rightNow = *getTime();
                if((rightNow.year == tempSchedule->date.year && rightNow.month == tempSchedule->date.month && rightNow.day == tempSchedule->date.day) && (rightNow.time <= end && rightNow.time >= start)){
                    delReservedFood(tempSchedule->id, student->userId);
                    addToFoodLog(student->userId, tempFood, tempSelf, 1, EATEN);
                    i = 0;
                    reservedFoods = getReservedFoodByUserId(student->userId, &size);
                    printCenter("YUM YUM YUM", 8);
                    c = getch();
                }
                else
                    flag = 1;
            }
            clear();
            endwin();
            continue;
        }
        clear();
        endwin();
    }
}

void studentReserveFood(user *student){
    int size;
    schedule **schedules = getAllSchedules(&size);
    char c;
    int i = 1;
    food *tempFood = NULL;
    self *tempSelf = NULL;
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Reserve Food", 1);
        mvprintw(8, 5, "Schedule: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_schedule 6 for next schedule or 0 for reserve food", 2);
        if (flag == 1)
            printCenter("Its too late for this food", 3);

        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            if(tempFood != NULL)
                free(tempFood);
            if(tempSelf != NULL)
                free(tempSelf);
            tempFood = getFoodById(schedules[i - 1]->foodId);
            tempSelf = getSelfById(schedules[i - 1]->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , schedules[i - 1]->date.year, schedules[i - 1]->date.month, schedules[i - 1]->date.day);
            if(schedules[i - 1]->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            flag = 0;
            if(i > 1) {
                i--;
            }
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            flag = 0;
            if (i < size) {
                i++;
            }
            continue;
        }
        if(c == '0') {
            clear();
            endwin();
            if (size > 0 && i > 0 && i < size) {
                if (schedules[i - 1]->meal == LUNCH)
                    schedules[i - 1]->date.time = tempSelf->lunch.start;
                else //Dinner case
                    schedules[i - 1]->date.time = tempSelf->dinner.start;
                if (minusTimes(schedules[i - 1]->date, *getTime()) >= 48) {
                    addToFinancialLog(student->userId, tempFood, 1, RESERVED);
                    addToFoodLog(student->userId, tempFood, tempSelf, 1, RESERVED);
                    updateCreditUser(student->userId, -tempFood->price);

                    addToReservedFoods(schedules[i - 1]->id, student->userId);
                    flag = 2;
                }
                else if(minusTimes(schedules[i - 1]->date, *getTime()) == 0 && schedules[i - 1]->date.time%100 - (*getTime()).time%100 >= 30){
                    printCenter("You can't reserve food normally it would be daily_reserve are you fine with that (press any key or 1 for going back)", 7);
                    noecho();
                    c = getch();
                    if(c == '1')
                        continue;
                    addToFinancialLog(student->userId, tempFood, 2, DAILY_RESERVE);
                    addToFoodLog(student->userId, tempFood, tempSelf, 2, DAILY_RESERVE);
                    updateCreditUser(student->userId, 2 * tempFood->price);

                    addToReservedFoods(schedules[i - 1]->id, student->userId);
                    flag = 2;
                }
                else
                    flag = 1;
            }
            continue;
        }
        clear();
        endwin();
    }
}


void studentChangeSelf(user *student){
    int size;
    reservedFood **reservedFoods = getReservedFoodByUserId(student->userId, &size);
    char c;
    int i = 1;
    schedule *tempSchedule;
    schedule **schedules;
    food *tempFood;
    self *tempSelf;
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Reserved food", 1);
        mvprintw(8, 5, "Reserved Food: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_food 6 for next food or press 0 for change your self", 2);
        if (flag){
            printCenter("its too late", 7);
        }
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            tempSchedule = getScheduleById(reservedFoods[i - 1]->id);
            tempFood = getFoodById(tempSchedule->foodId);
            tempSelf = getSelfById(tempSchedule->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , tempSchedule->date.year, tempSchedule->date.month, tempSchedule->date.day);
            if(tempSchedule->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            flag = 0;
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            flag = 0;
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == '0'){
            clear();
            endwin();
            if (size > 0 && i > 0){
                if (tempSchedule->meal == LUNCH)
                    tempSchedule->date.time = tempSelf->lunch.start;
                else //Dinner case
                    tempSchedule->date.time = tempSelf->dinner.start;
                if(minusTimes(tempSchedule->date, *getTime()) >= 3){
                    int temp_size;
                    schedule **otherSelfs = getSchedulesByTimeAndFood(&temp_size, tempSchedule->date, tempFood->id);
                    int j = selectSchedule(size, otherSelfs);
                    delReservedFood(tempSchedule->id, student->userId);
                    addToReservedFoods(otherSelfs[j - 1]->id, student->userId);
                }
                else
                    flag = 1;
            }
            continue;
        }
        clear();
        endwin();
    }
}

void studentShowReserve(user *student){
    int size;
    reservedFood **reservedFoods = getReservedFoodByUserId(student->userId, &size);
    char c;
    int i = 1;
    schedule *tempSchedule;
    food *tempFood;
    self *tempSelf;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Reserved food", 1);
        mvprintw(8, 5, "Reserved Food: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_food 6 for next food or press 0 for cancel your reserve", 2);
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
            tempSchedule = getScheduleById(reservedFoods[i - 1]->id);
            tempFood = getFoodById(tempSchedule->foodId);
            tempSelf = getSelfById(tempSchedule->selfId);
            mvprintw(4, (col- 30)/3, "Food: %s" , tempFood->name);
            mvprintw(4, 2 * (col- 30)/3, "self: %s" , tempSelf->name);
            mvprintw(5, (col- 30)/3, "date: %d-%d-%d" , tempSchedule->date.year, tempSchedule->date.month, tempSchedule->date.day);
            if(tempSchedule->meal == DINNER)
                mvprintw(5, 2 * (col- 30)/3, "%s", "dinner");
            else
                mvprintw(5, 2 * (col- 30)/3, "%s", "lunch");
        }
        noecho();
        c = getch();
        if(c == '4'){
            clear();
            endwin();
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        clear();
        endwin();
    }
}

void foodBusinessMenu(user *student){
    char c;
    while(1){
        initscr();
        student = updateUserWithDB(student);
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Menu of food business", 1);
        printCenter("Chose what do you want to do and press the key or press 1 to get back to menu", 2);
        int col = getmaxx(stdscr);
        mvprintw(4, 1 * (col- 9)/4, "%s" ,"a)Take food");
        mvprintw(4, 2 * (col- 9)/4, "%s" ,"b)Cancel reserve");
        mvprintw(4, 3 * (col- 9)/4, "%s" ,"c)Show reserved foods");
        mvprintw(5, 1 * (col- 9)/4, "%s" ,"d)Reserve food");
        mvprintw(5, 2 * (col- 9)/4, "%s" ,"e)Define agent");
        mvprintw(5, 3 * (col- 9)/4, "%s" ,"f)Change self");
        noecho();
        c = getch();
        if(c == 'e'){
            clear();
            endwin();
            studentDefineAgent(student);
            continue;
        }
        if(c == 'd'){
            clear();
            endwin();
            studentReserveFood(student);
            continue;
        }
        if(c == 'f'){
            clear();
            endwin();
            studentChangeSelf(student);
            continue;
        }
        if(c == 'a'){
            clear();
            endwin();
            studentTakeFood(student);
            continue;
        }
        if(c == 'b'){
            clear();
            endwin();
            studentCancelReserve(student);
            continue;
        }
        if(c == 'c'){
            clear();
            endwin();
            studentShowReserve(student);
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}


void menuStudent(user* student){
    char welcome[60];
    sprintf(welcome, "Welcome, dear %s %s", student->name, student->family);
    char c;
    while(1){
        initscr();
        student = updateUserWithDB(student);
//        mvprintw(5, 5, "%d" ,flag);
        printCenter(welcome, 1);
        mvprintw(8, 5, "%s %d" ,"Your credit: ", student->credit);
        printCenter("Chose what do you want to do and press the key", 2);
        int col = getmaxx(stdscr);
        mvprintw(3, 1 * (col- 9)/4, "%s" ,"a)Check News");
        mvprintw(3, 2 * (col- 9)/4, "%s" ,"b)Food Business");
        mvprintw(3, 3 * (col- 9)/4, "%s" ,"c)Vote");
        mvprintw(4, 1 * (col- 9)/4, "%s" ,"d)Charge Account");
        mvprintw(4, 2 * (col- 9)/4, "%s" ,"e)Change Password");
        mvprintw(4, 3 * (col- 9)/4, "%s" ,"f)Send Charge");
        mvprintw(5, 1 * (col- 9)/4, "%s" ,"g)Food Log");
        mvprintw(5, 2 * (col- 9)/4, "%s" ,"h)Set Time");
        mvprintw(5, 3 * (col- 9)/4, "%s" ,"i)financial Log");
        mvprintw(6, 2 * (col- 9)/4, "%s" ,"j)Logout");
        noecho();
        c = getch();
        if(c == 'h'){
            clear();
            endwin();
            UserSetTime();
            continue;
        }
        if(c == 'j'){
            clear();
            endwin();
            return;
        }
        if(c == 'e'){
            clear();
            endwin();
            userChangePassword(student);
            continue;
        }
        if(c == 'd'){
            clear();
            endwin();
            studentCharge(student);
            continue;
        }
        if(c == 'f'){
            clear();
            endwin();
            userCharge(student);
            continue;
        }
        if(c == 'a'){
            clear();
            endwin();
            checkNews();
            continue;
        }
        if(c == 'g'){
            clear();
            endwin();
            studentFoodLog(student);
            continue;
        }
        if(c == 'i'){
            clear();
            endwin();
            studentFinancialLog(student);
            continue;
        }
        if(c == 'b'){
            clear();
            endwin();
            foodBusinessMenu(student);
            continue;
        }
        if(c == 'c'){
            clear();
            endwin();
            studentVote(student);
            continue;
        }
        clear();
        endwin();
    }
}