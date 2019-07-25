#include <strategy.h>
#include <sensors.h>

const int methanos_turnOrder_post1 [3] = {RIGHT,LEFT,LEFT};
const int thanos_turnOrder_post1 [3] = {LEFT,RIGHT,RIGHT};



int initializeStrategy(int TEAM) {
    int size = sizeof(thanos_turnOrder_post1)/sizeof(thanos_turnOrder_post1[0]);


    if(TEAM == THANOS) {
        for (int i = 0; i < 3; i ++) {
            currentPostMap[i] = thanos_turnOrder_post1[i];
        }
    } else {
        for (int i = 0; i < 3; i ++) {
            currentPostMap[i] = methanos_turnOrder_post1[i];
        }
    }

    return size;
}
