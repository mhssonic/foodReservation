#include "food.h"
#include "stdlib.h"

void addToReservedFoods(const char id[], const char userId[]){
    reservedFood *reservedFood1 = (reservedFood *) malloc(sizeof (reservedFood));
    strcpy(reservedFood1->id, id);
    strcpy(reservedFood1->userId, userId);
    insertReservedFood(reservedFood1);
    free(reservedFood1);
}

int selectSchedule(int size, schedule **schedules){//return index(its start from 1) of schedule return 0 in case of not selecting
    char c;
    int i = 1;
    food *tempFood;
    self *tempSelf;
    while(1){
        initscr();
//        mvprintw(5, 5, "%d" ,flag);
        printCenter("Select Schedule", 1);
        mvprintw(8, 5, "Schedule: %d/%d" , i, size);
        printCenter("Press 1 for back to menu press 4 for pre_schedule 6 for next schedule or 0 for Select", 2);
        int col = getmaxx(stdscr);
        if (size > 0 && i > 0){
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
            if(i > 1)
                i--;
            continue;
        }
        if(c == '1'){
            clear();
            endwin();
            return 0;
        }
        if(c == '6'){
            clear();
            endwin();
            if (i < size)
                i++;
            continue;
        }
        if(c == '0') {
            clear();
            endwin();
            if (size > 0 && i > 0)
                return i;
        }
        clear();
        endwin();
    }
}