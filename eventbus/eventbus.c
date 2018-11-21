/**
 * Engi's Kitchen Expansion
 * Event Bus
 *
 * @author Muhammad Aditya Hilmy, NIM 18217025
 * @file eventbus.c
 */

#include "eventbus.h"

/**
 * Initialize event bus
 */
void init_event_bus() {
    int i;
    for(i = 0; i < NO_OF_EVENTS; i++) {
        events.T[i].broadcastListeners.N = 0;
        events.T[i].broadcastListeners.NT = 0;
        events.T[i].broadcast1PListeners.N = 0;
        events.T[i].broadcast1PListeners.NT = 0;
    }
}

/**
 * Listen for event
 * @param event event
 * @param f function
 */
void listen_event(Event event, f_broadcast f) {
    if(events.T[event].broadcastListeners.N <= MAX_LISTENERS) {
        events.T[event].broadcastListeners.N++;
        events.T[event].broadcastListeners.T[events.T[event].broadcastListeners.N] = f;
    }
}

/**
 * Listen for post event. The functions will be called after the event is published
 * @param event event
 * @param f post-event function
 */
void listen_post_event(Event event, f_broadcast f) {
    if(events.T[event].broadcastListeners.NT <= MAX_LISTENERS) {
        events.T[event].broadcastListeners.NT++;
        events.T[event].broadcastListeners.postT[events.T[event].broadcastListeners.NT] = f;
    }
}

/**
 * Listen for one-parameter event
 * @param event event enum
 * @param f function
 */
void listen_1p_event(Event event, f_broadcast_1p f) {
    if(events.T[event].broadcast1PListeners.N <= MAX_LISTENERS) {
        events.T[event].broadcast1PListeners.N++;
        events.T[event].broadcast1PListeners.T[events.T[event].broadcast1PListeners.N] = f;
    }
}

/**
 * Listen for post event. The functions will be called after the event is published
 * @param event event enum
 * @param f post-event function
 */
void listen_1p_post_event(Event event, f_broadcast_1p f) {
    if(events.T[event].broadcast1PListeners.NT <= MAX_LISTENERS) {
        events.T[event].broadcast1PListeners.NT++;
        events.T[event].broadcast1PListeners.postT[events.T[event].broadcast1PListeners.NT] = f;
    }
}

/**
 * Listen for get value events
 * @param event event enum
 * @param f function returning DataType
 */
void listen_getval_event(Event event, f_getval f) {
    events.T[event].getvalListener = f;
}


void publish_event(Event event) {
    int i;
    f_broadcast f;

    // Invoke listeners
    for(i = 1; i <= events.T[event].broadcastListeners.N; i++) {
        f = events.T[event].broadcastListeners.T[i];
        f();
    }

    // Invoke post listeners
    for(i = 1; i <= events.T[event].broadcastListeners.NT; i++) {
        f = events.T[event].broadcastListeners.postT[i];
        f();
    }
}

void publish_1p_event(Event event, DataType data)  {
    int i;
    f_broadcast_1p f;

    // Invoke listeners
    for(i = 1; i <= events.T[event].broadcast1PListeners.N; i++) {
        f = events.T[event].broadcast1PListeners.T[i];
        f(data);
    }

    // Invoke post listeners
    for(i = 1; i <= events.T[event].broadcast1PListeners.NT; i++) {
        f = events.T[event].broadcast1PListeners.postT[i];
        f(data);
    }
}

DataType publish_getval_event(Event event) {
    return events.T[event].getvalListener();
}