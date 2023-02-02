#include "app.h"
#include <stdio.h>
#include "user.h"
#include "../tools.h"


void loginPage(){
    int flag = 0;
    char username[30];
    char password[30];
    user *userLoggedIn;
    char c;
    while(1){
        initscr();
//        raw();
//        noraw();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Welcome to Food Reservation", 1);
        if (flag == 1)
            printCenter("Your username or password is wrong", 3);
        if (flag == 2)
            printCenter("You are not allowed to login", 3);
        printCenter("Press press any key for login or press 1 for register or 0 for exit", 2);
        noecho();
        c = getch();
        if(c == '1'){
            clear();
            endwin();
            menuRegister();
            continue;
        }
        if(c == '0'){
            clear();
            endwin();
            return;
        }

        int col = getmaxx(stdscr);
        mvprintw(5,(col- 9)/3,"%s","Username:");
        echo();
        getstr(username);
        mvprintw(5, 2 * (col- 9)/3, "%s" ,"Password:");
        noecho();
        getstr(password);
        userLoggedIn = userLogin(username, password);
        if (userLoggedIn == NULL){
            flag = 1;
        }
        else{
            if(userLoggedIn->role == STUDENT){
                flag = 0;
                clear();
                endwin();
                menuStudent(userLoggedIn);
            }
            if(userLoggedIn->role == ADMIN){
                flag = 0;
                endwin();
                clear();
                menuAdmin(userLoggedIn);
            }
            else {
                flag = 2;
            }
        }
        clear();
        endwin();
    }
}

//int main()
//{
//
////    char mesg[]="Enter a string: ";		/* message to be appeared on the screen */
////    char str[80];
////    int row,col;				/* to store the number of rows and *
////					 * the number of colums of the screen */
////    initscr();				/* start the curses mode */
////    noecho();
////    getmaxyx(stdscr,row,col);		/* get the number of rows and columns */
////    printCenter(mesg, row / 2);
////    getstr(str);
////    mvprintw(LINES - 2, 0, "You Entered: %s", str);
////    getch();
////    endwin();
//
//    return 0;
//}
