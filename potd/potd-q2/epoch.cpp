#include "epoch.h"
/* Your code here! */
int hours(long time_t) {
    int output = time_t / 60 / 60;
    return output;
}

int days(long time_t) {
    int output = time_t / 60 / 60 / 24;
    return output;
}

int years(long time_t) {
    int output = time_t / 60 / 60 / 24 / 365;
    return output;
}
