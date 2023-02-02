#include "../objects.h"
#ifndef FOODRESERVATION_POLLLDB_H
#define FOODRESERVATION_POLLLDB_H
bool creatPollsTable(PGconn* conn);
bool insertPoll(poll * poll1);
poll **getAllPoll(int *size);
poll *getPollById(const char id[]);
bool delPoll(const char id[]);
bool votePoll(const char id[], int numCase, int numberOfVote);
#endif //FOODRESERVATION_POLLLDB_H
