#include "../objects.h"
#ifndef FOODRESERVATION_VOTEDB_H
#define FOODRESERVATION_VOTEDB_H
bool creatVotesTable(PGconn* conn);
bool isVoteById(const char poll_id[], const char user_id[]);
bool insertVote(vote *vote1);
vote *getVote(const char poll_id[], const char user_id[]);
bool delVote(const char poll_id[],const char user_id[]);
#endif //FOODRESERVATION_VOTEDB_H
