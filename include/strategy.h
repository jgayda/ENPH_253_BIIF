#include <sensors.h>

extern const int methanos_turnOrder_post1 [3];
// extern const int methanos_turnOrder_post2 [] = {RIGHT,RIGHT,RIGHT};
extern const int thanos_turnOrder_post1 [3];
// extern const int thanos_turnOrder_post2 [] = {LEFT,LEFT,LEFT};

extern int currentPostMap[10];



int initializeStrategy(int TEAM); // returns the array size of the strategy