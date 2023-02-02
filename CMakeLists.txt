cmake_minimum_required(VERSION 3.24)
project(foodReservation C)

set(CMAKE_C_STANDARD 99)
add_executable(foodReservation main.c src/user.c src/user.h database/databas.c database/databas.h database/userdb.c database/userdb.h database/selfdb.c  database/selfdb.h objects.c objects.h database/fooddb.c database/fooddb.h database/scheduledb.c database/scheduledb.h database/reservedFoodsdb.c database/reservedFoodsdb.h database/foodLogdb.h database/foodLogdb.c database/financialLog.c database/financialLog.h database/polldb.c database/polldb.h database/newsdb.c database/newsdb.h src/app.c src/app.h testCase/testCase.c testCase/testCase.h tools.c tools.h src/student.c src/student.h src/admin.c src/admin.h database/votedb.c database/votedb.h src/logs.c src/logs.h src/food.c src/food.h)
find_package(PostgreSQL REQUIRED)
find_package( Curses REQUIRED )
target_include_directories(foodReservation PRIVATE ${PostgreSQL_INCLUDE_DIRS}  ${CURSES_INCLUDE_DIRS})
target_link_libraries(foodReservation PRIVATE ${PostgreSQL_LIBRARIES} ${CURSES_LIBRARIES})