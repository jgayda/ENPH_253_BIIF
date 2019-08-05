#include <sensors.h>

extern const int methanos_turnOrder_TEST [3];
// extern const int methanos_turnOrder_post2 [] = {RIGHT,RIGHT,RIGHT};
extern const int thanos_turnOrder_TEST [3];
// extern const int thanos_turnOrder_post2 [] = {LEFT,LEFT,LEFT};
extern const int methanos_turnOrder_2 [3];
extern const int thanos_turnOrder_2 [3];

extern const int M_post_1 [2];
extern const int M_post_2 [2];
extern const int M_post_3 [3];
extern const int M_post_4 [3];
extern const int M_post_5 [4];
extern const int M_post_6 [5];

extern const int T_post_1 [2];
extern const int T_post_2 [2];
extern const int T_post_3 [3];
extern const int T_post_4 [3];
extern const int T_post_5 [4];
extern const int T_post_6 [5];

extern int currentPostMap[6];



int initializeStrategy(int TEAM); // returns the array size of the strategy
int switchStrategy(int TEAM); // returns the second strategy for each team