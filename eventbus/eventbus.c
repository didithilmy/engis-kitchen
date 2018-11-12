/**
 * Engi's Kitchen Expansion
 * Event Bus
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file eventbus.c
 */

#include <stdio.h>
#include "eventbus.h"


void listen_event(int event, f_broadcast f) {
    if(broadcastEvents.T[event].N <= MAX_LISTENERS) {
        broadcastEvents.T[event].N++;
        broadcastEvents.T[event].T[broadcastEvents.T[event].N] = f;
    }
}

void listen_1p_event(int event, f_broadcast_1p f) {
    if(broadcast1PEvents.T[event].N <= MAX_LISTENERS) {
        broadcast1PEvents.T[event].N++;
        broadcast1PEvents.T[event].T[broadcast1PEvents.T[event].N] = f;
    }
}

void listen_np_event(int event, f_broadcast_np f) {
    if(broadcastNPEvents.T[event].N <= MAX_LISTENERS) {
        broadcastNPEvents.T[event].N++;
        broadcastNPEvents.T[event].T[broadcastNPEvents.T[event].N] = f;
    }
}

void listen_getval_event(int event, f_getval f) {
    getvalEvents.T[event] = f;
}


void publish_event(int event) {
    int i;
    f_broadcast f;
    for(i = 1; i <= broadcastEvents.T[event].N; i++) {
        f = broadcastEvents.T[event].T[i];
        f();
    }
}

void publish_1p_event(int event, DataType data)  {
    int i;
    f_broadcast_1p f;
    for(i = 1; i <= broadcastEvents.T[event].N; i++) {
        f = broadcastEvents.T[event].T[i];
        f(data);
    }
}

//TODO DO THIS
// void publish_np_event(int event, DataType data, ...);

DataType publish_getval_event(int event) {
    return getvalEvents.T[event]();
}