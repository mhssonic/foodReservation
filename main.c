#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "src/app.h"
#include "src/user.h"

int main() {
//    userChangeRole("sina9090", STUDENT);
    delUser("sina9090");
    Date date;
    date.day = 25;
    date.month = 1;
    date.year = 2023;
    date.time = 1858;
    setTime(date);
    loginPage();
    return 0;
}
