#include <stdio.h>
#include <stdlib.h>
#include "../objects.h"
#include "../src/user.h"
#include "testCase.h"
static user *userLoggedIn;

char **tokenize1(char str[], int* size){
    int j = 0;
    int k = 0;
    int flag = 0;
    char **tokenized = (char**)malloc(60 * sizeof (char*));
    for (int i = 0; i < 50; i++)
        tokenized[i] =  (char*)malloc(110 * sizeof (char));
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++){
        if(j % 49 == 0){
            tokenized = (char**)realloc(tokenized, (j + 60) * sizeof (char*));
            for (int d = k; d < j + 60; d++)
                tokenized[d] =  (char*)realloc( tokenized[d], 110 * sizeof (char));
        }
        if (k % 100 == 0)
            tokenized[j] =  (char*)realloc(tokenized[j], (k + 110) * sizeof (char));
        if(str[i] == '#' || str[i] == '|'){
            tokenized[j][k] = '\0';
            j++;
            k = 0;
            flag = 1;
        }
        else if (str[i] == ':' && flag){
            tokenized[j][k] = '\0';
            j++;
            k = 0;
            flag = 0;
        }
        else{
            tokenized[j][k] = str[i];
            k++;
        }
    }
    tokenized[j][k] = '\0';
    *size = j + 1;
    return tokenized;
}

int login_page(char ** tokenized, int size){
    if(size == 6){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (strcmp(tokenized[4], "password") != 0)
            return 2;
        userLoggedIn = userLogin(tokenized[3], tokenized[5]);
        if(userLoggedIn != NULL)
            return 0;//success
        else
            return 1;//not found
    }
    else
        return 2;
}

//int change_date_time(char ** tokenized, int size){
//    if(size == 6){
//        if (strcmp(tokenized[2] , "date") != 0)
//            return 2;//invalid
//        if (strcmp(tokenized[4], "password") != 0)
//            return 2;
//        userLoggedIn = userLogin(tokenized[3], tokenized[5]);
//        if(userLoggedIn != NULL)
//            return 0;//success
//        else
//            return 1;//not found
//    }
//    else
//        return 2;
//}

int log_out(char ** tokenized, int size){
    if(size == 4){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (userLoggedIn == NULL)
            return NOT_FOUND;
        if (strcmp(tokenized[3], userLoggedIn->userId) != 0)
            return NOT_FOUND;
        userLoggedIn = NULL;
        return SUCCESSS;
    }
    else
        return 2;
}

int change_pass(char ** tokenized, int size){
    if(size == 8){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (strcmp(tokenized[4], "old-pass") != 0)
            return INVALID;
        if (strcmp(tokenized[6], "new-pass") != 0)
            return INVALID;
        if (userLoggedIn == NULL)
            return NOT_FOUND;
        if (strcmp(tokenized[3], userLoggedIn->userId) != 0)
            return NOT_FOUND;
        if (strcmp(tokenized[5], userLoggedIn->pass) != 0)
            return PERMISSION_DENIED;
        userChangePass(userLoggedIn->userId, tokenized[7]);
        userLoggedIn = getUserByUserId(userLoggedIn->userId);
        return SUCCESSS;
    }
    else
        return 2;
}

int change_student_pass(char ** tokenized, int size){
    if(size == 6){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (strcmp(tokenized[4], "new-pass") != 0)
            return INVALID;
        if (userLoggedIn == NULL)
            return PERMISSION_DENIED;
        if (userLoggedIn->role != ADMIN)
            return PERMISSION_DENIED;
        if (!isUserId(tokenized[3]))
            return NOT_FOUND;
        userChangePass(tokenized[3], tokenized[5]);
        return SUCCESSS;
    }
    else
        return 2;
}

int remove_student(char ** tokenized, int size){
    if(size == 6){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (userLoggedIn == NULL)
            return PERMISSION_DENIED;
        if (userLoggedIn->role != ADMIN)
            return PERMISSION_DENIED;
        if (!userDelStudent(tokenized[3]))
            return NOT_FOUND;
        return SUCCESSS;
    }
    else
        return 2;
}

int deactivate(char ** tokenized, int size){
    if(size == 6){
        if (strcmp(tokenized[2] , "user") != 0)
            return 2;//invalid
        if (userLoggedIn == NULL)
            return PERMISSION_DENIED;
        if (userLoggedIn->role != ADMIN)
            return PERMISSION_DENIED;
        if (!userChangeRole(tokenized[3], DIS_STUDENT))
            return NOT_FOUND;
        return SUCCESSS;
    }
    else
        return 2;
}

int change_datetime(char ** tokenized, int size){
    if(size == 6){
        Date date;
        if (strcmp(tokenized[2] , "date") != 0)
            return 2;//invalid
        if (strcmp(tokenized[4] , "time") != 0)
            return INVALID;
        if(sscanf(tokenized[3], "%d-%d-%d", &(date.year), &(date.month), &(date.day)) != 3)
            return INVALID;
        if(strlen(tokenized[5]) != 4)
            return INVALID;
        if(!isNumber(tokenized[5][0]) || !isNumber(tokenized[5][1]) || !isNumber(tokenized[5][2]) || !isNumber(tokenized[5][3]))
            return INVALID;
        if(sscanf(tokenized[5], "%d", &(date.time)) != 1)
            return INVALID;
        setTime(date);
        return SUCCESSS;
    }
    else
        return 2;
}

int approve(char ** tokenized, int size){
    if(size >= 4 && size % 2 == 0){
        for(int i = 2; i < size; i++) {
            if (strcmp(tokenized[i], "user") != 0)
                return 2;//invalid
            if (userLoggedIn == NULL)
                return PERMISSION_DENIED;
            if (userLoggedIn->role != ADMIN)
                return PERMISSION_DENIED;
            if (isUserId(tokenized[i + 1]) == 0)
                return NOT_FOUND;
            user *user1 = getUserByUserId(tokenized[i + 1]);
            if (user1->role != REG_STUDENT && user1->role != REG_ADMIN)
                return NOT_FOUND;
            if(user1->role == REG_ADMIN)
                userChangeRole(tokenized[i + 1], ADMIN);
            else
                userChangeRole(tokenized[i + 1], STUDENT);
            free(user1);
        }
        return SUCCESSS;
    }
    else
        return 2;
}

int registerUser(char ** tokenized, int size){
    if(size == 18){
        if (strcmp(tokenized[2] , "name") != 0)
            return 2;//invalid
        if (strcmp(tokenized[4], "family") != 0)
            return INVALID;
        if (strcmp(tokenized[6], "user-id") != 0)
            return INVALID;
        if (strcmp(tokenized[8], "password") != 0)
            return INVALID;
        if (strcmp(tokenized[10], "national-id-code") != 0)
            return INVALID;
        if (strcmp(tokenized[12], "birthdate") != 0)
            return INVALID;
        if (strcmp(tokenized[14], "gender") != 0)
            return INVALID;
        if (strcmp(tokenized[16], "type") != 0)
            return INVALID;
        int year, day, month;
        long int national;
        bool gender;
        int role;
        if (sscanf(tokenized[13],"%d-%d-%d", &year, &month, &day) != 3)
            return INVALID;
        if (sscanf(tokenized[11],"%ld", &national) != 1)
            return INVALID;
        if (strcmp(tokenized[15], "male") == 0)
            gender = 1;
        else if (strcmp(tokenized[15], "female") == 0)
            gender = 0;
        else
            return INVALID;

        if (userLoggedIn == NULL) {
            if (strcmp(tokenized[17], "student") == 0)
                role = REG_STUDENT;
            else if (strcmp(tokenized[17], "admin") == 0)
                role = REG_ADMIN;
            else
                return INVALID;
        }
        else if (userLoggedIn->role == ADMIN){
            if (strcmp(tokenized[17], "student") == 0)
                role = STUDENT;
            else if (strcmp(tokenized[17], "admin") == 0)
                role = ADMIN;
            else
                return INVALID;
        }
        if(userRegister(tokenized[3] , tokenized[5], tokenized[7], tokenized[9], national, year, month, day, gender, role) == 0)
            return PERMISSION_DENIED;
        return SUCCESSS;
    }
    else
        return 2;
}




int test_case(){
    char str[500];
    FILE *fp = fopen("input.txt", "r");
    char **tokenized;
    if(fp == NULL){
        printf("its NULL");
        return 0;
    }
    int state = -1;
    while(1) {
        state = -1;
        if (fgets(str, 500, fp) == NULL) {
            break;
        }
        int size;
        tokenized = tokenize1(str, &size);
        if (strcmp(tokenized[1], "login") == 0) {
            printf("%s#", tokenized[0]);
            state = login_page(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state== NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
        }
        else if (strcmp(tokenized[1], "change-datetime") == 0) {
            printf("%s#", tokenized[0]);
            state = change_datetime(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == INVALID)
                printf("%s\n", "invalid");
        }
        else if (strcmp(tokenized[1], "logout") == 0) {
            printf("%s#", tokenized[0]);
            state = log_out(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
        }
        else if (strcmp(tokenized[1], "change-pass") == 0) {
            printf("%s#", tokenized[0]);
            state = change_pass(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        else if (strcmp(tokenized[1], "approve") == 0) {
            printf("%s#", tokenized[0]);
            state = approve(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        else if (strcmp(tokenized[1], "register") == 0) {
            printf("%s#", tokenized[0]);
            state = registerUser(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == INVALID)
                printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        else if (strcmp(tokenized[1], "change-student-pass") == 0) {
            printf("%s#", tokenized[0]);
            state = change_student_pass(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        else if (strcmp(tokenized[1], "remove-student") == 0) {
            printf("%s#", tokenized[0]);
            state = remove_student(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        else if (strcmp(tokenized[1], "remove-student") == 0) {
            printf("%s#", tokenized[0]);
            state = deactivate(tokenized, size);
            if (state == SUCCESSS)
                printf("%s\n", "success");
            if (state == NOT_FOUND)
                printf("%s\n", "not_found");
            if (state == INVALID)
                    printf("%s\n", "invalid");
            if (state == PERMISSION_DENIED)
                printf("%s\n", "permission-denied");
        }
        free(tokenized);
    }
    fclose(fp);
}
//
//int main(){
//    test_case();
//    return 0;
//}
//
//
