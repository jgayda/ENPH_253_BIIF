#ifndef SEARCH_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define SEARCH_H

int searchMode();
int detectDistance_cm(int trigPin,int echoPin);

extern bool firstFork;

#endif