/**
 * Engi's Kitchen Expansion
 * Event Bus
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file eventbus.c
 */

#include "eventbus.h"


void listen_event(Event event, f_broadcast f) {
    if(events.T[event].broadcastListeners.N <= MAX_LISTENERS) {
        events.T[event].broadcastListeners.N++;
        events.T[event].broadcastListeners.T[events.T[event].broadcastListeners.N] = f;
    }
}

void listen_1p_event(Event event, f_broadcast_1p f) {
    if(events.T[event].broadcast1PListeners.N <= MAX_LISTENERS) {
        events.T[event].broadcast1PListeners.N++;
        events.T[event].broadcast1PListeners.T[events.T[event].broadcast1PListeners.N] = f;
    }
}

void listen_np_event(Event event, f_broadcast_np f) {
    if(events.T[event].broadcastNPListeners.N <= MAX_LISTENERS) {
        events.T[event].broadcastNPListeners.N++;
        events.T[event].broadcastNPListeners.T[events.T[event].broadcastNPListeners.N] = f;
    }
}

void listen_getval_event(Event event, f_getval f) {
    events.T[event].getvalListener = f;
}


void publish_event(Event event) {
    int i;
    f_broadcast f;
    for(i = 1; i <= events.T[event].broadcastListeners.N; i++) {
        f = events.T[event].broadcastListeners.T[i];
        f();
    }
}

void publish_1p_event(Event event, DataType data)  {
    int i;
    f_broadcast_1p f;
    for(i = 1; i <= events.T[event].broadcast1PListeners.N; i++) {
        f = events.T[event].broadcast1PListeners.T[i];
        f(data);
    }
}

//TODO DO THIS
// void publish_np_event(int event, DataType data, ...);

DataType publish_getval_event(Event event) {
    return events.T[event].getvalListener();
}