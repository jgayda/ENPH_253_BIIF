#include <strategy.h>
#include <sensors.h>

//const int methanos_turnOrder_post1 [3] = {RIGHT,LEFT,LEFT};
const int methanos_turnOrder_TEST [3] = {RIGHT,RIGHT,RIGHT};
const int thanos_turnOrder_TEST [3] = {LEFT,LEFT,LEFT};

const int methanos_turnOrder_2[3]= {RIGHT,LEFT,LEFT};
const int thanos_turnOrder_2[3] = {LEFT,RIGHT,RIGHT};

//const int M_post_1 [2] = {RIGHT LEFT, LEFT};
// const int M_post_2 [2];
// const int M_post_3 [3];
// const int M_post_4 [3];
// const int M_post_5 [4];
// const int M_post_6 [5];

// const int T_post_1 [2];
// const int T_post_2 [2];
// const int T_post_3 [3];
// const int T_post_4 [3];
// const int T_post_5 [4];
// const int T_post_6 [5];



int initializeStrategy(int TEAM) {
    int size = 0;


    if(TEAM == THANOS) {
         size = sizeof(thanos_turnOrder_TEST)/sizeof(thanos_turnOrder_TEST[0]);
        for (int i = 0; i < sizeof thanos_turnOrder_TEST/sizeof thanos_turnOrder_TEST[0]; i ++) {
            currentPostMap[i] = thanos_turnOrder_TEST[i];
            Serial.println(currentPostMap[i]);
        }
    } else {
        for (int i = 0; i < sizeof methanos_turnOrder_TEST/sizeof methanos_turnOrder_TEST[0]; i ++) {
            size = sizeof(methanos_turnOrder_TEST)/sizeof(methanos_turnOrder_TEST[0]);
            currentPostMap[i] = methanos_turnOrder_TEST[i];
            Serial.println(currentPostMap[i]);
        }
    }

    return size;
}

int switchStrategy(int TEAM) {
    int size = 0;

    if(TEAM == THANOS) {
         size = sizeof(thanos_turnOrder_2)/sizeof(thanos_turnOrder_2[0]);
        for (int i = 0; i < sizeof thanos_turnOrder_2/sizeof thanos_turnOrder_2[0]; i ++) {
            currentPostMap[i] = thanos_turnOrder_2[i];
            Serial.println(currentPostMap[i]);
        }
    } else {
        for (int i = 0; i < sizeof methanos_turnOrder_2/sizeof methanos_turnOrder_2[0]; i ++) {
            size = sizeof(methanos_turnOrder_2)/sizeof(methanos_turnOrder_2[0]);
            currentPostMap[i] = methanos_turnOrder_2[i];
            Serial.println(currentPostMap[i]);
        }
    }

    return size;
}