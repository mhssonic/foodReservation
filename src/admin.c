#include "admin.h"
#include <stdlib.h>

void adminLog(){
    char c;
    char temp1[20];
    char temp2[20];
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Your Logs", 1);
        printCenter("Press 1 for back to menu or any other key to continue", 2);
        if(flag){
            printCenter("Your format of times is wrong", 3);
        }
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        echo();
        poll *poll1 = (poll*)malloc(sizeof(poll));
        int col = getmaxx(stdscr);
        mvprintw(4,col / 4,"%s","Time start(like 1401-12-5 1200):");
        getstr(temp1);
        Date start;
        mvprintw(4,2 * col / 3,"%s","Time end(like 1401-12-5 1200):");
        getstr(temp2);
        Date end;


        if (sscanf(temp1, "%d-%d-%d %d", &(start.year) , &(start.month) , &(start.day), &(start.time)) != 4)
            flag = 1;
        else if (sscanf(temp2, "%d-%d-%d %d", &(end.year) , &(end.month) , &(end.day), &(end.time)) != 4)
            flag = 1;
        else {
            mvprintw(5,1 * (col - 40) / 4,"Number of reserved food:%d",countFoodLogByStateAndType(RESERVED, FOOD ,start, end));
            mvprintw(5,2 * (col - 40) / 4,"Number of eaten food:%d",countFoodLogByStateAndType(EATEN, FOOD ,start, end));
            mvprintw(5,3 * (col - 40) / 4,"Number of reserved food:%d",countFoodLogByStateAndType(DAILY_RESERVE, FOOD ,start, end));
            mvprintw(6,1 * (col - 40) / 4,"Number of reserved dessert:%d",countFoodLogByStateAndType(RESERVED, DESSERT ,start, end));
            mvprintw(6,2 * (col - 40) / 4,"Number of eaten dessert:%d",countFoodLogByStateAndType(EATEN, DESSERT ,start, end));
            mvprintw(6,3 * (col - 40) / 4,"Number of reserved dessert:%d",countFoodLogByStateAndType(DAILY_RESERVE, DESSERT ,start, end));

            mvprintw(7,1 * (col - 40) / 4,"Number of reserved food:%d",sumFoodLogByStateAndType(RESERVED, FOOD ,start, end));
            mvprintw(7,2 * (col - 40) / 4,"Number of eaten food:%d",sumFoodLogByStateAndType(EATEN, FOOD ,start, end));
            mvprintw(7,3 * (col - 40) / 4,"Number of reserved food:%d",sumFoodLogByStateAndType(DAILY_RESERVE, FOOD ,start, end));
            mvprintw(8,1 * (col - 40) / 4,"Number of reserved dessert:%d",sumFoodLogByStateAndType(RESERVED, DESSERT ,start, end));
            mvprintw(8,2 * (col - 40) / 4,"Number of eaten dessert:%d",sumFoodLogByStateAndType(EATEN, DESSERT ,start, end));
            mvprintw(8,3 * (col - 40) / 4,"Number of reserved dessert:%d",sumFoodLogByStateAndType(DAILY_RESERVE, DESSERT ,start, end));
            printCenter("press any key to continue", 6);
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void creatNews(){
    char c;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Creat news", 1);
        printCenter("Press 1 for back to menu or any other key to continue", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        echo();
        news *news1 = (news*)malloc(sizeof(news));
        int col = getmaxx(stdscr);
        mvprintw(3, (col- 30)/2, "%s" , "News Title:");
        getstr(news1->title);
        mvprintw(4, 20, "%s" , "News: ");
        getstr(news1->content);
        news1->date = *getTime();
        insertNews(news1);
        free(news1);
        printCenter("news have been added", 6);
        c = getch();
        clear();
        endwin();
    }
}

void creatPoll(){
    char c;
    char temp[20];
    int flag = 0;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Creat Poll", 1);
        printCenter("Press 1 for back to menu or any other key to continue", 2);
        if(flag){
            printCenter("Your format of time is wrong", 3);
        }
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }
        echo();
        poll *poll1 = (poll*)malloc(sizeof(poll));
        int col = getmaxx(stdscr);
        mvprintw(4, 20, "%s" , "Poll Question:");
        getstr(poll1->question);
        mvprintw(5, 1 * col / 5, "%s" , "case a) ");
        getstr(poll1->cases[0]);
        mvprintw(5, 2 * col / 5, "%s" , "case b) ");
        getstr(poll1->cases[1]);
        mvprintw(5, 3 * col / 5, "%s" , "case c) ");
        getstr(poll1->cases[2]);
        mvprintw(5, 4 * col / 5, "%s" , "case d) ");
        getstr(poll1->cases[3]);
        mvprintw(6,col / 4,"%s","Time (like 1401-12-5 1200):");
        getstr(temp);
        mvprintw(6, 3 * col / 4,"%s","id:");
        getstr(poll1->id);
        Date date;
        poll1->votes[0] = 0;
        poll1->votes[1] = 0;
        poll1->votes[2] = 0;
        poll1->votes[3] = 0;
        poll1->count = 0;

        if (sscanf(temp, "%d-%d-%d %d", &(date.year) , &(date.month) , &(date.day), &(date.time)) != 4)
            flag = 1;
        else {
            poll1->date = date;
            insertPoll(poll1);
            free(poll1);
            printCenter("poll have been added", 7);
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void adminChangeStudentPassword(user *user1){//with UI
    int flag = 0;
    char c;
    char password[25];
    char userId[25];
    while(1){
        initscr();
//        mvprintw(2,5,"%d",flag);
        printCenter("Press 1 for get back to menu or pres any key for continue", 1);
        if (flag == 1)
            printCenter("Your format of password is wrong", 2);
        if (flag == 2)
            printCenter("There is no user with that user ID", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            return;
        }

        int col = getmaxx(stdscr);
        echo();

        mvprintw(5,(col- 30)/2,"%s","user ID: ");
        getstr(userId);

        mvprintw(6,(col- 24)/2,"%s","His/Her new password: ");
        getstr(password);

        if (!isOkStr(password))
            flag = 1;
        else if (!isUserId(userId))
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
            userChangePass(userId, password);
            printCenter("password have been changed", 8);
            c = getch();
            clear();
            endwin();
            return;
        }
        clear();
        endwin();
    }
}

void menuAdmin(user* admin){
    char welcome[60];
    sprintf(welcome, "Welcome, dear %s %s", admin->name, admin->family);
    char c;
    while(1){
        initscr();
        admin = updateUserWithDB(admin);
//        mvprintw(5, 5, "%d" ,flag);
        printCenter(welcome, 1);
        mvprintw(8, 5, "%s %s" ,"Your credit: ", "8 big money");
        printCenter("Chose what do you want to do and press the key", 2);
        int col = getmaxx(stdscr);
        mvprintw(3, 1 * (col- 9)/4, "%s" ,"a)Check News");
        mvprintw(3, 2 * (col- 9)/4, "%s" ,"b)Food Business");//todo
        mvprintw(3, 3 * (col- 9)/4, "%s" ,"c)Creat poll");
        mvprintw(4, 1 * (col- 9)/4, "%s" ,"d)Charge a student account");
        mvprintw(4, 2 * (col- 9)/4, "%s" ,"e)Change Password");
        mvprintw(4, 3 * (col- 9)/4, "%s" ,"f)Change a student password");
        mvprintw(5, 1 * (col- 9)/4, "%s" ,"g)Creat News");
        mvprintw(5, 2 * (col- 9)/4, "%s" ,"h)Set Time");
        mvprintw(5, 3 * (col- 9)/4, "%s" ,"i)Log");
        mvprintw(6, 2 * (col- 9)/4, "%s" ,"j)Logout");//todo users list
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
            userChangePassword(admin);
            continue;
        }
        if(c == 'd'){
            clear();
            endwin();
            userCharge(admin);
            continue;
        }
        if(c == 'f'){
            clear();
            endwin();
            adminChangeStudentPassword(admin);
            continue;
        }
        if(c == 'a'){
            clear();
            endwin();
            checkNews();
            continue;
        }
//        if(c == 'g'){
//            clear();
//            endwin();
//            studentFoodLog(admin);
//            continue;
//        }
        if(c == 'i'){
            clear();
            endwin();
            adminLog();
            continue;
        }
//        if(c == 'b'){
//            clear();
//            endwin();
//            foodBusinessMenu(student);
//            continue;
//        }
        if(c == 'c'){
            clear();
            endwin();
            creatPoll();
            continue;
        }
        if(c == 'g'){
            clear();
            endwin();
            creatNews();
            continue;
        }
        clear();
        endwin();
    }
}
