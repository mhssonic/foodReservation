#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../tools.h"
#include <string.h>
#include "../database/databas.h"


user *userLogin(const char userId[], const char password[]){
    if (isUserId(userId) == 0)
        return NULL;

    user *loggedInUser = getUserByUserId(userId);
    if(strcmp(loggedInUser->pass, password) == 0){
        return loggedInUser;
    }
    return NULL;
}

bool userChangePass(const char userId[], const char newPass[]){//without UI
    if (isUserId(userId) == 0)
        return 0;
    char temp[25];
    sprintf(temp, "\'%s\'", newPass);
    updateUser(userId, "pass", temp);
    return 1;
}

bool userChangeRole(const char userId[], int newRole){//without UI
    if (isUserId(userId) == 0)
        return 0;
    char temp[15];
    sprintf(temp, "%d", newRole);
    updateUser(userId, "role", temp);
    return 1;
}

bool userToStudent(const char userId[]){
    if (isUserId(userId) == 0)
        return 0;
    if (getUserByUserId(userId)->role != DIS_STUDENT)
        return 0;
    char role[2] = {'0' + STUDENT, '\0'};
    updateUser(userId, "role", role);
    return 1;
}

bool userToDisStudent(const char userId[]){
    if (isUserId(userId) == 0)
        return 0;
    if (getUserByUserId(userId)->role != STUDENT)
        return 0;
    char role[2] = {'0' + DIS_STUDENT, '\0'};
    updateUser(userId, "role", role);
    return 1;
}

bool userDelStudent(const char userId[]){
    if (isUserId(userId) == 0)
        return 0;
    delUser(userId);
    return 1;
}

bool userRegister(const char name[], const char family[], char userId[], const char pass[], long int nationalIdCode, int year, int month, int day, bool gender, int role){
    if (isUserId(userId) == 1){
        return 0;
    }
    user *user1 = (user *) malloc(sizeof (user));
    user1->role = role;
    strcpy(user1->name, name);
    strcpy(user1->family, family);
    strcpy(user1->userId, userId);
    strcpy(user1->pass, pass);
    user1->nationalIdCode = nationalIdCode;
    user1->birthdate.year = year;
    user1->birthdate.month = month;
    user1->birthdate.day = day;
    user1->gender = gender;
    insertUser(user1);
    free(user1);
    return 1;
}

bool userRegisterByUser(user *user1){
    if (isUserId(user1->userId) == 1)
        return 0;
    insertUser(user1);
    return 1;
}

bool userChangeCredit(const char userId[], int credit){
    if (isUserId(userId) == 0)
        return 0;
    updateCreditUser(userId, credit);
    return 1;
}

user *updateUserWithDB(user *user1){
    user *p = getUserByUserId(user1->userId);
    *user1 = *p;
    free(p);
    return user1;
}


void menuRegister(){
    int flag = 0;
    user *userReg = (user *) malloc(sizeof (user));
    char c;
    char temp[30];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("you can only use number, letters, !, ?, - , _ and . in string inputs", 1);
        printCenter("use 1 for student and 0 for admin and 0 for female and 1 for males", 2);
        if (flag == 1)
            printCenter("Your format of input is wrong", 4);
        if (flag == 2)
            printCenter("there is already a user with this username", 4);
        printCenter("Press enter any key for register or press 1 for back to login", 3);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }

        int col = getmaxx(stdscr);
        echo();

        mvprintw(6,(col- 9)/3,"%s","name:");
        getstr(userReg->name);

        mvprintw(6, 2 * (col- 9)/3, "%s" ,"family:");
        getstr(userReg->family);

        mvprintw(7,(col- 9)/4,"%s","Username:");
        getstr(userReg->userId);

        mvprintw(7, (col- 9)/2, "%s" ,"Password:");
        getstr(userReg->pass);

        mvprintw(7, 3 * (col- 9)/4, "%s" ,"national Id Code:");
        getstr(temp);
        if(sscanf(temp, "%ld", &(userReg->nationalIdCode)) != 1)
            flag = 1;

        mvprintw(8, 1 * (col- 9)/4, "%s" ,"gander:");
        c = getch() - '0';
        if (c != 0 && c != 1){
            flag = 1;
        }
        else
            userReg->gender = c;

        mvprintw(8, (col- 9)/2, "%s" ,"role:");
        userReg->role = getch() - '0';
        if (userReg->role != ADMIN && userReg->role != STUDENT){
            flag = 1;
        }
        if(userReg->role == STUDENT){
            userReg->role = REG_STUDENT;
        }

        mvprintw(8, 3 * (col- 9)/4, "%s" ,"birthday (like: 1400-5-6):");
        getstr(temp);

        if (sscanf(temp, "%d-%d-%d", &(userReg->birthdate.year) , &(userReg->birthdate.month) , &(userReg->birthdate.day)) != 3)
            flag = 1;

        if (!isOkStr(userReg->userId) || !isOkStr(userReg->pass) || !isOkStr(userReg->name) || !isOkStr(userReg->family)){
//            printf("im here you fucker %d%d%d%d", isOkStr(userReg->userId) ,isOkStr(userReg->pass) , isOkStr(userReg->name) , isOkStr(userReg->family));
            flag = 1;
        }
        else if(!userRegisterByUser(userReg))
                flag = 2;
        else
        {
            printCenter("your information have been sent to admins press any key to back to login page", 9);
            noecho();
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void UserSetTime(){
    int flag = 0;
    char c;
    char temp[25];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("Press enter then type time and date or just press 1 for get back to menu if time set successfully it will get back to menu", 1);
        if (flag == 1)
            printCenter("Your format of Time is wrong", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }

        int col = getmaxx(stdscr);
        echo();

        mvprintw(6,(col- 36)/2,"%s","Time (like 1401-12-5 1200):");
        getstr(temp);
        Date date;

        if (sscanf(temp, "%d-%d-%d %d", &(date.year) , &(date.month) , &(date.day), &(date.time)) != 4)
            flag = 1;

        else{
            setTime(date);
            printCenter("Your time have been set", 8);
            noecho();
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void userChangePassword(user *user1){//with UI
    int flag = 0;
    char c;
    char newPassword[25];
    char oldPassword[25];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("Press 1 for get back to menu or pres any key for continue", 1);
        if (flag == 1)
            printCenter("Your format of password is wrong", 2);
        if (flag == 2)
            printCenter("Your old password is wrong", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }

        int col = getmaxx(stdscr);
        echo();

        mvprintw(5,(col- 30)/2,"%s","Your old password: ");
        getstr(oldPassword);

        mvprintw(6,(col- 24)/2,"%s","New password: ");
        getstr(newPassword);

        if (!isOkStr(newPassword))
            flag = 1;
        else if (strcmp(oldPassword, user1->pass))
            flag = 2;
        else{
            printCenter("Are you sure? (press y/n)", 7);
            noecho();
            while (c != 'n' && c!= 'y')
                c = getch();
            if(c == 'n'){
                clear();
                endwin();
                continue;
            }
            userChangePass(user1->userId, newPassword);
            printCenter("Your password have been changed", 8);
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void userCharge(user *user1){//UI
    int flag = 0;
    char c;
    int charge;
    char temp[30], userId[30];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("Press 1 for get back to menu or pres any key for continue", 1);
        if (flag == 1)
            printCenter("There isn't a user with that user id or you want steal from them :)", 2);
        if (flag == 2)
            printCenter("Your credit is low", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        int col = getmaxx(stdscr);
        echo();

        mvprintw(3, (col- 20)/2,"%s","User ID: ");
        getstr(userId);
        mvprintw(4, (col- 20)/2,"%s","Credit: ");
        getstr(temp);

        if (sscanf(temp, "%d", &charge) == 1){
            if(user1->role != ADMIN && user1->credit < charge){
                flag = 2;
            }
            else if (!userChangeCredit(userId, charge) || charge < 0)
                flag = 1;
            else {
                financialLog *financialLog1;
                financialLog1 = (financialLog *)malloc(sizeof (financialLog));
                strcpy(financialLog1->userId, userId);
                financialLog1->money = charge;
                financialLog1->date = *getTime();
                financialLog1->state = CHARGE;
                insertFinancialLog(financialLog1);
                userChangeCredit(user1->userId, -charge);
                strcpy(financialLog1->userId, user1->userId);
                financialLog1->money = -charge;
                financialLog1->state = SEND_CHARGE;
                insertFinancialLog(financialLog1);
                free(financialLog1);
                printCenter("credits have been changed", 6);
                c = getch();
                clear();
                endwin();
                return;
            }
        }
        clear();
        endwin();
    }
}

void checkNews(){
    int size;
    news ** listNews = getAllNews(&size);
    char c;
    int i = 1;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your news", 1);
        mvprintw(8, 5, "News: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_news 6 for next news", 2);
        int col = getmaxx(stdscr);
        if (size > 0){
            mvprintw(3, (col- 30)/2, "News Title: %s" , listNews[i - 1]->title);
            mvprintw(4, 20, "News: %s" , listNews[i - 1]->content);
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
